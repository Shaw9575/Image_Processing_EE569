//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 02/04/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256][SizeWidth = 256][# Method]

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 512;
	int SizeW = 512; //default is 512 by 512 image
	int Method;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256][SizeWidth = 256][# Method]" << endl;
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
	//Choose the Method
	if (argc < 6)
	{
		Method = 1; //default is Method 1
	}
	else 
	{
		Method = atoi(argv[6]);
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

	int Image_channel[SizeL][SizeW][BytesPerPixel];
	unsigned char Image_trans[SizeL][SizeW][BytesPerPixel];
	unsigned char Image_cumul[SizeL][SizeW][BytesPerPixel];
	int i,j,color,channel,pixel_num,sum,val,m,n,step,sumc;
	int count_pixels[3][256]={0};
	int sum_pixels[3][256]={0};
	int Height[SizeL*SizeW],Width[SizeL*SizeW];

	for(channel=0;channel<3;channel++)
    {
        for(i=0;i<SizeL;i++)
        {
            for(j=0;j<SizeW;j++)
            {
                Image_channel[i][j][channel]=(int)Imagedata[i][j][channel];
            }
        }
    }

	// count the number of each pixel value
	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				pixel_num = Image_channel[i][j][channel];
				count_pixels[channel][pixel_num]++;
			}
		}
	}

	//tranfer function
	for(channel=0; channel<3; channel++)
    {
        for(i=0; i<256; i++)
        {
            sum=0;
            for(j=0; j<=i; j++)
            {
                sum+=count_pixels[channel][j];
            }
            sum_pixels[channel][i]=sum;
        }
    }

	//generate the new enhanced image by transfer function -----> Method 1
	for(channel=0;channel<3;channel++)
    {
        for(i=0; i<SizeL; i++)
        {
            for(j=0; j<SizeW; j++)
            {
                for(color=0; color<256; color++)
                {
                    if(Image_channel[i][j][channel]==color)
                    {
                        val=255*sum_pixels[channel][color]/(SizeL*SizeW);
						Image_trans[i][j][channel] = (unsigned char)val;
                    }
                }
            }
        }
    }
	
	//generate the new enhanced image by cumulative probability -----> Method 2
	for(channel=0; channel<3; channel++) 
	{
        m = 0;
        n = 0;
        for (color=0; color<256; color++) 
		{
            for (i=0; i<SizeL; i++) 
			{
                for (j=0; j<SizeW; j++) 
				{
                    if (Image_channel[i][j][channel] == color) 
					{
                        Height[m] = i;
                        Width[n] = j;
                        m++;
                        n++;
                    }
                }
            }
        }
        step=0;
        for (color=0; color<256; color++) 
		{
            for (i=step; i<SizeL*SizeW/256+step; i++) 
			{
                Image_cumul[Height[i]][Width[i]][channel] = (unsigned char) color;
            }
            step+=SizeL*SizeW/256;
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
		fwrite(Image_trans, sizeof(unsigned char), SizeL*SizeW*BytesPerPixel, file);
	}
	else if (Method == 2)
	{
		fwrite(Image_cumul, sizeof(unsigned char), SizeL*SizeW*BytesPerPixel, file);
	}
	fclose(file);

	return 0;
}
