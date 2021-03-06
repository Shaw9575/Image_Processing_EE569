//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image1.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256]


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "functions1.cpp"
#include <string>
#include <fstream>
#include <memory.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 100;
	int SizeW = 100;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeL = 640] [SizeW = 480]" << endl;
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
	int New_Image[SizeL][SizeW],imput_image[SizeL][SizeW],Image[SizeL][SizeW];
	memset(Image,0,sizeof(Image));
	memset(New_Image,0,sizeof(New_Image));
	unsigned char output_image[SizeL][SizeW][BytesPerPixel];
	int N = 3;
	int i,j,m,n,k,times,counthit,hit,hit2;
	
	

	//add a filter to remove the blured color
	for (i=0; i<SizeL; i++)
	{
		for (j=0; j<SizeW; j++)
		{
			if ((int)Imagedata[i][j][0] > 40)
			{
				imput_image[i][j] = 0;
			}
			else
			{
				imput_image[i][j] = 1;
			}
		}
	}

	//shrink the image
	for (times =0; times<100; times++)
	{
		counthit = 0;
		for (i=1; i<SizeL-1; i++)
		{
			for (j=1; j<SizeW-1; j++)
			{
				if (imput_image[i][j] == 1)
				{
					string st;
					for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    st+=to_string(imput_image[i+n-1][j+m-1]);
					    }
				    }
					hit = FirstStage_T(st);
					//generate the intermediate image
					if (hit == 1)
					{
						Image[i][j] = 1;
						counthit++;
					}
					else if (hit == 0)
					{
						Image[i][j] = 0;
					}
				    hit =0;
				}
				else if (imput_image[i][j] == 0)
				{
					Image[i][j] = 0;
				}	
			}
		}
		if (counthit == 0)
		{
			goto number0;
		}
		for (i=1; i<SizeL-1; i++)
		{
			for (j=1; j<SizeW-1; j++)
			{
				if (Image[i][j] == 1)
				{
					string s;
			    	for (m=0; m<N; m++)
			    	{
				    	for (n=0; n<N; n++)
				    	{
					    	s+=to_string(Image[i+n-1][j+m-1]);
				    	}
			    	}
					hit2=uncondition_ST(s);
					if (hit2 == 1)
					{
						New_Image[i][j]=imput_image[i][j];
					}
					else if(hit2 == 0)
					{
						New_Image[i][j]=0;
					}
					hit2=0;
				}
				else if (Image[i][j] == 0) 
			    {
				    New_Image[i][j]=imput_image[i][j];
			    }
			}
		}
		for (i=0; i<SizeL; i++)
	    {
		    for (j=0; j<SizeW; j++)
		    {
				imput_image[i][j]=New_Image[i][j];
			}
		}	
	}

	number0:
	for (i = 0; i<SizeL; i++)
	{
		for (j=0; j<SizeW; j++)
		{
			if (New_Image[i][j] == 1)
			{
				output_image[i][j][0] = (unsigned char) 0;
			}
			else
			{
				output_image[i][j][0] = (unsigned char) 255;
			}
		}
	}


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output_image, sizeof(unsigned char), SizeL*SizeW*BytesPerPixel, file);
	fclose(file);

	return 0;
}