/*
 * Copyright 1993-2013 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#   pragma warning( disable : 4996 ) // disable deprecated warning 
#endif

#pragma pack(1)

typedef struct
{
    short type;
    int size;
    short reserved1;
    short reserved2;
    int offset;
} BMPHeader;

typedef struct
{
    int size;
    int width;
    int height;
    short planes;
    short bitsPerPixel;
    unsigned compression;
    unsigned imageSize;
    int xPelsPerMeter;
    int yPelsPerMeter;
    int clrUsed;
    int clrImportant;
} BMPInfoHeader;

//Isolated definition
// typedef struct
// {
//     unsigned char x, y, z, w;
// } uchar4;


void LoadBMPFile(unsigned char **dst,  int *width,
                             int *height, const char *name)
{
    BMPHeader hdr;
    BMPInfoHeader infoHdr;
    int x, y;
    FILE *fd = NULL;

    printf("Loading %s...\n", name);
     if (!(fd = fopen(name,"r+")))
    {
        printf("***BMP load error: file access denied***\n");
        exit(EXIT_SUCCESS);
    }

    fread(&hdr, sizeof(hdr), 1, fd);
    printf("head_length:%ld\n",sizeof(hdr));
    if (hdr.type != 0x4D42)
    {
        printf("***BMP load error: bad file format***\n");
        exit(EXIT_SUCCESS);
    }

    fread(&infoHdr, sizeof(infoHdr), 1, fd);
    printf("info_length:%ld\n",sizeof(infoHdr));
    if (infoHdr.bitsPerPixel != 24)
    {
        printf("depth:%d",infoHdr.bitsPerPixel);
        printf("***BMP load error: invalid color depth***\n");
        exit(EXIT_SUCCESS);
    }

    if (infoHdr.compression)
    {
        printf("***BMP load error: compressed image***\n");
        exit(EXIT_SUCCESS);
    }

    *width  = infoHdr.width;
    *height = infoHdr.height;
    *dst    = (unsigned char *)malloc(*width * *height * 4);

    printf("BMP width: %u\n", infoHdr.width);
    printf("BMP height: %u\n", infoHdr.height);

    fseek(fd, hdr.offset - sizeof(hdr) - sizeof(infoHdr), SEEK_CUR);

    for (y = 0; y < infoHdr.height; y++)
    {
        for (x = 0; x < infoHdr.width; x++)
        {
            (*dst)[4*(y * infoHdr.width + x)+3] = 0;
            (*dst)[4*(y * infoHdr.width + x)+2] = fgetc(fd);
            (*dst)[4*(y * infoHdr.width + x)+1] = fgetc(fd);
            (*dst)[4*(y * infoHdr.width + x)] = fgetc(fd);

        }

        for (x = 0; x < (4 - (3 * infoHdr.width) % 4) % 4; x++)
        {
            fgetc(fd);
        }
    }

    if (ferror(fd))
    {
        printf("***Unknown BMP load error.***\n");
        free(*dst);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("BMP file loaded successfully!\n");
    }

    fclose(fd);
}
