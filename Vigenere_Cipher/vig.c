#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vig.h"
#include "filehelp.h"

#define ALPHABET 26
#define KEY_SIZE 26 // Guessing max key size

double frequency[] = {
    0.08167, 0.01492, 0.02782, 0.04253,
    0.12702, 0.02228, 0.02015, 0.06094,
    0.06966, 0.00153, 0.00772, 0.04025,
    0.02406, 0.06749, 0.07507, 0.01929,
    0.00095, 0.05987, 0.06327, 0.09056,
    0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074
};

void vigenerePrepare(char *filename, char *filesave) {

  char *orig = NULL;
  char *plain = NULL;

  orig = readFile(filename);

  // How many chars are in the string
  int origSize = strlen(orig);
  // Allocate the same amount of memory for plain (worst case scenario)
  plain = calloc(origSize, sizeof(char));

  int i = 0;
  int k = 0;

  while(*(orig + i) != '\0') {
    // Check if char is space, tab, any special character(exclude "\n")
    // if true just move the pointer on original text
    if((*(orig + i) < 65 || *(orig + i) > 90) && \
       (*(orig + i) < 97 || *(orig + i) > 122 )) { //&& \
       (*(orig + i) != '\n')) {
      i++;
    }
    else {
      // Check if char is a capital letter, then switch it to lower case
      if(*(orig + i) > 64 && *(orig + i) < 91){
        *(plain + k) = (char) (*(orig + i) + 32);
      }
      // If lower case or new line just copy it
      else {
        *(plain + k) = *(orig + i);
      }
      k++;
      i++;
    }
  }

  saveFile(filesave, plain);

  free(orig);
  free(plain);

  return;
}

void vigenereEncrypt(char *filename, char *filesave, char *filekey) {

  char *plain = NULL;
  char *key = NULL;
  char *encrypt = NULL;

  plain = readFile(filename);
  key = readFile(filekey);

  int plainSize = strlen(plain);
  // Remember keySize is with new line char, so -1 everytime in loops
  int keySize = strlen(key);

  encrypt = calloc(plainSize, sizeof(char));

  int i = 0;

  while(*(plain + i) != '\0') {
    if(*(plain + i)>='a' && *(plain + i)<='z') {
      int j = i % (keySize - 1);
      int keyMove = ((*(key + j) - 'a') % ALPHABET);
      *(encrypt + i) = ((*(plain + i) - 'a' + keyMove) % ALPHABET) + 'a';
    }
    else {
      *(encrypt + i) = *(plain + i);
    }
    i++;
  }

  saveFile(filesave, encrypt);

  free(plain);
  free(key);
  free(encrypt);

  return;
}

void vigenereDecrypt(char *filename, char *filesave, char *filekey) {

  char *encrypt = NULL;
  char *key = NULL;
  char *decrypt = NULL;

  encrypt = readFile(filename);
  key = readFile(filekey);

  int encryptSize = strlen(encrypt);
  // Remember keySize is with new line char, so -1 everytime in loops
  int keySize = strlen(key);

  decrypt = calloc(encryptSize, sizeof(char));

  int i = 0;

  while(*(encrypt + i) != '\0') {
    if(*(encrypt + i)>='a' && *(encrypt + i)<='z') {
      int j = i % (keySize - 1);
      int keyMove = ((*(key + j) - 'a') % ALPHABET);
      *(decrypt + i) = ((*(encrypt + i) - 'a' - keyMove + ALPHABET) % ALPHABET) + 'a';
    }
    else {
      *(decrypt + i) = *(encrypt + i);
    }
    i++;
  }

  saveFile(filesave, decrypt);

  free(encrypt);
  free(key);
  free(decrypt);

  return;
}

int bestMatch(double *tab1, double *tab2) {

  double sum = 0;
  double fit, d;
  double bestFit = 1e100;
  int i, rotate;
  int bestRotate = 0;

  for(i = 0; i < ALPHABET; i++) sum += tab1[i];

  for(rotate = 0; rotate < ALPHABET; rotate++) {

    fit = 0;

    for(i = 0; i < ALPHABET; i++) {
      d = tab1[(i + rotate) % ALPHABET] / sum - tab2[i];
      fit += d * d / tab2[i];
    }

    if(fit < bestFit) {
      bestFit = fit;
      bestRotate = rotate;
    }
  }

  return bestRotate;
}

double calcFrequency(int *text, int length, int interval, char *key) {

  double sum, d, result;
  double out[ALPHABET], accuracy[ALPHABET] = {0};
  int i, j, rotate;

  for(j = 0; j < interval; j++) {
    for(i = 0; i < ALPHABET; i++) out[i] = 0;
    for(i = j; i < length; i += interval)
    out[text[i]]++;
    // Find the best match
    rotate = bestMatch(out, frequency);
    key[j] = rotate;
    // Add the offset
    key[j] += 'a';
    for(i = 0; i < ALPHABET; i++) accuracy[i] += out[(i + rotate) % ALPHABET];
  }

  for(i = 0, sum = 0; i < ALPHABET; i++) sum += accuracy[i];

  for(i = 0, result = 0; i < ALPHABET; i++) {
    d = accuracy[i] / sum - frequency[i];
    result += d * d / frequency[i];
  }

  key[interval] = '\n';
  key[interval+1] = '\0';

  return result;
}

void vigenereBreak(char *filename, char *filesave, char *keysave) {

  char *encrypt;
  int length = 0;
  int j;
  char key[KEY_SIZE];
  char bestKey[KEY_SIZE] = {0};
  double guess, bestGuess = 1e100;

  encrypt = readFile(filename);
  int sizeEncrypt = strlen(encrypt);

  int text[sizeEncrypt];

  // Copy the encrypted text to array of "ALPHABET type" numbers
  for(j = 0; encrypt[j] != '\0'; j++) text[length++] = encrypt[j] - 'a';

  // We should start from 4 to make it more likely
  // But for education purposes we start from 1
  for(j = 1; j < KEY_SIZE; j++) {
    guess = calcFrequency(text, length, j, key);
    if (bestGuess > guess) {
      bestGuess = guess;
      strcpy(bestKey, key);
    }
  }

  saveFile(keysave, bestKey);
  vigenereDecrypt(filename, filesave, keysave);

  free(encrypt);

  return;
}
