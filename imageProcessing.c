#ifndef IMAGEPROCESSING_C
#define IMAGEPROCESSING_C


#include "imageProcessing.h"
#include "bmp.h"

#define BW_TRESHOLD 128
const unsigned char darkenFactor = 192;
const int brightnessMinimum = 20;
const int brightnessMaximum = 220;

unsigned char* createOneCanal(char color, unsigned char* iData, int iWidth, int iHeight)
{
    int numOfPixels = iWidth * iHeight;
    unsigned char* canal = (unsigned char*)malloc(numOfPixels);
    //int* canal = malloc(sizeof(int) * numOfPixels);
    unsigned char* ptr = iData;
    if (color == 'g')
        ptr += 1;
    if (color == 'b')
        ptr += 2;
    for (int i = 0; i < numOfPixels; i++)
    {
        canal[i] = *ptr;
        ptr += 3;
    }
    return canal;
}

float* meanFilterPerColor(unsigned char* colorData, int iWidth, int iHeight)
{
    float* meanFilterResult = (float*)malloc(sizeof(float) * iWidth * iHeight);
    unsigned char* ptr = colorData;

    for (int i = 0; i < iWidth * iHeight; i++)
    {
        int rowIndex = i / iWidth;
        int colIndex = i % iWidth;
        meanFilterResult[i] = 0;

        for (int row = -1; row <= 1; row++)
        {
            for (int col = -1; col <= 1; col++)
            {
                if (!((rowIndex + row < 0 || rowIndex + row > iHeight) ||
                    (colIndex + col < 0 || colIndex + col > iWidth)))
                {
                    int indexOfData = (row + rowIndex) * iHeight + (colIndex + col);
                    meanFilterResult[i] += (float)ptr[indexOfData];
                    //printf("MeanFilterResult[i] is %f, ptr[i] is %d", meanFilterResult[i], ptr[indexOfData]);
                }
            }
        }
        meanFilterResult[i] /= 9;
    }
    return meanFilterResult;
}

void averageValuePerColor(unsigned char* iData, int iWidth,
    int iHeight, Pixel* pixel)
{
    unsigned char* ptr = iData;
    for (int i = 0; i < iHeight; i++)
    {
        for (int j = 0; j < iWidth; j++)
        {
            pixel->red += *ptr;
            pixel->green += *(++ptr);
            pixel->blue += *(++ptr);
            ++ptr;
        }
    }
    pixel->red /= (iWidth * iHeight);
    pixel->green /= (iWidth * iHeight);
    pixel->blue /= (iWidth * iHeight);
}
/*
unsigned char* meanFilterPerColor(unsigned char* colorData, int iWidth, int iHeight)
{
    unsigned char* ptr = colorData;
    unsigned char* resultOfFilter = (unsigned char*)malloc(iWidth * iHeight);
    int rowIndex = 0;
    int colIndex = 0;
    for (int arrayIndex = 0; arrayIndex < iHeight * iWidth; arrayIndex++)
    {
        rowIndex = arrayIndex / iHeight;
        colIndex = arrayIndex % iWidth;

        for (int l = -1; l < 1; l++)
        {
            for (int g = -1; g < 1; g++)
            {
                int neighborRowIndex = rowIndex + l;
                int neighborColIndex = colIndex + g;
                if (!((neighborRowIndex < 0 || neighborRowIndex > iHeight) ||
                    (neighborColIndex < 0 || neighborColIndex > iWidth)))
                {
                    int neighborIndex = neighborRowIndex * iWidth + neighborColIndex;
                    resultOfFilter[arrayIndex] += ptr[neighborIndex];
                }
            }
        }
        resultOfFilter[arrayIndex] /= 9;
    }
    return resultOfFilter;
}
*/
void darkenImage(unsigned char* iData, int iWidth, int iHeight)
{
    int i;
    int j;
    unsigned char* ptr = iData;

    for (i = 0; i < iHeight; i++)
    {
        for (j = 0; j < iWidth; j++)
        {
            *ptr = *ptr + darkenFactor;
            ptr++;
            *ptr = *ptr + darkenFactor;
            ptr += 1;
            *ptr = *ptr + darkenFactor;
            ptr += 1;
        }
    }
}

void adjustImageBrightness(unsigned char* iData, int iWidth, int iHeight,
    bool brighten, unsigned char adjustmentValue)
{
    int i;
    int newValue;

    for (i = 0; i < iWidth * iHeight * 3; i++)
    {
        newValue = iData[i];
        if (brighten)
        {
            newValue += adjustmentValue;
        }
        else
        {
            newValue -= adjustmentValue;
        }

        if (newValue < brightnessMinimum)
        {
            newValue = brightnessMinimum;
        }
        else if (newValue > brightnessMaximum)
        {
            newValue = brightnessMaximum;
        }

        iData[i] = newValue;
    }
}

void effect(unsigned char* iData, int iWidth, int iHeight)
{
    unsigned char* ptr = iData;
    int i;
    int j;
    int k;

    for (i = 0; i < iHeight; i++)
    {
        for (j = 0; j < iWidth; j++)
        {
            for (k = 0; k < 3; k++)
            {
                if (*(ptr + k) > BW_TRESHOLD)
                {
                    *(ptr + k) = 255;
                }
                else
                {
                    *(ptr + k) = 0;
                }
            }
            ptr += 3;
        }
    }
}

#endif // IMAGEPROCESSING_C
