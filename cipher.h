#ifndef CIPHER_H
#define CIPHER_H
#include "init.h"
/*
this file contains the declarations for the encryption fucntions
the data is to be encrypted before sending on the can bus and hence,
decrypted once recieved
*/
void encrypt_caesar(char* plainText, int key);
void decrypt_caesar(char* cipherText,int key);
void decrypt_vigenere(char* cipherText, char* key);
void encrypt_vigenere(char* plainText, char* key);
void vigenere_key(char* plainText, char* key, char* cyclic_key);


#endif
