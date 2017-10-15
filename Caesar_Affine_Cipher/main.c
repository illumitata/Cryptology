#include <stdio.h>
#include <string.h>

int main (int argc, char **argv){

  if(!strcmp(argv[1], "-c") || !strcmp(argv[1], "-a")){
    //Ceaser section
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-e")){
      //szyfrowanie cezarem
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-d")){
      //odszyfrowanie cezarem
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-j")){
      //kryptoanaliza z tekstem jawnym cezarem
    }
    if(!strcmp(argv[1], "-c") && !strcmp(argv[2], "-k")){
      //kryptoanaliza w oparciu o kryptogram cezarem
    }
    /////////////////
    //Affine section
    if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "-e")){
      //szyfrowanie afinicznym
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
