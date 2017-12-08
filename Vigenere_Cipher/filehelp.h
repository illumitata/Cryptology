#ifndef FILEHELP_H
#define FILEHELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

char* readFile(char *filename);

void saveFile(char *filename, char *result);

#endif
