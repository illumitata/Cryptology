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

  while(*(input+i) != '\0'){
    if(*(input+i)>='A' && *(input+i)<='Z'){
      *(code+i) = ((*(input+i) - 'A' + key) % ALPHABET) + 'A';
    }
    else if(*(input+i)>='a' && *(input+i)<='z'){
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

  while(*(input+i) != '\0'){
    if(*(input+i)>='A' && *(input+i)<='Z'){
      *(output+i) = (((*(input+i) - 'A') - key + ALPHABET) % ALPHABET) + 'A';
    }
    else if(*(input+i)>='a' && *(input+i)<='z'){
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

//Using extra.txt file with little bit of original text
void caesarDecryptHelp(){

  char *input;
  char *inputHelp;
  char *output;
  int  key, keytmp, sizeInput;

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

  while(*(inputHelp+k) != '\0'){
    keytmp = (*(input+k) - *(inputHelp+k)) % ALPHABET;
    if(key==keytmp){

      while(*(input+i) != '\0'){
        if(*(input+i)>='A' && *(input+i)<='Z'){
          *(output+i) = (((*(input+i) - 'A') - key + ALPHABET) % ALPHABET) + 'A';
        }
        else if(*(input+i)>='a' && *(input+i)<='z'){
          *(output+i) = (((*(input+i) - 'a') - key + ALPHABET) % ALPHABET) + 'a';
        }
        else{
          *(output+i) = *(input+i);
        }
        i++;
      }

      *(output+i+1) = '\0';

      saveFile(filesave, output);

      break;
    }
    else{
      key = keytmp;
      k++;
    }
  }

  return;
}

//Breaking the code using all possible options for key
void caesarDecryptBreak(){

  char *input;
  char *output;
  int  key, keytmp, sizeInput;

  char *filetext = "files/crypto.txt";
  char *filesave = "files/decrypt.txt";

  input = readFile(filetext);

  sizeInput = strlen(input);
  output = (char*)calloc(sizeInput*100, 4);

  int i = 0;
  int j = 0;

  for(int key=1; key<=25; key++){

    i = 0; //"rewind" the input

    while(*(input+i) != '\0'){
      if(*(input+i)>='A' && *(input+i)<='Z'){
        *(output+j) = (((*(input+i) - 'A') - key + ALPHABET) % ALPHABET) + 'A';
      }
      else if(*(input+i)>='a' && *(input+i)<='z'){
        *(output+j) = (((*(input+i) - 'a') - key + ALPHABET) % ALPHABET) + 'a';
      }
      else{
        *(output+j) = *(input+i);
      }
      i++;
      j++;
    }

    for(int k=0; k<5; k++){
      *(output+j) = '@';
      j++;
    }

    *(output+j) = '\n';
    j++;
  }

  saveFile(filesave, output);

  return;
}
