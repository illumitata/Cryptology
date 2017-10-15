#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

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
