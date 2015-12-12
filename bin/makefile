fibo: fibonacci.o commander.o
	gcc -std=c99 fibonacci.o commander.o -o fibo

test : test.o commander.o
	gcc -std=c99 test.o commander.o -o test

fibonacci.o : ../commander.h ../fibonacci.c
	gcc -std=c99 -c ../fibonacci.c

test.o : ../commander.h ../test.c
	gcc -std=c99 -c ../test.c

commander.o : ../commander.c ../commander.h
	gcc -std=c99 -c ../commander.c
