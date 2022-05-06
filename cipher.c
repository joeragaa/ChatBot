#include "cipher.h"
//the encryption function takes a string of plain text and an integer key
//and a roational cipher is created based on the rovided key
void encrypt_caesar(char* plainText, int key)
{
	//implementing caesar cipher
	int index = 0;
	while(plainText[index]!='\0')
	{
		//check if character is in the alphabet 
	  if (plainText[index] >= 'A' && plainText[index]<= 'Z')
		{
			//increment the character by 'key' amount in the alphabet
			char c = plainText[index] - 'A';
			c += key;
			c = c % 26;
			plainText[index] = c + 'A';
		}
		//handle lower case
		else if (plainText[index] >= 'a' && plainText[index]<= 'z')
		{
			char c = plainText[index] - 'a';
			c += key;
			c = c % 26;
			plainText[index] = c + 'a';
		}
    index++;
	}
}
//the decryption function takes the same inputs as before
//and decrements the cipher text by the given key
void decrypt_caesar(char* cipherText,int key)
{
	int index=0;
	while(cipherText[index]!='\0')
	{
		if (cipherText[index] >= 'A' && cipherText[index]<= 'Z')
		{
			//decrement the character by 'key' amount in the alphabet
			char c = cipherText[index] - 'A';
			c+=26;
			c -= key;
			c = c % 26;
			cipherText[index] = c + 'A';
		}
		//handle lower case
		else if (cipherText[index] >= 'a' && cipherText[index]<= 'z')
		{
			char c = cipherText[index] - 'a';
			c+=26;
			c -= key;
			c = c % 26;
			cipherText[index] = c + 'a';
		}
		index++;
	}
}

void vigenere_key(char* plainText, char* key, char* cyclic_key)
{
	int index = 0;
	while(plainText[index]!='\0')
	{
		cyclic_key[index]=key[index%strlen(key)];
		index++;
	}
}

void encrypt_vigenere(char* plainText, char* key)
{
	int index = 0;
	int text_size = strlen(plainText);
	char *cyclic_key;
	vigenere_key(plainText,key,cyclic_key);
	while(plainText[index]!='\0')
	{
		char c = ( (plainText[index]-'a') + (cyclic_key[index]-'a') ) %26;
		plainText[index]=c+'a';
		index++;
	}
}
void decrypt_vigenere(char* cipherText, char* key)
{
	int index = 0;
	int text_size = strlen(cipherText);
	char *cyclic_key;
	vigenere_key(cipherText,key,cyclic_key);
	while(cipherText[index]!='\0')
	{
		char c = ( (cipherText[index]-'a') - (cyclic_key[index]-'a') + 26 ) %26;
		cipherText[index]=c+'a';
		index++;
	}
}
