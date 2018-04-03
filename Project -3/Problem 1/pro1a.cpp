//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/28/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256] 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fileRead.cpp"
#include "functions.cpp"

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 700;
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
	ReadImage(filename,&Imagedata[0][0][0],BytesPerPixel,Size,Size);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int N = 5;
	int Extended_Width[Size][Size+N-1],Extended_Matrix[Size+N-1][Size+N-1];
	int Image[Size][Size];
	int i,j,k,m,n,x,y,p,q,channel,type;
	double mean,sum,energy,value;
	double Result[9];
	double filters[3][5] = {{-0.166667,-0.33333,0,0.33333,0.166667},{-0.25,0,0.5,0,-0.25},{-0.166667,0.33333,0,-0.33333,0.166667}};
	double Matrix[5][5];

	// change unsigned char into integer
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			Image[i][j] = (int) Imagedata[i][j][0]; 
		}
	}

	//Matrix Extension
	//Firstly, extended width
	for (i=0; i<Size; i++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Width[i][(N-1)/2-k]=Image[i][k];
			Extended_Width[i][Size+(N-1)/2+k-1]=Image[i][Size-1-k];
		}
	}
	// Fill in the rest unchanged part of original image
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			Extended_Width[i][j+(N-1)/2]=Image[i][j];
		}
	}
	//Then, extended length
	for (j=0; j<Size+N-1; j++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Matrix[(N-1)/2-k][j]=Extended_Width[k][j];
			Extended_Matrix[Size+(N-1)/2+k-1][j]=Extended_Width[Size-1-k][j];
		}
	}
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size+N-1; j++)
		{
	    	Extended_Matrix[i+(N-1)/2][j]=Extended_Width[i][j];
		}
	}
	
	//get the first mean
	for (i=(N-1)/2; i<Size+(N-1)/2; i++)
    {
        for (j=(N-1)/2; j<Size+(N-1)/2; j++)
        {
			sum = 0;
            for (m=0; m<N; m++)
			{
				for (n=0; n<N; n++)
				{
					sum += Extended_Matrix[i-(N-1)/2+m][j-(N-1)/2+n];
				}
			}
			mean = sum/(N*N);
			Image[i-(N-1)/2][j-(N-1)/2] = Image[i-(N-1)/2][j-(N-1)/2] - (int)mean;
        }
    }

	//Matrix Extension
	for (i=0; i<Size; i++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Width[i][(N-1)/2-k]=Image[i][k];
			Extended_Width[i][Size+(N-1)/2+k-1]=Image[i][Size-1-k];
		}
	}
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size; j++)
		{
			Extended_Width[i][j+(N-1)/2]=Image[i][j];
		}
	}
	for (j=0; j<Size+N-1; j++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Matrix[(N-1)/2-k][j]=Extended_Width[k][j];
			Extended_Matrix[Size+(N-1)/2+k-1][j]=Extended_Width[Size-1-k][j];
		}
	}
	for (i=0; i<Size; i++)
	{
		for (j=0; j<Size+N-1; j++)
		{
	    	Extended_Matrix[i+(N-1)/2][j]=Extended_Width[i][j];
		}
	}

	//Using Laws Filters
	// filtering using Laws' filter banks
	type = 0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
			energy = 0;
            for(x=0; x<5; x++)
            {
                for(y=0; y<5; y++)
                {
                    Matrix[x][y] = filters[i][x]*filters[j][y];
                }
			}
            for(m=(N-1)/2; m<Size+(N-1)/2; m++) 
			{
                for(n=(N-1)/2; n<Size+(N-1)/2; n++) 
				{
					value = 0;
                    for(p=0; p<N; p++)
					{
                        for(q=0; q<N; q++) 
						{
							value += Extended_Matrix[m-(N-1)/2+p][n-(N-1)/2+q]*Matrix[p][q];
						}
                    }
					energy += value*value;
                }
            }
			Result[type] = energy/(Size*Size);
            type++;
        }
    }
	for (i=0; i<9; i++)
	{
		cout<<Result[i]<<',';
	}
	cout<<endl;

	return 0;
}
