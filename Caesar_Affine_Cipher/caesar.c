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
  code = (char*) malloc(sizeof(4 * sizeInput));

  int i = 0;

  while(((char)*(input+i)) != '\0'){
    if(((char)*(input+i)>='A' && (char)*(input+i)<='Z')){
      *(code+i) = 65 + ((*(input+i) + key) % ALPHABET);
      printf("%c\n", *(code+i));
    }
    else{
      *(code+i) = *(input+i);
      printf("%c\n", *(code+i));
    }
    i++;
  }

  *(code+i+1) = '\0';

  saveFile(filesave, code);

  return;
}
