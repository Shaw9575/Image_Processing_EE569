//
//  main.cpp
//  image resizing via Bilinear Interpolation
//


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
	unsigned char Imagedata[Size][Size][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int New_Size = 650;		//new image size
	int Width,Length,channel,x,y,i,j;
	int value;
	float p,q;
	unsigned char New_Image[New_Size][New_Size][BytesPerPixel];
	int Image_channel[Size][Size][BytesPerPixel];

	//Change unsigned char data into integer for further calculation
	for(channel=0;channel<3;channel++)
    {
        for(i=0; i<Size; i++)
        {
            for(j=0; j<Size; j++)
            {
                Image_channel[i][j][channel]=(int)Imagedata[i][j][channel];
            }
        }
    }
	// Image resizing by bilinear interpolation
	for(channel=0;channel<3;channel++)
	{
		for(Length=0; Length<New_Size; Length++)
		{
			for(Width=0; Width<New_Size; Width++)
			{
				x = Length*(Size-1)/(New_Size-1);
				y = Width*(Size-1)/(New_Size-1);
				p = (float)Length*(Size-1)/(New_Size-1) - x;
				q = (float)Width*(Size-1)/(New_Size-1) - y;
				if(x == (Size-1) && y == (Size-1))
				{
					New_Image[New_Size-1][New_Size-1][channel] = Imagedata[Size-1][Size-1][channel];
					continue;
				}
				if(x == (Size-1) && y != (Size-1))
				{
					value = q*Image_channel[x][y+1][channel]+(1-p)*(1-q)*Image_channel[x-1][y][channel]+p*(1-q)*Image_channel[x-1][y+1][channel]+p*(1-q)*Image_channel[x][y][channel];
					New_Image[Length][Width][channel] = (char)value;
					continue;
				}
				if(y == (Size-1) && x != (Size-1))
				{
					value = p*Image_channel[x+1][y][channel]+(1-p)*(1-q)*Image_channel[x][y-1][channel]+p*(1-q)*Image_channel[x][y][channel]+p*(1-q)*Image_channel[x+1][y-1][channel];
					New_Image[Length][Width][channel] = (char)value;
					continue;
				}
				value = p*q*Image_channel[x+1][y+1][channel]+(1-p)*(1-q)*Image_channel[x][y][channel]+p*(1-q)*Image_channel[x][y+1][channel]+p*(1-q)*Image_channel[x+1][y][channel];
				New_Image[Length][Width][channel] = (char)value;
			}
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(New_Image, sizeof(unsigned char), New_Size*New_Size*BytesPerPixel, file);
	fclose(file);
	return 0;
}