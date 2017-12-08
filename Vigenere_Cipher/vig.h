#ifndef VIG_H
#define VIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vig.h"
#include "filehelp.h"

  void vigenerePrepare(char *filename, char *filesave);

  void vigenereEncrypt(char *filename, char *filesave, char *filekey);

  void vigenereDecrypt(char *filename, char *filesave, char *filekey);

  void vigenereBreak(char *filename, char *filesave, char *keysave);

#endif
