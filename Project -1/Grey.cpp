// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	int Method;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256][# Method]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 4){
			Size = atoi(argv[4]);
		}
	}
	//Choose the Method
	if (argc < 5)
	{
		Method = 1; //default is Method 1
	}
	else 
	{
		Method = atoi(argv[5]);
	}

	// Allocate image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i,j,channel;
	int val=0;
	int new_BytesPerPixel=1;
	unsigned char GreyImage1[Size][Size][new_BytesPerPixel], GreyImage2[Size][Size][new_BytesPerPixel],GreyImage3[Size][Size][new_BytesPerPixel];
	unsigned char Max[Size][Size][new_BytesPerPixel]; 
	unsigned char Min[Size][Size][new_BytesPerPixel];

	//Method 1
	for (i =0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			for (channel=0; channel<3; channel++)
			{
				Max[j][i][0]=Imagedata[i][j][0];
				Min[i][j][0]=Imagedata[i][j][0];
				if (Max[i][j][0]<Imagedata[i][j][channel])
				{
					Max[i][j][0]=Imagedata[i][j][channel];
				}
				if (Min[i][j][0]>Imagedata[i][j][channel])
				{
					Min[i][j][0]=Imagedata[i][j][channel];
				}
			}
			GreyImage1[i][j][new_BytesPerPixel]=(unsigned char)((int)Min[i][j][0]/2+(int)Max[i][j][0]/2);
		}
	}
	//Method 2
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			for (channel=0; channel<3; channel++)
			{
				val=(int)Imagedata[i][j][0]/3+(int)Imagedata[i][j][1]/3+(int)Imagedata[i][j][2]/3;
			}
			GreyImage2[i][j][new_BytesPerPixel]=(unsigned char)val;
		}
	}
	//Method 3
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			for (channel=0; channel<3; channel++)
			{
				val=(int)Imagedata[i][j][0]*0.21+(int)Imagedata[i][j][1]*0.72+(int)Imagedata[i][j][2]*0.07;
			}
			GreyImage3[i][j][new_BytesPerPixel]=(unsigned char)val;
		}
	}
	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	//Choose the method 
	if (Method == 1)
	{
		fwrite(GreyImage1, sizeof(unsigned char), Size*Size*new_BytesPerPixel, file);
	}
	else if (Method == 2)
	{
		fwrite(GreyImage2, sizeof(unsigned char), Size*Size*new_BytesPerPixel, file);
	}
	else if (Method == 3)
	{
		fwrite(GreyImage3, sizeof(unsigned char), Size*Size*new_BytesPerPixel, file);
	}
	fclose(file);

	return 0;
}
