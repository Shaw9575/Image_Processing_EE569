//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [# Method]
//Method 1 ------> Floyd-Steinberg
//Method 2 ------> JJN
//Method 3 ------> Stucki

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 512;
	int Method = 1;
	
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
			Size = atoi(argv[4]);
		}
	}
	if (argc < 5)
	{
		Method = 1; //default method is fixed thresholding
	}
	else
	{
		Method = atoi (argv[5]);
	}
	if (Method > 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "Method number should be in 1 to 3" << endl;
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
	int i,j,k,N,error;
	unsigned char Extended_Width[Size][Size+N-1] [BytesPerPixel];
	unsigned char Extended_Matrix[Size+N-1][Size+N-1][BytesPerPixel];
	unsigned char New_Image[Size][Size][BytesPerPixel];

	if (Method == 1)
	{
		N = 3;
		//Matrix Extension
		for (i=0; i<Size; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width[i][(N-1)/2-k][0]=Imagedata[i][k][0];
				Extended_Width[i][Size+(N-1)/2+k-1][0]=Imagedata[i][Size-1-k][0];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				Extended_Width[i][j+(N-1)/2][0]=Imagedata[i][j][0];
			}
		}
		//Then, extended length
		for (j=0; j<Size+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix[(N-1)/2-k][j][0]=Extended_Width[k][j][0];
				Extended_Matrix[Size+(N-1)/2+k-1][j][0]=Extended_Width[Size-1-k][j][0];
			}
		}
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size+N-1; j++)
			{
				Extended_Matrix[i+(N-1)/2][j][0]=Extended_Width[i][j][0];
			}
		}
		// scan every points to get result image
		for (i=(N-1)/2; i<Size+(N-1)/2; i++)
		{
			for (j=(N-1)/2; j<Size+(N-1)/2; j++)
			{
				//Arrange data to new greyscale
				if ((int)Extended_Matrix[i][j][0]<128)
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 0;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				else
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 255;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				//Rearrange the error
				Extended_Matrix[i+1][j][0] = (unsigned char) ((int)Extended_Matrix[i+1][j][0]+ (int)(error*7/16));
				Extended_Matrix[i+1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i+1][j+1][0]+ (int)(error*1/16));
				Extended_Matrix[i][j+1][0] = (unsigned char) ((int)Extended_Matrix[i][j+1][0]+ (int)(error*5/16));
				Extended_Matrix[i-1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i-1][j+1][0]+ (int)(error*3/16));
			}
		}
	}

	if (Method == 2)
	{
		N = 5;
		//Matrix Extension
		for (i=0; i<Size; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width[i][(N-1)/2-k][0]=Imagedata[i][k][0];
				Extended_Width[i][Size+(N-1)/2+k-1][0]=Imagedata[i][Size-1-k][0];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				Extended_Width[i][j+(N-1)/2][0]=Imagedata[i][j][0];
			}
		}
		//Then, extended length
		for (j=0; j<Size+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix[(N-1)/2-k][j][0]=Extended_Width[k][j][0];
				Extended_Matrix[Size+(N-1)/2+k-1][j][0]=Extended_Width[Size-1-k][j][0];
			}
		}
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size+N-1; j++)
			{
				Extended_Matrix[i+(N-1)/2][j][0]=Extended_Width[i][j][0];
			}
		}
		// scan every points to get result image
		for (i=(N-1)/2; i<Size+(N-1)/2; i++)
		{
			for (j=(N-1)/2; j<Size+(N-1)/2; j++)
			{
				//Arrange data to new greyscale
				if ((int)Extended_Matrix[i][j][0]<128)
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 0;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				else
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 255;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				//Rearrange the error
				Extended_Matrix[i+1][j][0] = (unsigned char) ((int)Extended_Matrix[i+1][j][0]+ (int)(error*7/48));
				Extended_Matrix[i+2][j][0] = (unsigned char) ((int)Extended_Matrix[i+2][j][0]+ (int)(error*5/48));
				Extended_Matrix[i-2][j+1][0] = (unsigned char) ((int)Extended_Matrix[i-2][j+1][0]+ (int)(error*3/48));
				Extended_Matrix[i+2][j+1][0] = (unsigned char) ((int)Extended_Matrix[i+2][j+1][0]+ (int)(error*3/48));
				Extended_Matrix[i+1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i+1][j+1][0]+ (int)(error*5/48));
				Extended_Matrix[i][j+1][0] = (unsigned char) ((int)Extended_Matrix[i][j+1][0]+ (int)(error*7/48));
				Extended_Matrix[i-1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i-1][j+1][0]+ (int)(error*5/48));
				Extended_Matrix[i+2][j+2][0] = (unsigned char) ((int)Extended_Matrix[i+2][j+2][0]+ (int)(error*1/48));
				Extended_Matrix[i+1][j+2][0] = (unsigned char) ((int)Extended_Matrix[i+1][j+2][0]+ (int)(error*3/48));
				Extended_Matrix[i][j+2][0] = (unsigned char) ((int)Extended_Matrix[i][j+2][0]+ (int)(error*5/48));
				Extended_Matrix[i-1][j+2][0] = (unsigned char) ((int)Extended_Matrix[i-1][j+2][0]+ (int)(error*3/48));
				Extended_Matrix[i-2][j+2][0] = (unsigned char) ((int)Extended_Matrix[i-2][j+2][0]+ (int)(error*1/48));
			}
		}
	}

	if (Method == 3)
	{
		N = 5;
		//Matrix Extension
		for (i=0; i<Size; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width[i][(N-1)/2-k][0]=Imagedata[i][k][0];
				Extended_Width[i][Size+(N-1)/2+k-1][0]=Imagedata[i][Size-1-k][0];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				Extended_Width[i][j+(N-1)/2][0]=Imagedata[i][j][0];
			}
		}
		//Then, extended length
		for (j=0; j<Size+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix[(N-1)/2-k][j][0]=Extended_Width[k][j][0];
				Extended_Matrix[Size+(N-1)/2+k-1][j][0]=Extended_Width[Size-1-k][j][0];
			}
		}
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size+N-1; j++)
			{
				Extended_Matrix[i+(N-1)/2][j][0]=Extended_Width[i][j][0];
			}
		}
		// scan every points to get result image
		for (i=(N-1)/2; i<Size+(N-1)/2; i++)
		{
			for (j=(N-1)/2; j<Size+(N-1)/2; j++)
			{
				//Arrange data to new greyscale
				if ((int)Extended_Matrix[i][j][0]<128)
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 0;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				else
				{
					New_Image[i-(N-1)/2][j-(N-1)/2][0] = (unsigned char) 255;
					error = (int)Extended_Matrix[i][j][0] - (int)New_Image[i-(N-1)/2][j-(N-1)/2][0];
				}
				//Rearrange the error
				Extended_Matrix[i+1][j][0] = (unsigned char) ((int)Extended_Matrix[i+1][j][0]+ (int)(error*8/42));
				Extended_Matrix[i+2][j][0] = (unsigned char) ((int)Extended_Matrix[i+2][j][0]+ (int)(error*4/42));
				Extended_Matrix[i-2][j+1][0] = (unsigned char) ((int)Extended_Matrix[i-2][j+1][0]+ (int)(error*2/42));
				Extended_Matrix[i+2][j+1][0] = (unsigned char) ((int)Extended_Matrix[i+2][j+1][0]+ (int)(error*2/42));
				Extended_Matrix[i+1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i+1][j+1][0]+ (int)(error*4/42));
				Extended_Matrix[i][j+1][0] = (unsigned char) ((int)Extended_Matrix[i][j+1][0]+ (int)(error*8/42));
				Extended_Matrix[i-1][j+1][0] = (unsigned char) ((int)Extended_Matrix[i-1][j+1][0]+ (int)(error*4/42));
				Extended_Matrix[i+2][j+2][0] = (unsigned char) ((int)Extended_Matrix[i+2][j+2][0]+ (int)(error*1/42));
				Extended_Matrix[i+1][j+2][0] = (unsigned char) ((int)Extended_Matrix[i+1][j+2][0]+ (int)(error*2/42));
				Extended_Matrix[i][j+2][0] = (unsigned char) ((int)Extended_Matrix[i][j+2][0]+ (int)(error*4/42));
				Extended_Matrix[i-1][j+2][0] = (unsigned char) ((int)Extended_Matrix[i-1][j+2][0]+ (int)(error*2/42));
				Extended_Matrix[i-2][j+2][0] = (unsigned char) ((int)Extended_Matrix[i-2][j+2][0]+ (int)(error*1/42));
			}
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(New_Image, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
