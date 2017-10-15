#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caesar.h"
#include "filehelp.h"

#define ALPHABET 26

void caesarEncrypt(){

  char *input;
  char *code;
  int  key, sizeInput;

  char *filetext = "files/plain.txt";
  char *filekey  = "files/key.txt";
  char *filesave = "files/crypto.txt";

  //make string form input file
  input = readFile(filetext);
  key   = readKey(filekey, 1);

  sizeInput = strlen(input);
  code = (char*)calloc(sizeInput, 4);

  int i = 0;

  while(((char)*(input+i)) != '\0'){
    if(((char)*(input+i)>='A' && (char)*(input+i)<='Z')){
      *(code+i) = ((*(input+i) - 'A' + key) % ALPHABET) + 'A';
    }
    else if(((char)*(input+i)>='a' && (char)*(input+i)<='z')){
      *(code+i) = ((*(input+i) - 'a' + key) % ALPHABET) + 'a';
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

void caesarDecrypt(){

  char *input;
  char *output;
  int  key, sizeInput;

  char *filetext = "files/crypto.txt";
  char *filekey  = "files/key.txt";
  char *filesave = "files/decrypt.txt";

  //make string form input file
  input = readFile(filetext);
  key   = readKey(filekey, 1);

  sizeInput = strlen(input);
  output = (char*)calloc(sizeInput, 4);

  int i = 0;
  int tmp;

  while(((char)*(input+i)) != '\0'){
    if(((char)*(input+i)>='A' && (char)*(input+i)<='Z')){
      *(output+i) = (((*(input+i) - 'A') - key + ALPHABET) % ALPHABET) + 'A';
    }
    else if(((char)*(input+i)>='a' && (char)*(input+i)<='z')){
      *(output+i) = (((*(input+i) - 'a') - key + ALPHABET) % ALPHABET) + 'a';
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
