#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

//Reading whole text file into one buffer
char* readFile(char *filename){

   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if(handler){
       //Go to last byte of file
       fseek(handler, 0, SEEK_END);
       //Get file size
       string_size = ftell(handler);
       //Go back to the begining
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       read_size = fread(buffer, sizeof(char), string_size, handler);

       //add \0 to make buffer a string
       buffer[string_size] = '\0';

       //in case of error
       if(string_size != read_size){
           free(buffer);
           buffer = NULL;
       }

       fclose(handler);
    }

  return buffer;
}

//Saving result in the file (overwriting it!)
void saveFile(char *filename, char *result){

  FILE *save = fopen(filename, "w+");

  if(save){
    fputs  (result, save);
  }

  fclose (save);

  return;
}

//Reading file which is binary
char* readFileBinary(char *name){

	FILE *file;
	char *buffer;
	unsigned long fileLen;

	file = fopen(name, "rb");

	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer=(char *)malloc(fileLen+1);

	fread(buffer, fileLen, 1, file);
	fclose(file);

  return buffer;
}

//Reading only size of file, helps when allocation of output happens
int readFileBinarySize(char *name){

  FILE *file;
  char *buffer;
  unsigned long fileLen;

  file = fopen(name, "rb");

  fseek(file, 0, SEEK_END);
  fileLen=ftell(file);
  fseek(file, 0, SEEK_SET);

  fclose(file);

  return fileLen;
}
