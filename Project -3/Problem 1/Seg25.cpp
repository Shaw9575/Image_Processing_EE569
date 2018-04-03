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

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int SizeL = 600;
    int SizeW = 450;
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
	int N=5;
	unsigned char output_image[SizeW][SizeL];
	double value1,value2,norm;
	double filters[3][5] = {{0.0625,0.25,0.375,0.25,0.0625},{-0.25,0,0.5,0,-0.25},{-0.166667,0.33333,0,-0.33333,0.166667}};
    vector<vector<double> > Matrix(5,vector<double>(5));
	vector<vector<int> > Extended_Width(SizeW,vector<int>(SizeL+N-1));
	vector<vector<int> > Extended_Matrix((SizeW+N-1),vector<int>(SizeL+N-1));
	vector<vector<vector<double> > > Result(SizeW,vector<vector<double> >(SizeL,vector<double>(9)));
	vector<vector<vector<double> > > Energy(SizeW,vector<vector<double> >(SizeL,vector<double>(9)));
	vector<vector<vector<double> > > Extended_Width2(SizeW,vector<vector<double> >((SizeL+24),vector<double>(9)));
	vector<vector<vector<double> > > Extended_Matrix2((SizeW+24),vector<vector<double> >((SizeL+24),vector<double>(9)));
	double Centroid[6][9]={{1,0.0225304,0.00723327,0.00807384,0.00518134,0.00260228,0.00317344,0.00190722,0.00102469},
	{1,0.00195102,0.00046374,0.00393698,0.00399497,0.00114766,0.00111536,0.00270367,0.00100658},
	{1,0.00156197,0.00044425,0.00361064,0.00170905,0.000497286,0.00152561,0.00111316,0.00030084},
	{1,0.00168685,0.000257806,0.00365638,0.00180414,0.000419827,0.000801538,0.000785496,0.000222059},
	{1,0.00282388,0.000906773,0.0167253,0.00112567,0.000288148,0.0053374,0.000604709,0.000152212},
	{1,0.00212062,0.000240003,0.00405338,0.00373103,0.000874425,0.000561741,0.00123205,0.00037717}};
	int Label[SizeW][SizeL],New_label[SizeW][SizeL];
	int iter,count,cout0,cout1,cout2,cout3,cout4,cout5;
	double sum,sum0[9],sum1[9],sum2[9],sum3[9],sum4[9],sum5[9];
	double Distance[6];

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
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
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
    for (type =0; type<9; type++)
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
    for (type=0; type<9; type++)
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
			for (type=0; type<9; type++)
			{
				Energy[i][j][type] = Energy[i][j][type]/norm;
			}
		}
	}
    for (iter = 0; iter<200; iter++)
	{
		// get distance from the sample and centroid and find the new label
		for (i=0; i<SizeW; i++)
		{
			for (j=0; j<SizeL; j++)
		    {
			    for (k=0; k<6; k++)
			    {
				    sum = 0;
				    for (m=1; m<9; m++)
				    {
					    sum += (Energy[i][j][m]-Centroid[k][m])*(Energy[i][j][m]-Centroid[k][m]);
				    }
				    Distance[k] = sqrt(sum);
			    }
			    New_label[i][j]=GetNewLabel(Distance,6);
			}
		}
		//Check if the label is not changed
		count = 0;
		for (i=0; i<SizeW; i++)
		{
			for (j=0; j<SizeL; j++)
			{
				if (Label[i][j]==New_label[i][j])
			    {
				    count++;
			    }
			}	
		}
		if (count == SizeL*SizeW)
		{
			goto number1;
		}
		else
		{
			for (i=0; i<SizeW; i++)
		    {
			    for (j=0; j<SizeL; j++)
			    {
				    Label[i][j] = New_label[i][j];
			    }
			}
		}
		//Move to new Centroid
		for (i=0; i<9; i++)
		{
			sum0[i] = 0;sum1[i] = 0;sum2[i] = 0;sum3[i] = 0;sum4[i] = 0;sum5[i] = 0;
		}
		cout0=0;cout1=0;cout2=0;cout3=0;cout4=0;cout5=0;
		for (i=0; i<SizeW; i++)
		{
			for (j=0; j<SizeL; j++)
			{
			    if (Label[i][j]==0)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum0[k] += Energy[i][j][k];
				    }
				    cout0++;
				}
				if (Label[i][j]==1)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum1[k] += Energy[i][j][k];
				    }
				    cout1++;
				}
				if (Label[i][j]==2)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum2[k] += Energy[i][j][k];
				    }
				    cout2++;
				}
				if (Label[i][j]==3)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum3[k] += Energy[i][j][k];
				    }
				    cout3++;
				}
				if (Label[i][j]==4)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum4[k] += Energy[i][j][k];
				    }
				    cout4++;
				}
				if (Label[i][j]==5)
			    {
				    for (k=0; k<9; k++)
				    {
					    sum5[k] += Energy[i][j][k];
				    }
				    cout5++;
				}
			}
		}
		for (i=0; i<9; i++)
		{
			Centroid[0][i] = sum0[i]/cout0;
			Centroid[1][i] = sum1[i]/cout1;
			Centroid[2][i] = sum2[i]/cout2;
			Centroid[3][i] = sum3[i]/cout3;
			Centroid[4][i] = sum4[i]/cout4;
			Centroid[5][i] = sum5[i]/cout5;
		}
	}
 
    number1:
	//output the result
    for (i=0; i<SizeW; i++)
	{
		for (j=0; j<SizeL; j++)
		{
			if (Label[i][j] == 0)
			{
				output_image[i][j]=(unsigned char) 0;
			}
			if (Label[i][j] == 1)
			{
				output_image[i][j]=(unsigned char) 51;
			}
			if (Label[i][j] == 2)
			{
				output_image[i][j]=(unsigned char) 102;
			}
			if (Label[i][j] == 3)
			{
				output_image[i][j]=(unsigned char) 153;
			}
			if (Label[i][j] == 4)
			{
				output_image[i][j]=(unsigned char) 204;
			}
			if (Label[i][j] == 5)
			{
				output_image[i][j]=(unsigned char) 255;
			}
		}
	}
	filename  = argv[2];
	WriteImage(filename, &output_image[0][0],1,SizeW,SizeL);
	return 0;
}
