#import <stdio.h>
#import <cs50.h>
#import <string.h>

void printInitial(int letter);

int main(void)
{
    string name = GetString();
    string namePart;
    
    namePart = strtok(name, " ");
    while(namePart != NULL)
    {
        printInitial((int) namePart[0]);
        namePart = strtok(NULL, " ");
    }
    printf("\n");
    return 0;
}

void printInitial(int letter)
{
    if(letter > 91)
    {
        letter -= 32;
    }
    printf("%c", (char) letter);
}