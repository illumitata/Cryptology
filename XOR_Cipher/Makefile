CC=gcc
CFLAGS=-Wall

all: main.o xor.o filehelp.o -lm
	$(CC) main.o xor.o filehelp.o -o xor -lm

main.o: main.c xor.h -lm
	$(CC) main.c -c -o main.o -lm

xor.o: xor.c xor.h filehelp.h -lm
	$(CC) xor.c -c -o xor.o -lm

filehelp.o: filehelp.c filehelp.h -lm
	$(CC) filehelp.c -c -o filehelp.o -lm

clean:				#get rid of *.o files
	@rm -f *.o
