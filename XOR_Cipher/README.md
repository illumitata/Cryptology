# XOR Cipher

Program uses [XOR cipher](https://en.wikipedia.org/wiki/XOR_cipher) to encrypt and decrypt given text file.
Decrypting is not a sure thing and the result depends on many things like:
* LINE_LENGTH variable
* key itself
* the length and arrangement of text
* used ASCII characters

## Running program

Type in the command line and run the program:
```
./xor -arg1
```
Where:
* **arg1** stands for method you want to use
  * **-p** for making a file with lines of the length of the key
  * **-e** encrypting the text
  * **-k** cryptanalysis with cryptogram(a little "bug" in logic doesn't cover well all of the key)
  * **-a** cryptanalysis with simple frequency analysis (knowing that SPACE is the most used english ASCII character)
  * **-s** decrypting with key

For compilation run simple *Makefile*, just type:
```
make
```
And to get rid of object files type:
```
make clean
```

## Editing keys and text

Content of **files** folder provides:

#### key.txt
```
ashdaksjhdkajshdaasdk
```
Where key must be as long as **LINE_LENGTH** in xor.c file.

#### orig.txt
Original text from user.

#### plain.txt
The file with cleartext, after preparing it.

#### crypto.txt
The file where an encrypt result will be saved.

#### decrypt.txt
The file where decrypting result will be saved.
