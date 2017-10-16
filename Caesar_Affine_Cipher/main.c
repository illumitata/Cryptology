#include <stdio.h>
#include <string.h>

#include "caesar.h"
#include "affine.h"

int main (int argc, char **argv){

  if(!strcmp(argv[1], "-c") || !strcmp(argv[1], "-a")){
    //Ceaser section
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-e")){
      caesarEncrypt();
      printf("Check crypto.txt for text.\n");
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-d")){
      caesarDecrypt();
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-j")){
      caesarDecryptHelp();
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-k")){
      caesarDecryptBreak();
      printf("Check decrypt.txt for text.\n");
    }
    /////////////////
    //Affine section
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-e")){
      affineEncrypt();
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-d")){
      //odszyfrowanie afinicznym
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-j")){
      //kryptoanaliza z tekstem jawnym afinicznym
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-k")){
      //kryptoanaliza w oparciu o kryptogram aficzninym
    }
  }
  else printf("You entered incorrect options! \n");

  return 0;
}
