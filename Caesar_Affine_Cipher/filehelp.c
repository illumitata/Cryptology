#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

//Reading key to an integer variable
//for caesar key position equals 1 etc. more in README.md
int readKey(char *filename, short int position){

  int key;
  int k, a, b;
  FILE *file = fopen(filename, "r");

  fscanf(file, "%d %d %d", &k, &a, &b);

  fclose(file);

  switch (position) {
    case 1:
      return k;
      break;
    case 2:
      return a;
      break;
    case 3:
      return b;
      break;
    default:
      printf("Error.\n");
      break;
  }
}

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
