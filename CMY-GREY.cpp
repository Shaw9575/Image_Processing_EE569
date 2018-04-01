// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 854;
	int SizeW = 480;
	int Size;
	
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
	int new_BytesPerPixel = 1;
	unsigned char CMY_C[SizeL][SizeW][new_BytesPerPixel];
	unsigned char CMY_M[SizeL][SizeW][new_BytesPerPixel];
	unsigned char CMY_Y[SizeL][SizeW][new_BytesPerPixel];
	int Image_channel[SizeL][SizeW][BytesPerPixel];
	int i,j,channel;

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
	

	// Gerenate CMY image data
	for (i=0; i<SizeL; i++)
	{
		for (j=0; j<SizeW; j++)
		{
			CMY_C[i][j][0]=(unsigned char)(255-Image_channel[i][j][0]);
			CMY_M[i][j][0]=(unsigned char)(255-Image_channel[i][j][1]);
			CMY_Y[i][j][0]=(unsigned char)(255-Image_channel[i][j][2]);
		}
	}


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(CMY_M, sizeof(unsigned char), SizeL*SizeW*new_BytesPerPixel, file);
	fclose(file);

	return 0;
}
