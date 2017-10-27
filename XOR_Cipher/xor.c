#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "xor.h"
#include "filehelp.h"

#define ORIG_FILE     "files/orig.txt"
#define KEY_FILE      "files/key.txt"
#define PLAIN_FILE    "files/plain.txt"
#define CRYPTO_FILE   "files/crypto.txt"
#define DECRYPT_FILE  "files/decrypt.txt"

#define LINE_LENGTH   64  //how many chars in line

//Preparing text to cipher, making lines of pre-defined length
void xorPrepareText(){

  char *input;
  char *output;
  int  sizeInput;

  char *originaltext = ORIG_FILE;
  char *plaintext    = PLAIN_FILE;

  input = readFile(originaltext);

  sizeInput = strlen(input);

  output = (char*)calloc(sizeInput+256, 4);

  int i = 0, k = 0, j = 1;

  //Transform original file into "char-lines"
  while(*(input+i) != '\0'){
    //Next line if there are enough characters
    if(j==LINE_LENGTH+1){
      *(output+k) = '\n';
      j = 0;
      j++;
      k++;
    }
    if(*(input+i)=='\n') *(output+k) = ' ';
    else *(output+k) = *(input+i);
    j++;
    i++;
    k++;
  }

  //Fill with spaces when the length of the last line isn't matching
  if(j<LINE_LENGTH+1){
    while(j<LINE_LENGTH+1){
      *(output+k) = ' ';
      j++;
      k++;
    }
  }

  saveFile(plaintext, output);

  return;
}

//Encrypt text using XOR method
void xorEncrypt(){

  char *input;
  char *key;
  char *output;
  int  sizeInput;

  char *plaintext     = PLAIN_FILE;
  char *keytext       = KEY_FILE;
  char *cryptotext    = CRYPTO_FILE;

  input = readFile(plaintext);
  key   = readFile(keytext);

  sizeInput = strlen(input);

  output = (char*)calloc(sizeInput, 4);

  int i = 0, k = 0;
  char tmp;

  //Using key to encrypt file
  while(*(input+i) != '\0'){

    if(k%(LINE_LENGTH+1)==0) k = 0;

    *(output+i)= (*(key+k)) ^ (*(input+i));

    i++;
    k++;
  }

  FILE *fpo;

  //special binary mode for this one, 'cause special characters happens
  fpo = fopen(CRYPTO_FILE,"wb+");

  fwrite(output, sizeof(char), sizeInput, fpo);

  fclose(fpo);

  return;
}

//Extra Function to test if en/decrypt works
void xorDecryptSimple(){

  char *input;
  char *key;
  char *output;
  int  sizeInput;

  char *plaintext     = CRYPTO_FILE;
  char *keytext       = KEY_FILE;
  char *cryptotext    = DECRYPT_FILE;

  input = readFileBinary(plaintext);
  key   = readFile(keytext);

  sizeInput = readFileBinarySize(plaintext);

  printf("%d\n", sizeInput);

  output = (char*)calloc(sizeInput, 4);

  int i = 0, k = 0;
  char tmp;

  //Using key to encrypt file
  while(i < sizeInput){

    if(k%(LINE_LENGTH+1)==0) k = 0;

    *(output+i)= (*(key+k)) ^ (*(input+i));

    i++;
    k++;
  }

  *(output+i+1) = '\0';

  saveFile(cryptotext, output);

  return;
}
