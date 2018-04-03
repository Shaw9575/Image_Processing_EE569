//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/28/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [SizeWidth = 256]

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fileRead.cpp"

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	int BytesPerPixel;
	int SizeW = 256;
	int SizeL = 256;
	char *filename;
	double threshold = 0.15;
	
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
		BytesPerPixel = atoi(argv[4]);
		// Check if size is specified
		if (argc >= 4){
			SizeL = atoi(argv[5]);
			SizeW = atoi(argv[6]);
		}
	}

	// Allocate image data array
	unsigned char Imagedata[SizeW][SizeL][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	filename = argv[1];
	ReadImage(filename,&Imagedata[0][0][0],BytesPerPixel,SizeW,SizeL);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i,j,k,p,q,count,boundary;
	int N;
	double max,min,value;
	unsigned char output_image1[SizeW][SizeL],output_image2[SizeW][SizeL];
	int Gau[9][9] = {{0,1,1,2,2,2,1,1,0},{1,2,4,5,5,5,4,2,1},{1,4,5,3,0,3,5,4,1},{2,5,3,-12,-24,-12,3,5,2},{2,5,0,-24,-40,-24,0,5,2},{2,5,3,-12,-24,-12,3,5,2},{1,4,5,3,0,3,5,4,1},{1,2,4,5,5,5,4,2,1},{0,1,1,2,2,2,1,1,0}};
	int GreyImage[SizeW][SizeL],Extended_Width[SizeW][SizeL+N-1],Extended_Matrix[SizeW+N-1][SizeL+N-1],Gaussian[SizeW][SizeL];
	int Image[SizeW][SizeL];


	//change image into grey color (use Hw1 problem1 method3)
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			GreyImage[i][j]=(int)(Imagedata[i][j][0]*0.21+Imagedata[i][j][1]*0.72+Imagedata[i][j][2]*0.07);
		}
	}
	//Matrix Extension
	N = 9;
	for (i=0; i<SizeW; i++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Width[i][(N-1)/2-k]=GreyImage[i][k];
			Extended_Width[i][SizeL+(N-1)/2+k-1]=GreyImage[i][SizeL-1-k];
		}
	}
	// Fill in the rest unchanged part of original image
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			Extended_Width[i][j+(N-1)/2]=GreyImage[i][j];
		}
	}
	//Then, extended length
	for (j=0; j<SizeL+N-1; j++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Matrix[(N-1)/2-k][j]=Extended_Width[k][j];
			Extended_Matrix[SizeW+(N-1)/2+k-1][j]=Extended_Width[SizeW-1-k][j];
		}
	}
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL+N-1; j++)
		{
	    	Extended_Matrix[i+(N-1)/2][j]=Extended_Width[i][j];
		}
	}
	//Calculate the Gaussian mask
	for(i=(N-1)/2; i<SizeW+(N-1)/2; i++) 
	{
        for(j=(N-1)/2; j<SizeL+(N-1)/2; j++) 
		{
			value = 0;
            for(p=0; p<N; p++)
			{
                for(q=0; q<N; q++) 
				{
					value += Extended_Matrix[i-(N-1)/2+p][j-(N-1)/2+q]*Gau[p][q];
				}
            }
			Gaussian[i-(N-1)/2][j-(N-1)/2] = value;
        }
    }

	
	//Normalization
	max = Gaussian[0][0];
	min = Gaussian[0][0];
	for(i=0; i<SizeW; i++) 
	{
		for(j=0; j<SizeL; j++) 
		{
			if (Gaussian[i][j]>max) 
			{
				max = Gaussian[i][j];
			}
			if (Gaussian[i][j]<min) 
			{
				min = Gaussian[i][j];
			}
		}
	}
	for(i=0; i<SizeW; i++) 
	{
		for (j=0; j<SizeL; j++)
		{
			GreyImage[i][j]=(int)(255*(Gaussian[i][j]-min)/(max-min));
		}
	}
	for(i=0; i<SizeW; i++) 
	{
		for (j=0; j<SizeL; j++)
		{
			if (GreyImage[i][j]<137)
			{
				GreyImage[i][j] = 64;
				Image[i][j] = -1;
			}
			if (GreyImage[i][j]>141)
			{
				GreyImage[i][j] = 192;
				Image[i][j] = 1;
			}
			if ((GreyImage[i][j]>136)&&(GreyImage[i][j]<142))
			{
				GreyImage[i][j] = 128;
				Image[i][j] = 0;
			}
		}
	}
	for(i=0; i<SizeW; i++) 
	{
		for (j=0; j<SizeL; j++)
		{
			output_image2[i][j]=(unsigned char)GreyImage[i][j];
		}
	}
	for(i=0; i<SizeW; i++) 
	{
		for (j=0; j<SizeL; j++)
		{
			output_image1[i][j]=(unsigned char)255;
		}
	}
	//detect zero crossing
	for(i=1; i<SizeW-1; i++) 
	{
		for (j=1; j<SizeL-1; j++)
		{
			if (GreyImage[i][j]>128)
			{
				if ((Image[i-1][j]*Image[i+1][j]<0)||(Image[i][j-1]*Image[i][j+1]<0)||(Image[i-1][j-1]*Image[i+1][j+1]<0)||(Image[i+1][j-1]*Image[i-1][j+1]<0))
				{
					output_image1[i][j] = (unsigned char) 0;
				}
				else
				{
					output_image1[i][j] = (unsigned char) 255;
				}
			}
		}
	}
	// Write image data (filename specified by second argument) from image data matrix

	filename  = argv[2];
	WriteImage(filename, &output_image1[0][0],1,SizeW,SizeL);
	filename  = argv[3];
	WriteImage(filename, &output_image2[0][0],1,SizeW,SizeL);

	return 0;
}