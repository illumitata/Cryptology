#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affine.h"
#include "filehelp.h"

#define ALPHABET 26

void affineEncrypt(){

  char *input;
  char *code;
  int  a, b, sizeInput;

  char *filetext = "files/plain.txt";
  char *filekey  = "files/key.txt";
  char *filesave = "files/crypto.txt";

  //make string form input file
  input = readFile(filetext);

  a = readKey(filekey, 2);
  b = readKey(filekey, 3);

  sizeInput = strlen(input);
  code = (char*)calloc(sizeInput, 4);

  int i = 0;

  while(*(input+i) != '\0'){
    if(*(input+i)>='A' && *(input+i)<='Z'){
      *(code+i) = ((((*(input+i) - 'A') * a) + b + ALPHABET) % ALPHABET) + 'A';
    }
    else if(*(input+i)>='a' && *(input+i)<='z'){
      *(code+i) = ((((*(input+i) - 'a') * a) + b + ALPHABET) % ALPHABET) + 'a';
    }
    else{
      *(code+i) = *(input+i);
    }
    i++;
  }

  *(code+i+1) = '\0';

  saveFile(filesave, code);

  return;
}

void affineDecrypt(){

  char *input;
  char *output;
  int  a, b, sizeInput;

  char *filetext = "files/crypto.txt";
  char *filekey  = "files/key.txt";
  char *filesave = "files/decrypt.txt";

  //make string form input file
  input = readFile(filetext);

  a = readKey(filekey, 2);
  b = readKey(filekey, 3);

  sizeInput = strlen(input);
  output = (char*)calloc(sizeInput, 4);

  int i = 0;

  //finding opposite number for "a" key
  a = oppositeModulo(a, ALPHABET);
  if(a==0) printf("Can't find the opposite.\n");

  while(*(input+i) != '\0'){
    if(*(input+i)>='A' && *(input+i)<='Z'){
      *(output+i) = (((((*(input+i) - 'A') - b) + ALPHABET) * a) % ALPHABET);
      *(output+i) += 'A';
    }
    else if(*(input+i)>='a' && *(input+i)<='z'){
      *(output+i) = (((((*(input+i) - 'a') - b) + ALPHABET) * a) % ALPHABET);
      *(output+i) += 'a';
    }
    else{
      *(output+i) = *(input+i);
    }
    i++;
  }

  *(output+i+1) = '\0';

  saveFile(filesave, output);

  return;
}
