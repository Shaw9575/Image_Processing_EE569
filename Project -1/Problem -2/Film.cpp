//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 02/04/2018
//How to run?

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
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
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//int R[256],G[256],B[256];
	double R[]={1,4,30,55,42,67,52,41,29,20,11,16,10,11,13,11,8,19,16,12,13,20,10,15,11,12,10,10,10,1,4,10,2,7,7,4,5,9,5,4,6,3,4,3,3,1,4,4,2,3,5,2,2,2,5,1,4,0,1,2,2,2,2,2,2,2,3,3,2,0,2,0,0,3,3,2,2,4,2,4,5,5,15,21,55,73,115,155,182,226,294,273,261,296,399,604,789,1036,1402,1551,1434,1517,1699,1862,1710,1600,1496,1563,1753,1880,1880,1713,1646,1548,1496,1341,1227,1253,1285,1306,1315,1363,1375,1438,1698,1979,2714,3421,3938,4116,4391,4906,5563,6409,7011,7796,9388,10227,10048,8579,7800,7056,6359,5725,5527,5585,5590,5582,5273,5017,4818,4466,3937,3534,3460,3093,2753,2554,2574,2595,2462,2258,2340,2181,2325,2334,2465,2493,2461,2635,2733,2889,2906,3248,3213,3476,3735,4016,4081,4403,4786,4849,5142,5172,5362,5329,5601,5477,5567,5595,5442,5336,5488,5329,5458,5467,5450,5406,5539,5516,5748,5720,5793,6003,5944,5963,6194,6326,6332,6397,6360,6452,6559,6496,6503,6252,6450,6392,6476,6426,6620,6679,6606,6935,6792,6810,6884,6876,6786,7000,6831,6687,6620,6653,6451,6494,6248,5984,5933,5553,5450,5374,5157,4852,4506,4332,4127,4200,4298,4346,4763,5562,6825,8553,10093,14694};
	double G[]={1,3,27,51,41,72,58,43,33,29,22,18,26,13,18,21,12,12,10,11,11,11,8,6,7,5,11,11,3,12,21,44,86,215,466,907,1638,2564,4022,4762,4649,4140,3609,3609,3780,4169,4887,6703,9735,12059,11340,9051,7398,7159,8528,9111,7796,5736,4288,3880,3603,3422,3422,3334,3096,2949,2764,2711,2977,3080,3516,3992,4294,4791,5095,5512,5836,6020,6010,5866,5930,5863,5986,5880,5919,5727,5549,5477,5512,5639,5419,5641,5762,6038,5984,6455,6532,6846,7095,7281,7532,7716,7844,8169,8132,7993,8131,8242,8036,8100,8045,8013,8215,8005,8015,7997,7984,8016,7957,7734,7475,7416,7467,7242,7334,7513,7439,7438,7433,7586,7576,7450,7431,7283,7075,6866,6360,6051,5765,5208,4930,4799,4433,4071,3898,3679,3509,3270,3119,2923,2801,2660,2580,2372,2430,2153,2080,2025,1963,1919,1851,1786,1728,1565,1499,1440,1457,1350,1303,1248,1217,1167,1152,1124,1031,1071,1096,1057,999,980,882,847,774,710,1920169936,1651076738,1819895451,684,482,474,497,589,718,760,712,560,278,157,108,71,67,38,25,16,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double B[]={10,14,36,61,51,49,45,40,22,27,25,19,10,19,9,14,11,13,20,24,38,56,62,72,103,178,294,651,1505,3553,7022,11118,13415,13532,12556,11650,10605,9593,7726,6063,5003,4396,4102,3909,3882,3869,3875,3663,3650,3598,3613,3482,3295,3248,3151,3078,2995,2830,2859,2799,2814,2762,2874,2770,2753,2904,2907,2823,3033,3249,3406,3599,3894,4292,4592,5034,5315,5489,5881,6027,6149,6071,6119,5818,5643,5426,5265,5235,5090,4871,4858,5047,5203,5258,5458,5998,6468,6724,7137,7522,7859,8243,8305,8500,8286,8287,8262,8078,7700,7433,7179,6799,6677,6472,6422,6329,6245,6291,6261,6247,6275,6375,6333,6417,6551,6484,6663,6553,6580,6582,6735,6796,6583,6598,6634,6484,6600,6481,6428,6316,6215,6161,5860,5814,5609,5444,5178,5135,4875,4759,4415,4111,3827,3449,3293,3073,2958,2561,2393,2093,1878,1776,1564,1325,1222,1067,870,761,598,510,375,304,254,153,125,78,53,43,25,20,11,8,8,2,3,0,4,4,0,0,2,1,1,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,7,0,1,0,0,0,0,0,0,0,0,0,0};

	int i,j,channel,color,sub;
	long m,n,sum;
	double prob_hist[BytesPerPixel][256];
	int Line[BytesPerPixel][Size*Size],map[3][256];
	unsigned char Result_image[Size][Size][BytesPerPixel],new_girl[Size][Size][BytesPerPixel];

	for (color=0; color<256; color++)
	{
		prob_hist[0][color]=R[color]/1000/750*Size*Size;
		prob_hist[1][color]=G[color]/1000/750*Size*Size;
		prob_hist[2][color]=B[color]/1000/750*Size*Size;
	}
	//Generate mirror and CMY new girl image
	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				new_girl[i][255-j][channel] = (unsigned char)(255 - (int)Imagedata[i][j][channel]);
			}
		}
	}
	//rearrange the imagedata to a line by numbers
	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				Line[channel][i*Size+j]=(int)new_girl[i][j][channel];
			}
		}
		for (m=0; m<Size*Size; m++)
		{
			for (n=0; n<Size*Size-m; n++)
			{
				if (Line[channel][n]>Line[channel][n+1])
				{
					sub = Line[channel][n];
					Line[channel][n]=Line[channel][n+1];
					Line[channel][n+1]=sub;
				}
			}
		}
	}
	//Generating mapping funciton
	for (channel=0; channel<3; channel++)
	{
		sum = 0;
		for (color=0; color<256; color++)
		{
			sum += (int)prob_hist[channel][color];
			map[channel][color]=Line[channel][sum];
		}
	}

	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<Size; i++)
		{
			for (j=0; j<Size; j++)
			{
				for (color=0; color<256; color++)
				{
					if (new_girl[i][j][channel]==color)
					{
						Result_image[i][j][channel]=(unsigned char)map[channel][color];
					}
				}
			}
		}
	}
	
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Result_image, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	return 0;
}
