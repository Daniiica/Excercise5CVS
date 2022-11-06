/*
 ============================================================================
 Name        : e_bitmap.c
 Author      : rt-rk
 Version     :
 Copyright   : Your copyright notice
 Description : image processing example
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "imageProcessing.h"

#define __ARG_NUM__ 2

int main(int argc, char* argv[])
{
	//sledece 2 linije sam ja ubacila da zna odakle da cita sliku
	argc = 2;
	argv[1] = "Image.bmp";
	int err = 0;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char* bitmapData;

	if (argc != __ARG_NUM__)
	{
		printf("Enter input file path \n");
		return 1;
	}

	printf("Applying brightness\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if (!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return 1;
	}
/*	unsigned char* red = createOneCanal('r', bitmapData,
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
	free(red);
*/
	unsigned char* green = createOneCanal('g', bitmapData,
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
	free(green);

	float* resultOfMeanFilter = meanFilterPerColor(green,
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
	err = SaveBitmapFile("meanFilterGreen.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, resultOfMeanFilter);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	free(resultOfMeanFilter);
/*	unsigned char* blue = createOneCanal('b', bitmapData,
		bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight);
	free(blue);
*/
	Pixel pixel = { 0 };
	//averageValuePerColor
	//averageValuePerColor(bitmapData, bitmapInfoHeader.biWidth,
		//bitmapInfoHeader.biHeight, &pixel);


	//printf("Red %f, green %f, blue %f", pixel.red, pixel.green, pixel.blue);

	// Apply image brightness to image
	/*adjustImageBrightness(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, false, 70);

	err = SaveBitmapFile("out_brightness.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	printf("Applying dark image\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if (!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return 1;
	}

	darkenImage(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight);
	err = SaveBitmapFile("out_dark.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	printf("Applying effect\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if (!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return 1;
	}

	effect(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight);
	err = SaveBitmapFile("out_bw.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}*/
	free(bitmapData);

	return EXIT_SUCCESS;
}
