#include "string.h"

size_t strlen(const char *str)
{
    size_t i = 0;
    
    while(str[i])
        i++;

    return i;
}

size_t strcmp(const char *str1, const char *str2)
{
    size_t i = 0;

    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
            break;
        i++;
    }

    return str1[i] - str2[i];
}

void strcpy(char *dest, const char *source)
{
    size_t i = 0;

    while (source[i])
    {
        dest[i] = source[i];
        i++;
    }
}

void strcat(char* dest, const char *source)
{
    size_t start,i;

    start = strlen(dest);
    i = 0;
    
    while (source[i])
    {
        dest[start+i] = source[i];
        i++;
    }
}

char hextochar(byte hex)
{
    static const char values[] = "0123456789abcdef";

    if (hex < 16)
        return values[hex];
    
    return -1;
}

void bytetostr(byte value, char buffer[3])
{
    buffer[2] = '\0';
    buffer[1] = hextochar(value & 0x00FF);
    buffer[0] = hextochar(value >> 4);
}

void wordtostr(word value, char buffer[5])
{
    buffer[4] = '\0';
    buffer[3] = hextochar(value & 0x00FF);
    buffer[2] = hextochar((value >> 4) & 0x00FF);
    buffer[1] = hextochar((value >> 8) & 0x00FF);
    buffer[0] = hextochar((value >> 12) & 0x00FF);
}

void dwordtostr(dword value, char buffer[9])
{
    buffer[8] = '\0';
    buffer[7] = hextochar(value & 0x00FF);
    buffer[6] = hextochar((value >> 4) & 0x00FF);
    buffer[5] = hextochar((value >> 8) & 0x00FF);
    buffer[4] = hextochar((value >> 12) & 0x00FF);
    buffer[3] = hextochar((value >> 16) & 0x00FF);
    buffer[2] = hextochar((value >> 20) & 0x00FF);
    buffer[1] = hextochar((value >> 24) & 0x00FF);
    buffer[0] = hextochar((value >> 28) & 0x00FF);
}

void qwordtostr(qword value, char buffer[17])
{
    buffer[16] = '\0';
    buffer[15] = hextochar(value & 0x00FF);
    buffer[14] = hextochar((value >> 4) & 0x00FF);
    buffer[13] = hextochar((value >> 8) & 0x00FF);
    buffer[12] = hextochar((value >> 12) & 0x00FF);
    buffer[11] = hextochar((value >> 16) & 0x00FF);
    buffer[10] = hextochar((value >> 20) & 0x00FF);
    buffer[9] = hextochar((value >> 24) & 0x00FF);
    buffer[8] = hextochar((value >> 28) & 0x00FF);
    buffer[7] = hextochar((value >> 32) & 0x00FF);
    buffer[6] = hextochar((value >> 36) & 0x00FF);
    buffer[5] = hextochar((value >> 40) & 0x00FF);
    buffer[4] = hextochar((value >> 44) & 0x00FF);
    buffer[3] = hextochar((value >> 48) & 0x00FF);
    buffer[2] = hextochar((value >> 52) & 0x00FF);
    buffer[1] = hextochar((value >> 56) & 0x00FF);
    buffer[0] = hextochar((value >> 60) & 0x00FF);
}