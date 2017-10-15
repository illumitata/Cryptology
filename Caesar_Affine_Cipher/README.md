Caesar and Affine Ciphers
========

Program uses [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher) and [Affine cipher](https://en.wikipedia.org/wiki/Affine_cipher) to encrypt and decrypt given text file.

###Running program###

Type in the command line and run the program:
```
./cezar -arg1 -arg2
```
Where:
* **arg1** stands for method you want to use
  * **-c** for caesar cipher
  * **-a** for affine cipher
* **arg2** stands for action to preform:
  * **-e** encrypting the text
  * **-d** decrypting it
  * **-j** cryptanalysis with cleartext
  * **-k** cryptanalysis without cleartext, gives all possible candidatures

For compilation run simple *Makefile*, just type:
```
make
```
And to get rid of object files type:
```
make clean
```

###Editing keys and text###

Content of **files** folder provides:

######key.txt######
```
k a b
```
Where:
* **k** is the key for caesar cipher (must be an integer from 1 to 25)
* **a** and **b** are variables which combine for affine cipher key (where gcd(a,26)=1 and a*a'=1 (mod 26))

#####plain.txt#####
The file with cleartext.

#####crypto.txt#####
The file where an encrypt result will be saved.

#####decrypt.txt#####
The file where decrypting result will be saved.

#####extra.txt#####
The file which stores additional help-cleartext.
