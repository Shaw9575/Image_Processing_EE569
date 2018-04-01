//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 02/04/2018

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
	int N = 5;
	double sigma1 = 3, sigma2 = 100;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256][Window Size = 5][Sigma = 3]" << endl;
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
	if (argc >= 5)
	{
		N = atoi (argv[5]);
	}
	if (argc >= 5)
	{
		sigma1 = atoi (argv[6]);
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
	unsigned char Extended_Width[Size][Size+N-1] [BytesPerPixel];
	unsigned char Extended_Matrix[Size+N-1][Size+N-1][BytesPerPixel];
	unsigned char Filtered_image[Size][Size][BytesPerPixel];
	int i,j,k,m,n,channel,x;
	double data,val;
	int Window[N][N];

	//Matrix Extension
	for (channel=0; channel<BytesPerPixel; channel++)
	{
		//Firstly, extended width
		for (i=0; i<Size; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width[i][(N-1)/2-k][channel]=Imagedata[i][k][channel];
				Extended_Width[i][Size+(N-1)/2+k-1][channel]=Imagedata[i][Size-1-k][channel];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				Extended_Width[i][j+(N-1)/2][channel]=Imagedata[i][j][channel];
			}
		}
		//Then, extended length
		for (j=0; j<Size+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix[(N-1)/2-k][j][channel]=Extended_Width[k][j][channel];
				Extended_Matrix[Size+(N-1)/2+k-1][j][channel]=Extended_Width[Size-1-k][j][channel];
			}
		}
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size+N-1; j++)
			{
				Extended_Matrix[i+(N-1)/2][j][channel]=Extended_Width[i][j][channel];
			}
		}
	}

	//Gaussian Filter
	for(channel=0;channel<BytesPerPixel;channel++)
    {
        for(i=(N-1)/2;i<Size+(N-1)/2;i++)
        {
            for(j=(N-1)/2;j<Size+(N-1)/2;j++)
			{
				//Exstract Window data
				for (m=0; m<N; m++)
				{
					for (n=0; n<N; n++)
					{
						Window[m][n]=(int)Extended_Matrix[i-(N-1)/2+m][j-(N-1)/2+n][channel];
					}
				}
				data = 0;
				val = 0;
				for (m=0; m<(N+1)/2; m++)
				{
					for (n=0; n<(N+1)/2; n++)
					{
                        x = Window[(N-1)/2+m][(N-1)/2+n] - Window[(N-1)/2][(N-1)/2];
                        data += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1))*Window[(N-1)/2+m][(N-1/2)+n];
                        val += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1));
                        x = Window[(N-1)/2+m][(N-1)/2-n] - Window[(N-1)/2][(N-1)/2];
                        data += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1))*Window[(N-1)/2+m][(N-1/2)-n];
                        val += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1));
                        x = Window[(N-1)/2-m][(N-1)/2+n] - Window[(N-1)/2][(N-1)/2];
                        data += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1))*Window[(N-1)/2-m][(N-1/2)+n];
                        val += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1));
                        x = Window[(N-1)/2-m][(N-1)/2-n] - Window[(N-1)/2][(N-1)/2];
                        data += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1))*Window[(N-1)/2-m][(N-1/2)-n];
                        val += exp(-1*x*x/(2*sigma2*sigma2))*exp(-1*(m*m+n*n)/(2*sigma1*sigma1));
                    }
					Filtered_image[i-(N-1)/2][j-(N-1)/2][channel]=(unsigned char)(data/val);
				}
			}
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Filtered_image, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
