#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caesar.h"
#include "filehelp.h"

void caesarEncrypt(){

  char *file = "files/plain.txt";

  char *input;

  //make string form input file
  input = readFile(file);

  printf("%s", input);

  return;
}
