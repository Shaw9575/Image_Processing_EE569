//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [# Method]
//Method 1 ------> fixed thresholding
//Method 2 ------> random thresholding
//Method 3 ------> Dithering Matrix I2
//Method 4 ------> Dithering matrix I4
//Method 5 ------> Dithering matrix I8

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

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
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256] [Method = 1]" << endl;
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
	int i,j,m,n,p,q,thresholding,N;
	unsigned char New_Image[Size][Size][BytesPerPixel];
	int Window[N][N];
	int I2[2][2] = {{1,2},{3,0}}; //Initialize I2
	int I4[4][4] = {{5,9,6,10},{13,1,14,2},{7,11,4,8},{15,3,12,0}}; //Initialize I4
	int I8[8][8] = {{21,37,25,41,22,38,26,42},{53,5,57,9,54,6,58,10},{29,45,17,33,30,46,18,34},{61,13,49,1,62,14,50,2},{23,39,27,43,20,36,24,40},{55,7,59,11,52,4,56,8},{31,47,19,35,28,44,16,32},{63,15,51,3,60,12,48,0}};


	//Method 1 ------> fixed thresholding
	if (Method == 1)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				if ((int) Imagedata[i][j][0] > 127)
				{
					New_Image[i][j][0] = (unsigned char) 255;
				}
				else
				{
					New_Image[i][j][0] = (unsigned char) 0;
				}
			}
		}
	}

	//Method 2 ------> random thresholding
	if (Method == 2)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				if ((int) Imagedata[i][j][0]>= (rand()%255))
				{
					New_Image[i][j][0] = (unsigned char) 255;
				}
				else
				{
					New_Image[i][j][0] = (unsigned char) 0;
				}
			}
		}
	}

	//Method 3 ------> Dithering Matrix I2
	if (Method <6)
	{
		if (Method == 3)     //Dithering matrix I2
		{
			N = 2;
			for(i=0; i<Size; i+=N)
            {
                for(j=0; j<Size;  j+=N)
			    {
				    //Exstract Window data
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    Window[m][n]=(int)Imagedata[i+m][j+n][0];
					    }
				    }
				    //Arrange the threshholding matrix into new image
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    thresholding = (I2[m][n]*256+128)/(N*N)-1;
							if (Window[m][n] < thresholding)
							{
								New_Image[i+m][j+n][0] = (unsigned char) 0;
							}
							else 
							{
								New_Image[i+m][j+n][0] = (unsigned char) 255;
							}
						}
					}
				}
			}
		}
		if (Method == 4)    //Dithering matrix I4
		{
			N = 4;
			//Generating new dithering matrix I4
			for(i=0; i<Size; i+=N)
            {
                for(j=0; j<Size; j+=N)
			    {
				    //Exstract Window data
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    Window[m][n]=(int)Imagedata[i+m][j+n][0];
					    }
				    }
				    //Arrange the threshholding matrix into new image
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    thresholding = (I4[m][n]*256+128)/(N*N)-1;
							if (Window[m][n] < thresholding)
							{
								New_Image[i+m][j+n][0] = (unsigned char) 0;
							}
							else 
							{
								New_Image[i+m][j+n][0] = (unsigned char) 255;
							}
						}
					}
				}
			}
		}
		if (Method == 5)   //Dithering matrix I8
		{
			N = 8;
			//Generating new dithering matrix I8
			for(i=0; i<Size; i+=N)
            {
                for(j=0; j<Size; j+=N)
			    {
				    //Exstract Window data
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    Window[m][n]=(int)Imagedata[i+m][j+n][0];
					    }
				    }
				    //Arrange the threshholding matrix into new image
				    for (m=0; m<N; m++)
				    {
					    for (n=0; n<N; n++)
					    {
						    thresholding = (I8[m][n]*256+128)/(N*N)-1;
							if (Window[m][n] < thresholding)
							{
								New_Image[i+m][j+n][0] = (unsigned char) 0;
							}
							else 
							{
								New_Image[i+m][j+n][0] = (unsigned char) 255;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "Method number should be in 1 to 5" << endl;
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
