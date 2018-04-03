//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [# Method]

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void ReadImage(const char *filename, unsigned char *Imagedata, int Bytes, int width, int height)
{
	FILE *file;
	if (!(file=fopen(filename,"rb"))) {
		cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*Bytes, file);
	fclose(file);
}
void WriteImage(const char *filename, unsigned char *Imagedata, int Bytes, int width, int height)
{
	FILE *file;
	if (!(file=fopen(filename,"wb"))) {
		cout << "Cannot open file: " << filename << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*Bytes, file);
	fclose(file);
}