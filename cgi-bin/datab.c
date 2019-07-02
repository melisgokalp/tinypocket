#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main ()
{
    char input_line[128];
    int record_number, loop_index;
    FILE *saying_file;
    
    printf("Content-type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Witty Saying (database lookup)</title>\n");
    printf("</head> <body>\n");
    /*
     No options, just get saying from file.
     */
    
    /*
     Open counter file
     */
    /* File locking not really needed - read only access */
    saying_file = fopen ("saying.txt", "r");
    if (saying_file== NULL)              /* error - didn't open file */
    {
        printf("Internal failure #1 please report %d\n", errno);
        printf("</p> </body> </html>\n");
        fflush(stdout);
        exit (1);
    }
    
    srand(time(NULL));                 /* init pseudo-random number */
    record_number = rand()%10;         /* get and scale random number */
    for (loop_index = 0; loop_index <= record_number; loop_index++)
    fgets(input_line, sizeof(input_line), saying_file);
    printf("<meta charset=\"utf-8\">");
    printf("<h2 align=\"center\">Burhan Sözleri: %d</h2>\n", record_number);
//    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    printf("<p align=\"center\">\n");
    printf("%s\n", input_line);
    printf("</p> </body> </html>\n");
    fflush(stdout);
    fclose (saying_file);
    exit (0);
}
