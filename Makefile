CC=gcc
CFLAGS=-I. -Wall
DEPS=delay.h

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pitalk: main.o delay.o
	$(CC) -o pitalk main.o delay.o $(CFLAGS)

clean:	
	rm -f pitalk *.o
