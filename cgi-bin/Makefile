CC = gcc
CFLAGS = -O2 -Wall -I ..

all: adder email mult datab

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c
email: email.c
	$(CC) $(CFLAGS) -o email email.c
datab: datab.c
	$(CC) $(CFLAGS) -o datab datab.c
mult: mult.c
	$(CC) $(CFLAGS) -o mult mult.c
clean:
	rm -f adder *~ *.exe
