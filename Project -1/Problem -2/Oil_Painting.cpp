// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <map>  
#include <vector>  
#include <algorithm>  

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 512;
	int SizeW = 512;  //default image size is 512 by 512
	int reduce_colors = 64;  //default reduce colors to 64 bits
	int N = 5; //default N = 5
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 512] [SizeWidth = 512] [reduce color to =64]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >=4){
			SizeL = atoi(argv[5]);
			SizeW = atoi(argv[4]);
		}
	}
	//check if image reduce to how many colors
	if (argc >5)
	{
		reduce_colors = atoi(argv[6]);
	}
	//check N value
	if (argc >6)
	{
		N = atoi (argv[7]);
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
	int i,j,k,channel,color,color_Range,m,n,a,b,count,max,row,col,sum,x,pixel_num;
	unsigned char Reduced_image[SizeL][SizeW][BytesPerPixel];
	unsigned char Extended_Width[SizeL][SizeW+ N-1] [BytesPerPixel];
	unsigned char Extended_Matrix[SizeL+N-1][SizeW+N-1][BytesPerPixel];
	int Window[N][N],freq_num[N][N];
	unsigned char Oil_Painting[SizeL][SizeW][BytesPerPixel];
	int count_pixels[BytesPerPixel][256];
	double prob_sum,prob_mean;
	int prob;
	

	//Check for reduce colors to 64 or 512
	if (reduce_colors == 64){
		color_Range = 4;
	}
	else if (reduce_colors ==512){
		color_Range = 8; 
	}
	else {
		cout <<"Syntax Error - Incorrect Parameter Usage. Reduce colors to 64 or 512" << endl;
	}
	
	int Range[BytesPerPixel][color_Range+1],Reduced_set[BytesPerPixel][color_Range];
	int critical[3][color_Range+1][2];
	Range[0][0]=0;Range[1][0]=0;Range[2][0]=0;

	//calculate reduced color image
	for (channel=0; channel<3; channel++)
	{
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				pixel_num = (int) Imagedata[i][j][channel];
				count_pixels[channel][pixel_num]++;
			}
		}
		for (i=0; i<color_Range; i++)
		{
			prob_sum = 0;
			for (color = 0; color<256; color++)
			{
			    prob_sum += count_pixels[channel][color];
			    if (prob_sum >= (i+1)*SizeL*SizeW/color_Range)
			    {
				    Range[channel][i+1]= color;
					break;
			    }
			}
		}
		for (i=0; i<color_Range+1; i++)
		{
			prob_sum = 0;
			for (color = 0; color<=Range[channel][i]; color++)
			{
			    prob_sum += count_pixels[channel][color];
				critical[channel][i][0] = prob_sum - i*SizeL*SizeW/color_Range;
			}
			prob_sum = 0;
			for (color = 0; color<Range[channel][i]; color++)
			{
			    prob_sum += count_pixels[channel][color];
				critical[channel][i][1] = i*SizeL*SizeW/color_Range - prob_sum;
			}
		}

		for (i=0; i<color_Range; i++)
		{
			prob_mean = 0;
			prob_mean += abs(critical[channel][i][0])*(Range[channel][i]);
			prob_mean += abs(critical[channel][i+1][1])*(Range[channel][i+1]);
			for (color = Range[channel][i]+1; color < Range[channel][i+1]; color++)
			{
				prob_mean += count_pixels[channel][color]*(color);
			}
			prob = prob_mean/(SizeL*SizeW)*color_Range;
			Reduced_set[channel][i]= prob;
		}

		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				for (k=0; k<color_Range; k++)
				{
					if ((int)Imagedata[i][j][channel]>=Range[channel][k])
					{
						if ((int)Imagedata[i][j][channel]<=Range[channel][k+1])
						{
							Reduced_image[i][j][channel] = (unsigned char)Reduced_set[channel][k];
						    break;
						}
					}
				}
			}
		}
	}

	// Matrix Extension
	for (channel=0; channel<3; channel++)
	{
		//Firstly, extended width
		for (i=0; i<SizeL; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width[i][(N-1)/2-k][channel]=Reduced_image[i][k][channel];
				Extended_Width[i][SizeW+(N-1)/2+k-1][channel]=Reduced_image[i][SizeW-1-k][channel];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW; j++)
			{
				Extended_Width[i][j+(N-1)/2][channel]=Reduced_image[i][j][channel];
			}
		}
		//Then, extended length
		for (j=0; j<SizeW+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix[(N-1)/2-k][j][channel]=Extended_Width[k][j][channel];
				Extended_Matrix[SizeL+(N-1)/2+k-1][j][channel]=Extended_Width[SizeL-1-k][j][channel];
			}
		}
		for (i=0; i<SizeL; i++)
		{
			for (j=0; j<SizeW+N-1; j++)
			{
				Extended_Matrix[i+(N-1)/2][j][channel]=Extended_Width[i][j][channel];
			}
		}
	}

	//Generate Oil painting
	for(channel=0;channel<3;channel++)
    {
        for(i=(N-1)/2;i<SizeL+(N-1)/2;i++)
        {
            for(j=(N-1)/2;j<SizeW+(N-1)/2;j++)
			{
				//Exstract Window data
				for (m=0; m<N; m++)
				{
					for (n=0; n<N; n++)
					{
						Window[m][n]=(int)Extended_Matrix[i-(N-1)/2+m][j-(N-1)/2+n][channel];
					}
				}
				for (m=0; m<N; m++)
				{
					for (n=0; n<N; n++)
					{
						count=0;
						for (a=0; a<N; a++)
						{
							for (b=0; b<N; b++)
							{
								if (Window[a][b]==Window[m][n])
								{
									count++;
								}
							}
						}
						freq_num[m][n]=count;
					}
				}
				max = freq_num[0][0];
				row =0;
				col =0;
                for (m=0; m<N; m++)
				{
					for (n=0; n<N; n++)
					{
						if (max < freq_num[m][n])
						{
							max = freq_num[m][n];
							row = m;
							col = n;
						}
					}
				}
				Oil_Painting[i-(N-1)/2][j-(N-1)/2][channel]=(unsigned char) Window[row][col];
	        }
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Oil_Painting, sizeof(unsigned char), SizeL*SizeW*BytesPerPixel, file);
	fclose(file);

	return 0;
}