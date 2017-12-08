CC=gcc
CFLAGS=-Wall

all: main.o vig.o filehelp.o
	$(CC) main.o vig.o filehelp.o -o vig

main.o: main.c vig.h
	$(CC) main.c -c -o main.o

vig.o: vig.h filehelp.h
	$(CC) vig.c -c -o vig.o

filehelp.o: filehelp.c filehelp.h
	$(CC) filehelp.c -c -o filehelp.o

clean:				#get rid of *.o files
	@rm -f *.o
