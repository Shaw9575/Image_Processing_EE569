//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/28/2018
//How to run?
//./a.out

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
    int SizeL = 600;
    int SizeW = 450;
    int i,j,k,m;
    vector<vector<vector<double> > > Energy(SizeW,vector<vector<double> >(SizeL,vector<double>(9)));
    double Centroid[6][9]={{0.0243839,-0.0167126,-0.000202178,0.000478866,0.000411682,1.8382e-05,0.000461474,2.97744e-05,-0.000107175},
	{-0.0101653,0.000381792,0.00124965,0.000150941,6.47732e-05,0.000834953,-4.29587e-05,0.000115592,9.06951e-05},
	{-0.0141227,-0.00411016,0.000111693,0.000411651,-5.39404e-05,-7.85457e-06,-5.46322e-05,-2.92158e-05,1.21021e-05},
	{-0.00877076,-0.000296684,-0.000827754,-9.52399e-05,0.000200596,9.3691e-05,-6.71876e-05,4.9695e-05,3.19388e-06},
	{-0.0148983,0.00750244,0.00147731,0.000216494,0.000327149,4.61656e-05,1.17119e+166,8.70389e-05,-4.60125e-06},
	{-0.00483763,0.000855169,0.000933407,0.000257863,0.000242283,6.47463e-05,4.43772e-05,-6.57689e-05,-4.39492e-06}};
	int Label[SizeW][SizeL],New_label[SizeW][SizeL];
	int iter,count,cout0,cout1,cout2,cout3,cout4,cout5;
	double sum,sum0[9],sum1[9],sum2[9],sum3[9],sum4[9],sum5[9];
	double Distance[6];
    unsigned char output_image[SizeW][SizeL];
    double S0[9],S1[9],S2[9],S3[9],S4[9],S5[9];
 

    FILE *fp = fopen("/Users/yuanshuang/Desktop/EE569/Image_IO/PCA.txt", "r");
    for (i=0; i<SizeW; i++)
    {
        for (j=0; j<SizeL; j++)
        {
            for (k=0; k<9; k++)
            {
                fscanf(fp, "%lf",&Energy[i][j][k]);
            }
        }
    }
    fclose(fp);
	/*	for (i=0; i<20; i++)
    {
        for (j=0; j<20; j++)
        {
            for (k=0; k<9; k++)
            {
                S0[k]+=Energy[230+i][300+j][k]/400;
                S2[k]+=Energy[75+i][100+j][k]/400;
                S3[k]+=Energy[375+i][100+j][k]/400;
                S4[k]+=Energy[200+i][150+j][k]/400;
                S5[k]+=Energy[375+i][500+j][k]/400;
                S1[k]+=Energy[100+i][500+j][k]/400;
            }
        }
    }
    for (k=0;k<9;k++)
    {
        cout<<S0[k]<<',';
    }
    cout<<endl;
    for (k=0;k<9;k++)
    {
        cout<<S1[k]<<',';
    }
    cout<<endl;
    for (k=0;k<9;k++)
    {
        cout<<S2[k]<<',';
    }
    cout<<endl;
    for (k=0;k<9;k++)
    {
        cout<<S3[k]<<',';
    }
    cout<<endl;
    for (k=0;k<9;k++)
    {
        cout<<S4[k]<<',';
    }
    cout<<endl;
    for (k=0;k<9;k++)
    {
        cout<<S5[k]<<',';
    }
    cout<<endl;*/

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
				    for (m=0; m<9; m++)
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
	WriteImage("RE.raw", &output_image[0][0],1,SizeW,SizeL);
	return 0;
}