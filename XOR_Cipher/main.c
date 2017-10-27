#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xor.h"

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

int main (int argc, char **argv){

  if(!strcmp(argv[1], "-p") || !strcmp(argv[1], "-e") || !strcmp(argv[1], "-k")){
    if(!strcmp(argv[1], "-p")){
      xorPrepareText();
      printf(GREEN "Text ready for action.\n" RESET);
    }
    if(!strcmp(argv[1], "-e")){
      xorEncrypt();
      printf(GREEN "Text encrypted in crypto.txt file.\n" RESET);
    }
    if(!strcmp(argv[1], "-k")){
      xorDecryptBreak();
      printf(GREEN "Text decrypted in decrypt.txt file.\n" RESET);
    }
  }
  else printf(RED "You entered incorrect options!\n" RESET);

  return 0;
}
