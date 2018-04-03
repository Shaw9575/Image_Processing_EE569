//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/28/2018
//How to run?
//program_name input_image.raw output_image.raw [BytesPerPixel = 1] [SizeLength = 256] [SizeWidth = 256]


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "fileRead.cpp"
#include "functions.cpp"
#include <vector>
#include<iostream>  
#include<fstream>  
#include<string>  
  

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 700;
    int SizeW = 700;
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
			SizeL = atoi(argv[4]);
            SizeW = atoi(argv[5]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[SizeW][SizeL][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	filename = argv[1];
	ReadImage(filename,&Imagedata[0][0][0],BytesPerPixel,SizeW,SizeL);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int i,j,k,m,n,x,y,p,q,type;
	int N = 5;
	double value1,value2,norm,max,min;
	double filters[5][5] = {{0.0625,0.25,0.375,0.25,0.0625},{-0.166667,-0.33333,0,0.33333,0.166667},{-0.25,0,0.5,0,-0.25},{-0.166667,0.33333,0,-0.33333,0.166667},{0.0625,-0.25,0.375,-0.25,0.0625}};
    vector<vector<double> > Matrix(5,vector<double>(5));
	vector<vector<int> > Extended_Width(SizeW,vector<int>(SizeL+N-1));
	vector<vector<int> > Extended_Matrix((SizeW+N-1),vector<int>(SizeL+N-1));
	vector<vector<vector<double> > > Result(SizeW,vector<vector<double> >(SizeL,vector<double>(25)));
	vector<vector<vector<double> > > Energy(SizeW,vector<vector<double> >(SizeL,vector<double>(25)));
	vector<vector<vector<double> > > Extended_Width2(SizeW,vector<vector<double> >((SizeL+24),vector<double>(25)));
	vector<vector<vector<double> > > Extended_Matrix2((SizeW+24),vector<vector<double> >((SizeL+24),vector<double>(25)));
	double sum0[9],sum1[9],sum2[9],sum3[9],sum4[9],sum5[9];
	//Matrix Extension
    N=5;
	for (i=0; i<SizeW; i++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Width[i][(N-1)/2-k]=(int)Imagedata[i][k][0];
			Extended_Width[i][SizeL+(N-1)/2+k-1]=(int)Imagedata[i][SizeL-1-k][0];
		}
	}
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			Extended_Width[i][j+(N-1)/2]=(int)Imagedata[i][j][0];
		}
	}
	for (j=0; j<SizeL+N-1; j++)
	{
		for (k=1; k<(N+1)/2; k++)
		{
			Extended_Matrix[(N-1)/2-k][j]=Extended_Width[k][j];
			Extended_Matrix[SizeW+(N-1)/2+k-1][j]=Extended_Width[SizeW-1-k][j];
		}
	}
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL+N-1; j++)
		{
	    	Extended_Matrix[i+(N-1)/2][j]=Extended_Width[i][j];
		}
	}
    //get masked 9 values
    type = 0;
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            for(x=0; x<5; x++)
            {
                for(y=0; y<5; y++)
                {
                    Matrix[x][y] = filters[i][x]*filters[j][y];
                }
			}
            for(m=(N-1)/2; m<SizeW+(N-1)/2; m++) 
			{
                for(n=(N-1)/2; n<SizeL+(N-1)/2; n++) 
				{
					value1 = 0;
                    for(p=0; p<N; p++)
					{
                        for(q=0; q<N; q++) 
						{
							value1 += Extended_Matrix[m-(N-1)/2+p][n-(N-1)/2+q]*Matrix[p][q];
						}
                    }
					Result[m-(N-1)/2][n-(N-1)/2][type] = value1;
                }
            }
            type++;
        }
    }
    //matrix extension 
    N=25;
    for (type =0; type<25; type++)
    {
    	for (i=0; i<SizeW; i++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Width2[i][(N-1)/2-k][type]=Result[i][k][type];
				Extended_Width2[i][SizeL+(N-1)/2+k-1][type]=Result[i][SizeL-1-k][type];
			}
		}
		// Fill in the rest unchanged part of original image
		for (i=0; i<SizeW; i++)
		{
			for (j=0; j<SizeL; j++)
			{
				Extended_Width2[i][j+(N-1)/2][type]=Result[i][j][type];
			}
		}
		//Then, extended length
		for (j=0; j<SizeL+N-1; j++)
		{
			for (k=1; k<(N+1)/2; k++)
			{
				Extended_Matrix2[(N-1)/2-k][j][type]=Extended_Width2[k][j][type];
				Extended_Matrix2[SizeW+(N-1)/2+k-1][j][type]=Extended_Width2[SizeW-1-k][j][type];
			}
		}
		for (i=0; i<SizeW; i++)
		{
			for (j=0; j<SizeL+N-1; j++)
			{
	    		Extended_Matrix2[i+(N-1)/2][j][type]=Extended_Width2[i][j][type];
			}
		}
    }
    //get energy values
    for (type=0; type<25; type++)
    {
        for(m=(N-1)/2; m<SizeW+(N-1)/2; m++) 
	    {
            for(n=(N-1)/2; n<SizeL+(N-1)/2; n++) 
		    {
			    value2 = 0;
                for(p=0; p<N; p++)
			    {
                    for(q=0; q<N; q++) 
				    {
					    value2 += Extended_Matrix2[m-(N-1)/2+p][n-(N-1)/2+q][type]*Extended_Matrix2[m-(N-1)/2+p][n-(N-1)/2+q][type];
				    }
                }
			    Energy[m-(N-1)/2][n-(N-1)/2][type] = value2/(N*N);
            }
        }
    }
	//Normalize L3
	for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			norm = Energy[i][j][0];
			for (type=0; type<25; type++)
			{
				Energy[i][j][type] = Energy[i][j][type]/norm;
			}
		}
	}

    //打开要写的文件  
	ofstream outfile ("/Users/yuanshuang/Desktop/EE569/Image_IO/Result.txt",ios::in|ios::out|ios::binary);
    if(!outfile.is_open())
    {
        cout<<" the file open fail"<<endl;
        exit(1);
    }
    for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			for (type=0; type<25; type++)
			{
				outfile<<Energy[i][j][type]<<" ";
                outfile<<"\r\n";
			}
		}
	}
    outfile.close();
}