// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 1000;
	int SizeW = 750;
	int Chl;

	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			SizeL = atoi(argv[4]);
			SizeW = atoi(argv[5]);
		}
	}
	if (argc < 6)
	{
		Chl = 0; //default Color channel is Red
	}
	else 
	{
		Chl = atoi(argv[6]);
	}
	
	// Allocate image data array
	unsigned char Imagedata[SizeL][SizeW][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), SizeL*SizeW*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int channel,i,j,pixel_num,k;
	int count_pixels[3][256];
	int output[256];

	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				pixel_num = (int) Imagedata[i][j][channel];
				count_pixels[channel][pixel_num]++;
			}
		}
	}
	for (i=0; i<256; i++)
	{
		output[i]=count_pixels[Chl][i];
	}

	for (k=0; k<256; k++)
	{
		cout<<output[k]<<endl;
	}

	return 0;
}
