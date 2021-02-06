#include <stdio.h>

void encode(char*, char*);

void readString(char* s);

int main()
{
    char s1[32] = "";
    char s2[32] = "";

    printf("Input: ");
    readString(s1);

    encode(s1, s2);
    printf("Encoded: %s", s2);
    
    return 0;
}

void readString(char* s)
{
    scanf("%s", s);
}