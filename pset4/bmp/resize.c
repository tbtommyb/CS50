/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize a 24-bit uncompressed BMP
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    int scale = atoi(argv[1]);
    if(scale < 1 || scale > 100)
    {
        printf("1 <= scale <= 100\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
    
    // update new header fields
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int originalPadding =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    RGBTRIPLE* outputLine = malloc(sizeof(RGBTRIPLE) * bi.biWidth);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(originalHeight); i < biHeight; i++)
    {
        for (int j = 0; j < originalWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
    
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
            // write RGB triple to outfile
            for (int count = 0; count < scale; count++) {
                outputLine[(j * scale) + count] = triple;
            }
        }
        
        fseek(inptr, originalPadding, SEEK_CUR);
        for (int row = 0; row < scale; row++)
        {
            fwrite(outputLine, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    free(outputLine);

    // that's all folks
    return 0;
}
