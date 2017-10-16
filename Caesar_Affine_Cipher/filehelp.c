#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

#define ALPHABET 26

//Greatest common divison
int gcd(int a, int b){

    int temp;
    while (b != 0){
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

//Algorithm returns opposite of a => a' in modulo
int oppositeModulo(int a, int b){

  int u, w, x, z, q;

  u = 1;
  w = a;
  x = 0;
  z = b;

  while(w){
    if(w<z){
      q = u;
      u = x;
      x = q;
      q = w;
      w = z;
      z = q;
    }
    q = w / z;
    u -= q * x;
    w -= q * z;
  }

  if(z==1){
    if(x<0) x+=b;
    return x;
  }
  else return 0;
}

//Checking conditions for affine key
int checkConditions(int a){

  if((gcd(a, ALPHABET) != 1) || ((a*(oppositeModulo(a, ALPHABET))%ALPHABET)!=1)) \
  return 1;
  else return 0;
}

//Reading key to an integer variable
//for caesar key position equals 1 etc. more in README.md
int readKey(char *filename, short int position){

  int key;
  int k, a, b;
  FILE *file = fopen(filename, "r");

  fscanf(file, "%d %d %d", &k, &a, &b);

  fclose(file);

  switch (position){
    case 1:
      if(k>25 || k<1) printf("Wrong key!\n");
      return k;
      break;
    case 2:
      if(checkConditions(a)) printf("Wrong 'a' key!\n");
      if(b>25 || b<1) printf("Wrong 'b' key!\n");
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
