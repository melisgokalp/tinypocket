CC = gcc
CFLAGS = -O2 -Wall -I .
FILES = pocket.c Makefile home.html csapp2ecover-small.jpg README.txt \
	csapp.c csapp.h \
	cgi-bin/adder.c cgi-bin/Makefile

# This flag includes the Pthreads library on a Linux box.
# Others systems will probably require something different.
LIB = -lpthread

all: pocket cgi pocket.tar

pocket: pocket.c csapp.o
	$(CC) $(CFLAGS) -o pocket pocket.c csapp.o $(LIB)

cgi:
	(cd cgi-bin; make)

csapp.o:
	$(CC) $(CFLAGS) -c csapp.c

pocket.tar: $(FILES)
	tar cvf pocket.tar $(FILES)

clean:
	rm -f *.o pocket *~ *.exe
	(cd cgi-bin; make clean)

