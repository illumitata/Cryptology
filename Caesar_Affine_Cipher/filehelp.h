#ifndef FILEHELP_H
#define FILEHELP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filehelp.h"

int readKey(char *filename, short int position);

char* readFile(char *filename);

void saveFile(char *filename, char *result);

int gcd(int a, int b);

int oppositeModulo(int a, int b);

int checkConditions(int a, int b);

#endif
