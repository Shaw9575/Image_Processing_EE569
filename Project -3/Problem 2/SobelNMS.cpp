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
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 4){
			SizeL = atoi(argv[4]);
			SizeW = atoi(argv[5]);
		}
	}

	// Allocate image data array
	unsigned char Imagedata[SizeW][SizeL][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	filename = argv[1];
	ReadImage(filename,&Imagedata[0][0][0],BytesPerPixel,SizeW,SizeL);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int i,j,k,val,color,count,boundary;
	int N = 3;
	double magnitude,dx,dy,max,min;
	double Gradient[SizeW][SizeL],degree[SizeW][SizeL];
	int GreyImage[SizeW][SizeL],Extended_Width[SizeW][SizeL+N-1],Extended_Matrix[SizeW+N-1][SizeL+N-1];
	unsigned char output_image[SizeW][SizeL];
	int height[SizeW*SizeL],width[SizeW*SizeL];

	//change image into grey color (use Hw1 problem1 method3)
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			val=(int)Imagedata[i][j][0]*0.21+(int)Imagedata[i][j][1]*0.72+(int)Imagedata[i][j][2]*0.07;
			GreyImage[i][j]=val;
		}
	}
	//Matrix Extension
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
	//calculate gradient magnitude
	for(i=(N-1)/2; i<SizeW+(N-1)/2; i++) 
	{
		for(j=(N-1)/2; j<SizeL+(N-1)/2; j++) 
		{
			dx = (Extended_Matrix[i-1][j+1]+2*Extended_Matrix[i][j+1]+Extended_Matrix[i+1][j+1]-Extended_Matrix[i-1][j-1]-2*Extended_Matrix[i][j-1]-Extended_Matrix[i+1][j-1])/4;
			dy = (Extended_Matrix[i-1][j-1]+2*Extended_Matrix[i-1][j]+Extended_Matrix[i-1][j+1]-Extended_Matrix[i+1][j-1]-2*Extended_Matrix[i+1][j]-Extended_Matrix[i+1][j+1])/4;
			magnitude = sqrt(dx*dx+dy*dy);
			Gradient[i-(N-1)/2][j-(N-1)/2]=magnitude;
			degree[i-(N-1)/2][j-(N-1)/2]=dy/dx;
		}
	}
	//Normalization
	max = Gradient[0][0];
	min = Gradient[0][0];
	for(i=0; i<SizeW; i++) 
	{
		for(j=0; j<SizeL; j++) 
		{
			if (Gradient[i][j]>max) 
			{
				max = Gradient[i][j];
			}
			if (Gradient[i][j]<min) 
			{
				min = Gradient[i][j];
			}
		}
	}
	for(i=0; i<SizeW; i++) 
	{
		for (j=0; j<SizeL; j++)
		{
			GreyImage[i][j]=(int)(255*(Gradient[i][j]-min)/(max-min));
		}
	}
	//Rearrange the image
	count = 0;
	for(color=0; color<256; color++)
	{
		for(i=0; i<SizeW; i++) 
		{
			for(j=0; j<SizeL; j++) 
			{
			    if(GreyImage[i][j]==color)
			    {
				    height[count]=i;
				    width[count]=j;
				    count++;
			    }
		    }
		}
	}
	boundary = (int)((1-threshold)*SizeW*SizeL);
	for(i=0; i<boundary; i++)
	{
		output_image[height[i]][width[i]] = (unsigned char)255;
	}
	for(i=boundary; i<SizeW*SizeL; i++)
	{ 
		if(degree[height[i]][width[i]]<1) 
		{
			if (GreyImage[height[i]][width[i]] > GreyImage[height[i]][width[i] - 1] && GreyImage[height[i]][width[i]] > GreyImage[height[i]][width[i] + 1]) 
			{
				output_image[height[i]][width[i]] = (unsigned char) 0;
			}
			else 
			{
				output_image[height[i]][width[i]] = (unsigned char) 255;
			}
		}
		else
		{
			if (GreyImage[height[i]][width[i]] > GreyImage[height[i]-1][width[i]] && GreyImage[height[i]][width[i]] > GreyImage[height[i] + 1][width[i]]) 
			{
				output_image[height[i]][width[i]] = (unsigned char) 0;
			}
			else 
			{
				output_image[height[i]][width[i]] = (unsigned char) 255;
			}
		}
	}
	
	// Write image data (filename specified by second argument) from image data matrix

	filename  = argv[2];
	WriteImage(filename, &output_image[0][0],1,SizeW,SizeL);

	return 0;
}