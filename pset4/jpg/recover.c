/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    int jpegs = 0;
    FILE* currentFile = NULL;
    unsigned char buffer[512];
    
    while(fread(&buffer, sizeof(buffer), 1, file))
    {
        // check if jpeg
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // Generate file name
            char title[10];
            sprintf(title, "%03d.jpg", jpegs);
            jpegs++;
            
            // Close previous file if open
            if(currentFile != NULL) {
                fclose(currentFile);
            }
            // Open new file
            FILE* img = fopen(title, "a");
            currentFile = img;
        }
        if(currentFile)
        {
            fwrite(&buffer, sizeof(buffer), 1, currentFile);
        }
    }
    
    // Close open file
    if(currentFile != NULL) {
        fclose(currentFile);
    }
    
}
