CC = gcc
CFLAGS = -std=c99 -g -Wall
LDFLAGS =  


all: build/test.out build/fibonacci.out

build/test.out: bin/test.o build/commander.a
	$(CC) $(LDFLAGS) $^ -o $@

build/fibonacci.out: bin/fibonacci.o build/commander.a
	$(CC) $(LDFLAGS) $^ -o $@

bin/test.o: src/test.c src/commander.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/fibonacci.o: src/fibonacci.c src/commander.h
	$(CC) $(CFLAGS) -c $< -o $@

build/commander.a: bin/commander.o
	ar rcs $@ $<
	ranlib $@

bin/commander.o: src/commander.c src/commander.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/* bin/*
