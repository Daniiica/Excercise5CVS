#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct pixel
{
    float red;
    float green;
    float blue;
};

typedef struct pixel Pixel;

void darkenImage(unsigned char* imageData, int imageWidth, int imageHeight);

void adjustImageBrightness(unsigned char* iData, int iWidth, int iHeight,
    bool brighten, unsigned char adjustmentValue);

void effect(unsigned char* iData, int iWidth, int iHeight);

void averageValuePerColor(unsigned char* iData, int iWidth, int iHeight,
    Pixel* pixel);

float* meanFilterPerColor(unsigned char* colorData, int iWidth, int iHeight);

unsigned char* createOneCanal(char color, unsigned char* iData,
    int iWidth, int iHeight);

#endif /* IMAGEPROCESSING_H_ */
