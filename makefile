CC = gcc

CFLAGS = -std=c99 -g
ODIR = bin
PROG = a.out

all: fibo test

fibo: fibonacci.o commander.o
	$(CC) $(LDFLAGS) $(ODIR)/fibonacci.o $(ODIR)/commander.o -o $(ODIR)/fibo.out

test : test.o commander.o
	$(CC) $(LDFLAGS) $(ODIR)/test.o $(ODIR)/commander.o -o $(ODIR)/test.out

fibonacci.o : commander.h fibonacci.c
	$(CC) $(CFLAGS) -c fibonacci.c -o $(ODIR)/fibonacci.o

test.o : commander.h test.c
	$(CC) $(CFLAGS) -c test.c -o $(ODIR)/test.o

commander.o : commander.c commander.h
	$(CC) $(CFLAGS) -c commander.c -o $(ODIR)/commander.o


clean:
	rm -f $(ODIR)/test.out $(ODIR)/fibo.out $(ODIR)/*.o