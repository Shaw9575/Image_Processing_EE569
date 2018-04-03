//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image1.raw imput_image2.raw imput_image3.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [SizeWidth = 256]

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "fileRead.cpp"
#include <math.h>
#include <cmath>
#include <vector>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 256;
	int SizeW = 256;
	char *filename;
	
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
		BytesPerPixel = atoi(argv[5]);
		// Check if size is specified
		if (argc >= 5){
			SizeL = atoi(argv[7]);
			SizeW = atoi(argv[6]);
		}
	}
	// Allocate image data array
	unsigned char Imagedata1[SizeL][SizeW][BytesPerPixel];
	unsigned char Imagedata2[SizeL][SizeW][BytesPerPixel];
	unsigned char Imagedata3[SizeL][SizeW][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	filename = argv[1];
	ReadImage(filename,&Imagedata1[0][0][0],BytesPerPixel,SizeL,SizeW);
	filename = argv[2];
	ReadImage(filename,&Imagedata2[0][0][0],BytesPerPixel,SizeL,SizeW);
	filename = argv[3];
	ReadImage(filename,&Imagedata3[0][0][0],BytesPerPixel,SizeL,SizeW);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int SizeL_output,SizeW_output;
	double H1[9] = {2.6271,0.0820,-737.4201,0.7403,2.2314,-273.1188,0.0027,0.0007,1};
	double H2[9] = {0.8926,-0.0788,210.1060,0.1858,0.7671,30.6607,0.0001,0.0003,1};
	vector<vector<double> > Length1(SizeL,vector<double>(SizeW));
	vector<vector<double> > Width1(SizeL,vector<double>(SizeW));
	vector<vector<double> > x_prime1(SizeL,vector<double>(SizeW));
	vector<vector<double> > y_prime1(SizeL,vector<double>(SizeW));
	vector<vector<double> > Length2(SizeL,vector<double>(SizeW));
	vector<vector<double> > Width2(SizeL,vector<double>(SizeW));
	vector<vector<double> > x_prime2(SizeL,vector<double>(SizeW));
	vector<vector<double> > y_prime2(SizeL,vector<double>(SizeW));
	double xyw1[3],xyw2[3];
	double minw,minl,maxw,maxl;
	int i,j,channel,col1,row1,col2,row2;

	//get the H implied in matrix
	for (i=0; i<SizeL;i++)
	{
		for (j=0; j<SizeW; j++)
		{
			Length1[i][j]=(double)i;
			Width1[i][j]=(double)j;
			xyw1[0] = H1[0]*Length1[i][j]+H1[1]*Width1[i][j]+H1[2];
			xyw1[1] = H1[3]*Length1[i][j]+H1[4]*Width1[i][j]+H1[5];
			xyw1[2] = H1[6]*Length1[i][j]+H1[7]*Width1[i][j]+H1[8];
			x_prime1[i][j] = xyw1[0]/xyw1[2];
			y_prime1[i][j] = xyw1[1]/xyw1[2];
		}
	}
	for (i=0; i<SizeL;i++)
	{
		for (j=0; j<SizeW; j++)
		{
			Length2[i][j]=(double)i;
			Width2[i][j]=(double)j;
			xyw2[0] = H2[0]*Length2[i][j]+H2[1]*Width2[i][j]+H2[2];
			xyw2[1] = H2[3]*Length2[i][j]+H2[4]*Width2[i][j]+H2[5];
			xyw2[2] = H2[6]*Length2[i][j]+H2[7]*Width2[i][j]+H2[8];
			x_prime2[i][j] = xyw2[0]/xyw2[2];
			y_prime2[i][j] = xyw2[1]/xyw2[2];
		}
	}
	//get the max and min position
	minl = x_prime1[0][0];
	minw = y_prime1[0][0];
	maxl = x_prime1[0][0];
	maxw = y_prime1[0][0];
	for (i=0; i<SizeL;i++)
	{
		for (j=0; j<SizeW; j++)
		{
			if (minl>x_prime1[i][j])
			{
				minl = x_prime1[i][j];
			}
			if (minw >y_prime1[i][j])
			{
				minw = y_prime1[i][j];
			}
			if (maxl < x_prime1[i][j])
			{
				maxl = x_prime1[i][j];
			}
			if (maxw < y_prime1[i][j])
			{
				maxw = y_prime1[i][j];
			}
			if (minl>x_prime2[i][j])
			{
				minl = x_prime2[i][j];
			}
			if (minw >y_prime2[i][j])
			{
				minw = y_prime2[i][j];
			}
			if (maxl < x_prime2[i][j])
			{
				maxl = x_prime2[i][j];
			}
			if (maxw < y_prime2[i][j])
			{
				maxw = y_prime2[i][j];
			}
		}
	}
	//move the image into the right position
	minl = abs(minl);
	minw = abs(minw);
	for (i=0; i<SizeL;i++)
	{
		for (j=0; j<SizeW; j++)
		{
			x_prime1[i][j] += minl;
			x_prime2[i][j] += minl;
			y_prime1[i][j] += minw;
			y_prime2[i][j] += minw;
		}
	}
	//map to new image
	SizeL_output = (int)(maxl+minl);
	SizeW_output = (int)(maxw+minw);
	unsigned char New_image[SizeL_output][SizeW_output][BytesPerPixel];
	memset(New_image,0,sizeof(New_image));
	for (channel=0; channel<BytesPerPixel; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				col1 = (int)x_prime1[i][j]; 
				row1 = (int)y_prime1[i][j];
				New_image[col1][row1][channel]=Imagedata1[i][j][channel];
			}
		}
	}
	for (channel=0; channel<BytesPerPixel; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				New_image[i+(int)minw][j+(int)minl][channel]=Imagedata2[i][j][channel];
			}
		}
	}
	for (channel=0; channel<BytesPerPixel; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				col2 = (int)x_prime2[i][j]; 
				row2 = (int)y_prime2[i][j];
				New_image[col2][row2][channel]=Imagedata3[i][j][channel];
			}
		}
	}
	
	cout <<SizeL_output<<',';
	cout<<SizeW_output<<endl;

	// Write image data (filename specified by second argument) from image data matrix
	filename = argv[4];
	WriteImage(filename, &New_image[0][0][0], BytesPerPixel, SizeL_output, SizeW_output);
	return 0;
}
