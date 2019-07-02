#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
void urlencxlate(char *out_line, const char *in_line);

int main ()
{
    char *env_value, *content_type, fname[128],
    *in_line, *out_line, command[128];
    time_t current_time;
    int content_length;
    FILE *tempfile;
    
    printf("Content-type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    /*
     Handle error conditions or send success message to user
     */
    content_length = atoi(getenv("CONTENT_LENGTH"));
    env_value = getenv("CONTENT_TYPE");
    content_type = malloc (strlen(env_value) + 1);
    if (content_type == NULL)
    {
        printf("<title>Error Occurred</title>\n");
        printf("</head> <body>\n");
        printf("<p>Major failure #1; please notify the webmaster\n");
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (2);
    }
    strcpy(content_type, env_value);
    if (content_length <= 0)
    {
        printf("<title>Error Occurred</title>\n");
        printf("</head> <body>\n");
        printf("<p>The form is empty; please enter some data!\n");
        printf("<br>\n");
        printf("Press the BACK key to return to the form.\n");
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (0);
    }
    else if (strcmp(content_type, "application/x-www-form-urlencoded") != 0)
    {
        printf("<title>Content Error Occurred</title>\n");
        printf("</head> <body>\n");
        printf("<p>Internal error - invalid content type.  Please report\n");
        printf("<br>\n");
        printf("Press the BACK key to return to the form.\n");
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (0);
    }
    /*
     Create temporary file for mailing
     */
    strcpy(fname, tmpnam(NULL));
    tempfile = fopen (fname, "w");     /* create temporary file */
    if (tempfile == NULL)              /* error - didn't create file */
    {
        printf("Internal failure #1 please report %d\n", errno);
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (1);
    }
    
    in_line = malloc (content_length + 1);
    if (in_line == NULL)
    {
        printf("<title>Error Occurred</title>\n");
        printf("</head> <body>\n");
        printf("<p>Major failure #2; please notify the webmaster\n");
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (2);
    }
    out_line = malloc (content_length + 1);
    if (out_line == NULL)
    {
        printf("<title>Error Occurred</title>\n");
        printf("</head> <body>\n");
        printf("<p>Major failure #3; please notify the webmaster\n");
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (2);
    }
    gets(in_line);                                   /* read in form data */
    current_time = time(NULL);                       /* get current time */
    fprintf(tempfile, "%s\n", ctime(&current_time));
    urlencxlate(out_line, in_line);                  /* convert */
    fprintf(tempfile, "%s\n", out_line);
    fclose(tempfile);
    
    printf("<title>Form Submitted</title>\n");
    printf("</head> <body>\n");
    printf("<h1>Your Form Has Been Submitted</h1>\n");
    printf("<p> Thank you very much for your input, it has been \n");
    printf("submitted to our people to deal with... \n");
    printf("<br>\n");
    printf("Press the BACK key to return to the form.\n");
    printf("</p> </body> </html>\n");
    
    /*
     Send the form data via mail; clean up the temporary file
     */
    sprintf(command, "mail -s \"form data\" melisgokalp@gmail.com < %s\n", fname);
    system (command);                                /* execute command */
    remove (fname);                                  /* clean up */
    exit (0);
}

void urlencxlate(char *out_line, const char *in_line)
{
    int in_length, loop_index, out_index;
    in_length = strlen(in_line);
    for (loop_index = 0, out_index = 0; loop_index < in_length;
         loop_index++)
    {
        if (in_line[loop_index] == '%')               /* needs translation */
        {
            /* if your system uses signed characters, use strtol(). */
            /* You may want to apply validity
             checking to the individual characters */
            out_line[out_index] = strtoul(in_line+loop_index + 1, NULL, 16);
            out_index++;
            loop_index += 2;                     /* skip rest of hex value */
        }
        else if (in_line[loop_index] == '+')    /* make a space */
        {
            out_line[out_index] = ' ';
            out_index++;
        }
        else if (in_line[loop_index] == '&')    /* make a newline */
        {
            out_line[out_index] = '\n';
            out_index++;
        }
        else                                    /* just copy */
        {
            out_line[out_index] = in_line[loop_index];
            out_index++;
        }
    }
    out_line[out_index] = '\0';                /* null terminate string */
}
