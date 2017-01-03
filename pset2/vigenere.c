#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int getKeyIndex(string key, int i);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Error: key string expected\n");
        return 1;
    }
    string k = argv[1];
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if(!isalpha(k[i]))
        {
            printf("Error: key value is not an alphanumeric string\n");
            return 1;
        }
    }
    string input = GetString();
    int j = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        int letter = input[i];
        if(isalpha(letter))
        {
            int cipherIndex = getKeyIndex(k, j);
            int cipher = 0;
            if(isupper(letter))
            {
                cipher  = (((letter - 'A') + cipherIndex ) % 26 ) + 'A';
            } else
            {
                cipher  = (((letter - 'a') + cipherIndex ) % 26 ) + 'a';
            }
            printf("%c", cipher);
            j++;
        } else {
            printf("%c", letter);
        }
    }
    printf("\n");
    return 0;
}

int getKeyIndex(string key, int i)
{
    int index = key[i % strlen(key)];
    if(isupper(index))
    {
        index -= 'A';
    } else
    {
        index -= 'a';
    }
    return index;
}