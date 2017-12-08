#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vig.h"
#include "filehelp.h"

#define ALPHABET 26

void vigenerePrepare(char *filename, char *filesave) {

  char *orig = NULL;
  char *plain = NULL;

  orig = readFile(filename);

  // How many chars are in the string
  int origSize = strlen(orig);
  // Allocate the same amount of memory for plain (worst case scenario)
  plain = calloc(origSize, sizeof(char));

  int i = 0;
  int k = 0;

  while(*(orig + i) != '\0') {
    // Check if char is space, tab, any special character(exclude "\n")
    // if true just move the pointer on original text
    if((*(orig + i) < 65 || *(orig + i) > 90) && \
       (*(orig + i) < 97 || *(orig + i) > 122 )) { //&& \
       (*(orig + i) != '\n')) {
      i++;
    }
    else {
      // Check if char is a capital letter, then switch it to lower case
      if(*(orig + i) > 64 && *(orig + i) < 91){
        *(plain + k) = (char) (*(orig + i) + 32);
      }
      // If lower case or new line just copy it
      else {
        *(plain + k) = *(orig + i);
      }
      k++;
      i++;
    }
  }

  saveFile(filesave, plain);

  free(orig);
  free(plain);

  return;
}

void vigenereEncrypt(char *filename, char *filesave, char *filekey) {

  char *plain = NULL;
  char *key = NULL;
  char *encrypt = NULL;

  plain = readFile(filename);
  key = readFile(filekey);

  int plainSize = strlen(plain);
  // Remember keySize is with new line char, so -1 everytime in loops
  int keySize = strlen(key);

  encrypt = calloc(plainSize, sizeof(char));

  int i = 0;

  while(*(plain + i) != '\0') {
    if(*(plain + i)>='a' && *(plain + i)<='z') {
      int j = i % (keySize - 1);
      int keyMove = ((*(key + j) - 'a') % ALPHABET);
      *(encrypt + i) = ((*(plain + i) - 'a' + keyMove) % ALPHABET) + 'a';
    }
    else {
      *(encrypt + i) = *(plain + i);
    }
    i++;
  }

  saveFile(filesave, encrypt);

  free(plain);
  free(key);
  free(encrypt);

  return;
}

void vigenereDecrypt(char *filename, char *filesave, char *filekey) {

  char *encrypt = NULL;
  char *key = NULL;
  char *decrypt = NULL;

  encrypt = readFile(filename);
  key = readFile(filekey);

  int encryptSize = strlen(encrypt);
  // Remember keySize is with new line char, so -1 everytime in loops
  int keySize = strlen(key);

  decrypt = calloc(encryptSize, sizeof(char));

  int i = 0;

  while(*(encrypt + i) != '\0') {
    if(*(encrypt + i)>='a' && *(encrypt + i)<='z') {
      int j = i % (keySize - 1);
      int keyMove = ((*(key + j) - 'a') % ALPHABET);
      *(decrypt + i) = ((*(encrypt + i) - 'a' - keyMove + ALPHABET) % ALPHABET) + 'a';
    }
    else {
      *(decrypt + i) = *(encrypt + i);
    }
    i++;
  }

  saveFile(filesave, decrypt);

  free(encrypt);
  free(key);
  free(decrypt);

  return;
}

void vigenereBreak(char *filename, char *filesave, char *keysave) {

  char *encrypt = NULL;
  char *brokenkey = NULL;
  char *decrypt = NULL;

  

  return;
}
