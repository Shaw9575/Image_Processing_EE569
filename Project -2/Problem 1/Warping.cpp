//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image1.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256]

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fileRead.cpp"
#include <vector>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	int BytesPerPixel;
	int Size = 512;
	char *filename;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "g++ program_name";
		cout << "input_image.raw output_image.raw [BytesPerPixel = 3] [Size = 512]" << endl;
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
	
	// Allocate image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	filename = argv[1];
	ReadImage (filename,&Imagedata[0][0][0],BytesPerPixel,Size,Size);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	double paraL,paraW;
	unsigned char New_Image[Size][Size][BytesPerPixel];
	int i,j,channel;
	vector<vector<double> > Length(Size,vector<double>(Size));
	vector<vector<double> > Width(Size,vector<double>(Size));
	double half_size = ((double)Size-1)/2;

	//move to the middle of the image then use equations to change u,v to the x,y
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			Length[i][j]=(double)i-half_size;
			Width[i][j]=(double)j-half_size;
			paraL = sqrt(half_size*half_size-Width[i][j]*Width[i][j]/2)/half_size;
			paraW = sqrt(half_size*half_size-Length[i][j]*Length[i][j]/2)/half_size;
			Length[i][j]=Length[i][j]*paraL+half_size;
			Width[i][j]=Width[i][j]*paraW+half_size;
		}
	}

	//map it into new image
	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				New_Image[(int)Length[i][j]][(int)Width[i][j]][channel]=Imagedata[i][j][channel];
			}
		}
	}


	// Write image data (filename specified by second argument) from image data matrix

	filename = argv[2];
	WriteImage (filename, &New_Image[0][0][0],BytesPerPixel,Size,Size);

	return 0;
}
