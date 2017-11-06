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
#define ASCII        128  //how many chars in ASCII code

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
    if(j==(LINE_LENGTH)){
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
  if(j<LINE_LENGTH){
    while(j<LINE_LENGTH){
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

    *(output+i)= (*(key+k)) ^ (*(input+i));

    i++;
    k++;

    if(k%(LINE_LENGTH)==0) k = 0;
  }

  saveFileBinary(cryptotext, output, sizeInput);

  return;
}

//Breaking the XOR cipher guessing from ciphertext
void xorDecryptBreak(){

  char *input;
  char *output;
  int  sizeInput, sizeOutput, sizeHelp;

  char *plaintext     = CRYPTO_FILE;
  char *cryptotext    = DECRYPT_FILE;

  input = readFileBinary(plaintext);

  sizeInput = readFileBinarySize(plaintext);
  sizeOutput = 16 * sizeInput;

  sizeHelp = ceil(sizeInput / LINE_LENGTH);

  output = (char*)calloc(sizeOutput, 4);;

  char guessKey[LINE_LENGTH];

  int i = 0, j = 0, k = 0;
  char spaceMask = 64;
  char A, B, C;

  //spaceMask = 0  1  0  0  0  0  0  0
  //          128 64 32 16  8  4  2  1


  while(i < (sizeInput-2)){

    A = *(input + i);
    B = *(input + i + 1);
    C = *(input + i + 2);

  /*Wersja z kolumnami gorzej działa?
  while(j<(sizeHelp-2)){

    A = *(input+k + (j*64));
    B = *(input+k + ((j+1)*64));
    C = *(input+k + ((j+2)*64));
    */
    if(((A^B) & spaceMask) != 0){
      if(((A^C) & spaceMask) != 0 && ((B^C) & spaceMask) == 0){
        guessKey[k] = A ^ ' ';
      }
      else{
        if(((A^C) & spaceMask) == 0 && ((B^C) & spaceMask) != 0){
          guessKey[k+1] = B ^ ' ';
        }
      }
    }

    if(((A^C) & spaceMask) != 0){
      if(((A^B) & spaceMask) != 0 && ((B^C) & spaceMask) == 0){
        guessKey[k] = A ^ ' ';
      }
      else{
        if(((A^B) & spaceMask) == 0 && ((B^C) & spaceMask) != 0){
          guessKey[k+2] = C ^ ' ';
        }
      }
    }

    if(((B^C) & spaceMask) != 0){
      if(((A^B) & spaceMask) != 0 && ((A^C) & spaceMask) == 0){
        guessKey[k+1] = B ^ ' ';
      }
      else{
        if(((A^B) & spaceMask) == 0 && ((A^C) & spaceMask) != 0){
          guessKey[k+2] = C ^ ' ';
        }
      }
    }

    i++;
    k++;

    if(k%(LINE_LENGTH)==0)//{
      k = 0;
    //j++;
    //}
  }

  for(int p=0; p<LINE_LENGTH; p++) printf("%d %c ", p, guessKey[p]);

  i = 0;
  k = 0;
  j = 0;

  while(i < sizeInput){

    *(output+j)= guessKey[k] ^ (*(input+i));

    i++;
    j++;
    k++;

    if(k%(LINE_LENGTH)==0){
      k = 0;
      *(output+j) = '\n';
      j++;
    }
  }

  *(output+i+1) = '\0';


  saveFileBinary(cryptotext, output, sizeOutput);

  return;
}

//Breaking the XOR cipher using probabilty
void xorDecryptProb(){

  char *input;
  char *output;
  int  sizeInput, sizeHelp, sizeOutput;

  char *plaintext     = CRYPTO_FILE;
  char *cryptotext    = DECRYPT_FILE;

  input = readFileBinary(plaintext);

  sizeInput = readFileBinarySize(plaintext);
  sizeOutput = 16 * sizeInput;
  output = (char*)calloc(sizeOutput, 4);;

  //First divide the cypher characters into groups
  //depending on which key character they were encoded from
  //So for this case it's 64 groups, 'cause key is 64 characters long
  //Make an array for [key_char][probabilty for this char]
  char guessKey[ASCII][LINE_LENGTH];

  int i = 0, j = 0;
  char tmpHelp;

  for(int b=0; b<LINE_LENGTH; b++){
    for (int a=0; a<ASCII; a++){
      guessKey[a][b] = 0;
    }
  }

  while(i<sizeInput){
    if(j%(LINE_LENGTH)==0) j = 0;
    tmpHelp = (int)*(input+i);
    guessKey[tmpHelp][j] += 1;
    j++;
    i++;
  }

//Printing the coincidence array
/*
  printf("     ");
  for(int a=0; a<ASCII; a++){
    printf(" %d", a%10);
  }
  printf("\n");
  for(int b=0; b<LINE_LENGTH; b++){
    printf("%2d!  ",b);
    for (int a=0; a<ASCII; a++){
      printf("%2d", guessKey[a][b]);
    }
    printf("\n");
  }

  tmpHelp = guessKey[1][0];
  printf("\n%d ", guessKey[1][0]);
  tmpHelp = 84 ^ 32;
  printf(" %c\n", tmpHelp);
*/

//For every line search for most likely ascii code
  int  guessProb;
  char guessPrint;
  int  a = 0;

  char newKey[LINE_LENGTH];

  i = 0;

  for(int b=0; b<LINE_LENGTH; b++){
    guessProb = guessKey[a][b];
    guessPrint = ' ';
    a++;
    while(a<ASCII){
      if(guessKey[a][b]>=guessProb){
        guessProb = guessKey[a][b];
        guessPrint = a;
      }
      a++;
    }
    newKey[i] = guessPrint ^ 32;
    i++;
    a = 0;
  }

  i = 0;
  j = 0;
  int k = 0;

  while(i < sizeInput){

    *(output+k)= newKey[j] ^ (*(input+i));

    k++;
    i++;
    j++;

    if(j%(LINE_LENGTH)==0){
        *(output+k) = '\n';
        k++;
        j = 0;
    }
  }

  *(output+k+1) = '\0';


  saveFileBinary(cryptotext, output, sizeOutput);

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

  output = (char*)calloc(sizeInput, 4);

  int i = 0, k = 0;
  char tmp;

  //Using key to encrypt file
  while(i < sizeInput){

    if(k%(LINE_LENGTH)==0) k = 0;

    *(output+i)= (*(key+k)) ^ (*(input+i));

    i++;
    k++;
  }

  *(output+i+1) = '\0';

  saveFileBinary(cryptotext, output, sizeInput);

  return;
}
