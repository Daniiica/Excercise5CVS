/*
 * bmp.h
 *
 *  Created on: Jan 11, 2011
 *      Author: romans
 */

#ifndef BMP_H_
#define BMP_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define _CRT_SECURE_NO_DEPRECATE

#define BYTE  unsigned char
#define DWORD unsigned int
#define LONG  int
#define UINT  unsigned int
#define WORD  unsigned short int


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //specifies height in pixels
    WORD biPlanes;  //specifies the number of color planes, must be 1
    WORD biBitCount;  //specifies the number of bits per pixel
    DWORD biCompression;  //specifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by the bitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)

#pragma pack(push,1)
typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
}_RGBQUAD;

#pragma pack(pop)

unsigned char* LoadBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader,
    BITMAPINFOHEADER* bitmapInfoHeader);

int SaveBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader,
    BITMAPINFOHEADER* bitmapInfoHeader, unsigned char* bitmapImage);

int bitmapLinePadding(BITMAPINFOHEADER* bitmapInfoHeader);

#endif /* BMP_H_ */
