#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affine.h"
#include "filehelp.h"

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



}
