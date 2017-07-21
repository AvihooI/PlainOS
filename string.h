#ifndef _string_h
#define _string_h

#include "types.h"

//Get the length of a null terminated string
size_t strlen(const char *str);

//Compare two strings based on lexical value
size_t strcmp(const char *str1, const char *str2);

//Copy source string into destination string
void strcpy(char *dest, const char *source);

//Concatenate source string to destination string
void strcat(char* dest, const char *source);

//Get the corresponding char (ascii) of a number in hexadecimal base
char hextochar(byte hex);

//Populate a buffer with the ascii representation of the numerical value of a byte
void bytetostr(byte value, char buffer[3]);

//Populate a buffer with the ascii representation of the numerical value of a word
void wordtostr(word value, char buffer[5]);

//Populate a buffer with the ascii representation of the numerical value of a dword
void dwordtostr(dword value, char buffer[9]);

//Populate a buffer with the ascii representation of the numerical value of a qword
void qwordtostr(qword value, char buffer[17]);


#endif