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
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-d")){
      affineDecrypt();
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-j")){
      affineDecryptHelp();
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-k")){
      affineDecryptBreak();
      printf("Check decrypt.txt for text.\n");
    }
  }
  else printf("You entered incorrect options! \n");

  return 0;
}
