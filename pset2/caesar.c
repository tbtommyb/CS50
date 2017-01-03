#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Error: key value expected\n");
        return 1;
    }
    int k = atoi(argv[1]);
    string input = GetString();
    
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        int letter = input[i];
        if(isalpha(letter))
        {
            int cipher = 0;
            if(isupper(letter))
            {
                cipher  = (((letter - 65) + k ) % 26 ) + 65;
            } else
            {
                cipher  = (((letter - 97) + k ) % 26 ) + 97;
            }
            printf("%c", cipher);
        } else {
            printf("%c", letter);
        }
    }
    printf("\n");
    return 0;
}