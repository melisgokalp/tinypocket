Tiny Web server
Dave O'Hallaron
Carnegie Mellon University

Updated 01-Nov-2010, Randal E. Bryant

This is the home directory for the Tiny server, a 200-line Web
server that we use in "15-213: Intro to Computer Systems" at Carnegie
Mellon University.  Tiny uses the GET method to serve static content
(text, HTML, GIF, and JPG files) out of ./ and to serve dynamic
content by running CGI programs out of ./cgi-bin. The default 
page is home.html (rather than index.html) so that we can view
the contents of the directory from a browser.

Tiny is neither secure nor complete, but it gives students an
idea of how a real Web server works. Use for instructional purposes only.

The code compiles and runs cleanly using gcc 4.3.5
on a Linux 2.6.18 kernel.

To install Tiny:
   Type "tar xvf tiny.tar" in a clean directory. 

To run Tiny:
   Run "tiny <port>" on the server machine, 
	e.g., "tiny 8000".
   Point your browser at Tiny: 
	static content: http://<host>:8000
	dynamic content: http://<host>:8000/cgi-bin/adder?1&2

Files:
  tiny.tar		Archive of everything in this directory
  tiny.c		The Tiny server
  Makefile		Makefile for tiny.c
  home.html		Test HTML page
  csapp2ecover-small.jpg	Image embedded in home.html
  README.txt		This file	
  cgi-bin/adder.c	CGI program that adds two numbers, accepted from HTML form
  cgi-bin/Makefile	Makefile for adder.c and divide.c

