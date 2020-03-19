// lab_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char* s = (char*)malloc(100 * sizeof(char));
    memset(s, 0, sizeof(*s));

    scanf("%s", s);
    while (strcmp(s, "exit") != 0)
    {
        printf("%s\n", s);
        scanf("%s", s);
    }

    free(s);

    return 0;
}

