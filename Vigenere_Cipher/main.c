#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vig.h"

int main (int argc, char **argv){

    if(!strcmp(argv[1], "-p")){
      vigenerePrepare("./files/orig.txt", \
                      "./files/plain.txt");
      printf("Check plain.txt for text.\n");
    }
    if(!strcmp(argv[1], "-e")){
      vigenereEncrypt("./files/plain.txt",  \
                      "./files/crypto.txt", \
                      "./files/key.txt");
      printf("Check crypto.txt for text.\n");
    }
    if(!strcmp(argv[1], "-d")){
      vigenereDecrypt("./files/crypto.txt", \
                      "./files/decrypt.txt", \
                      "./files/key.txt");
      printf("Check decrypt.txt for text.\n");
    }
    if(!strcmp(argv[1], "-k")){
      vigenereBreak("./files/crypto.txt",  \
                    "./files/decrypt.txt", \
                    "./files/key-crypto.txt");
      printf("Check decrypt.txt and key-krypto.txt for result.\n");
    }
    // else printf("You entered incorrect options! \n");

  return 0;
}
