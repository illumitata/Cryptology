#Caesar and Affine Ciphers

Program uses [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher) and [Affine cipher](https://en.wikipedia.org/wiki/Affine_cipher) to encrypt and decrypt given text file.

###Running program

Type in the command line and run the program:
```
./cezar -arg1 -arg2
```

Where:
* **arg1** stands for method you want to use
  * **-c** for caesar cipher
  * **-a** for affine cipher
* arg2 stands for action to preform:
  * **-e** encrypting the text
  * **-d** decrypting it
  * **-j** cryptanalysis with cleartext
  * **-k** cryptanalysis without cleartext, gives all possible candidatures
