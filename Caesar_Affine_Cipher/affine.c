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

void affineDecryptHelp(){

  char *input;
  char *inputHelp;
  char *output;
  int  a, b, sizeInput;

  char *filetext = "files/crypto.txt";
  char *filehelp = "files/extra.txt";
  char *filesave = "files/decrypt.txt";

  //make string form input file
  input     = readFile(filetext);
  inputHelp = readFile(filehelp);

  sizeInput = strlen(input);
  output = (char*)calloc(sizeInput, 4);

  int i = 0;
  int k = 0;

  //array holding letters and representing equations later
  char tab[2][2];

  while(a==0){

    //finding first letter to decode
    while(*(inputHelp+k) != '\0'){
      if(*(inputHelp+k)>='A' && *(inputHelp+k)<='Z'){
        tab[0][0] = *(inputHelp+k) - 'A';
        tab[0][1] = *(input+k) - 'A';
        break;
      }
      if(*(inputHelp+k)>='a' && *(inputHelp+k)<='z'){
        tab[0][0] = *(inputHelp+k) - 'a';
        tab[0][1] = *(input+k) - 'a';
        break;
      }
      else k++;
    }

    //finding second letter
    if(tab[0]!=NULL){
      k++;
      while(*(inputHelp+k) != '\0'){
        if(*(inputHelp+k)>='A' && *(inputHelp+k)<='Z'){
          tab[1][0] = *(inputHelp+k) - 'A';
          tab[1][1] = *(input+k) - 'A';
          break;
        }
        if(*(inputHelp+k)>='a' && *(inputHelp+k)<='z'){
          tab[1][0] = *(inputHelp+k) - 'a';
          tab[1][1] = *(input+k) - 'a';
          break;
        }
        else k++;
      }
    }
    else printf("Can't find 'a' key, not enough data!\n");

    //calculating modulo equations
    char x, y;

    x = tab[0][0] - tab[1][0];
    if(x<0) x += ALPHABET;

    y = tab[0][1] - tab[1][1];
    if(y<0) y += ALPHABET;

    int plainOpposite = oppositeModulo(x, ALPHABET);

    if(plainOpposite!=0){
      a = (y * plainOpposite) % ALPHABET;
      b = (tab[0][1] - ((a * tab[0][0])%ALPHABET) + ALPHABET) % ALPHABET;

    }
  }

  if(a!=0){

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
  }
  else printf("Can't resolve modulo equations!\n");


  return;
}
