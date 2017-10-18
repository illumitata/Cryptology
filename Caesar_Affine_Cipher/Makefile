CC=gcc
CFLAGS=-Wall

all: main.o caesar.o affine.o filehelp.o
	$(CC) main.o caesar.o affine.o filehelp.o -o cezar

main.o: main.c caesar.h affine.h
	$(CC) main.c -c -o main.o

affine.o: affine.c affine.h filehelp.h
	$(CC) affine.c -c -o affine.o

caesar.o: caesar.c caesar.h filehelp.h
	$(CC) caesar.c -c -o caesar.o

filehelp.o: filehelp.c filehelp.h
	$(CC) filehelp.c -c -o filehelp.o

clean:				#get rid of *.o files
	@rm -f *.o
