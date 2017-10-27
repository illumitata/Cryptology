CC=gcc
CFLAGS=-Wall

all: main.o xor.o filehelp.o
	$(CC) main.o xor.o filehelp.o -o xor

main.o: main.c xor.h
	$(CC) main.c -c -o main.o

xor.o: xor.c xor.h filehelp.h
	$(CC) xor.c -c -o xor.o

filehelp.o: filehelp.c filehelp.h
	$(CC) filehelp.c -c -o filehelp.o

clean:				#get rid of *.o files
	@rm -f *.o
