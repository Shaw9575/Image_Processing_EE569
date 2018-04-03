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

using namespace std;

int main(int argc, char *argv[])

{
	
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	double Sample[12][9] = {{210.145,167.022,65.3065,162.617,116.932,44.874,56.9504,39.4117,15.1894},
	{31.524,28.5466,10.0883,20.7606,16.9463,6.07309,6.15193,4.80527,1.83264},
	{14.105,8.9151,3.08416,11.9583,5.68943,1.73328,4.65421,1.98223,0.562887},	
	{255.271,196.23,71.9017,208.626,141.269,49.0824,70.6708,47.2601,16.538},
	{18.0745,10.486,3.07526,14.7969,6.64625,1.69197,5.48607,2.22402,0.509633},
	{233.159,189.503,73.2143,185.207,133.771,50.8898,65.8654,46.373,17.7457},
	{2.09757,2.32851,1.2816,2.37191,2.34448,1.26265,1.30263,1.27143,0.69419},
	{2.1134,2.33742,1.3216,2.37123,2.37583,1.31614,1.27122,1.2711,0.712313},
	{16.4426,12.2164,3.44301,11.5175,7.50009,2.01475,3.81499,2.39202,0.650932},
	{1.75995,1.48982,0.524454,1.95206,1.47597,0.496562,0.991682,0.745565,0.256653},
	{9.45539,6.53969,2.46386,6.31032,3.16781,1.08629,1.83524,0.794409,0.255281},
	{35.009,34.0232,12.7214,25.5871,23.6575,9.26029,9.0808,8.28692,3.5628}};
	double Centroid[4][9];
    int i,j,k,iter,count,cout0,cout1,cout2,cout3,error;
	double sum,sum0[9],sum1[9],sum2[9],sum3[9];
	double Distance[4],Dataset[9];
	int Label[12]={0,1,2,0,2,0,3,3,1,3,2,1};
	int New_label[12];

	//get first centroid
	for (i=0; i<9; i++)
	{
			sum0[i] = 0;
			sum1[i] = 0;
			sum2[i] = 0;
			sum3[i] = 0;
	}
	cout0=0;cout1=0;cout2=0;cout3=0;
	for (i=0; i<12; i++)
	{
		if (Label[i]==0)
		{
			for (j=0; j<9; j++)
			{
				sum0[j] += Sample[i][j];
			}
			cout0++;
		}
		if (Label[i]==1)
		{
			for (j=0; j<9; j++)
			{
				sum1[j] += Sample[i][j];
			}
			cout1++;
		}
		if (Label[i]==2)
		{
			for (j=0; j<9; j++)
			{
				sum2[j] += Sample[i][j];
			}
			cout2++;
		}
		if (Label[i]==3)
		{
			for (j=0; j<9; j++)
			{
				sum3[j] += Sample[i][j];
			}
		    cout3++;
		}
	}
	for (i=0; i<9; i++)
	{
		Centroid[0][i] = sum0[i]/cout0;
		Centroid[1][i] = sum1[i]/cout1;
		Centroid[2][i] = sum2[i]/cout2;
		Centroid[3][i] = sum3[i]/cout3;
	}


	for (iter = 0; iter<100; iter++)
	{
		// get distance from the sample and centroid and find the new label
		for (i =0; i<12; i++)
		{
			for (j=0; j<4; j++)
			{
				sum = 0;
				for (k=0; k<9; k++)
				{
					sum += (Sample[i][k]-Centroid[j][k])*(Sample[i][k]-Centroid[j][k]);
				}
				Distance[j] = sqrt(sum);
			}
			New_label[i]=GetNewLabel(Distance,4);
		}
		//Check if the label is not changed
		count = 0;
		for (i=0; i<12; i++)
		{
			if (Label[i]==New_label[i])
			{
				count++;
			}
		}
		if (count == 12)
		{
			goto number1;
		}
		else
		{
			for (i=0; i<12; i++)
		    {
				Label[i] = New_label[i];
			}
		}
		//Move to new Centroid
		for (i=0; i<9; i++)
		{
			sum0[i] = 0;
			sum1[i] = 0;
			sum2[i] = 0;
			sum3[i] = 0;
		}
		cout0=0;cout1=0;cout2=0;cout3=0;
		for (i=0; i<12; i++)
		{
			if (Label[i]==0)
			{
				for (j=0; j<9; j++)
				{
					sum0[j] += Sample[i][j];
				}
				cout0++;
			}
			if (Label[i]==1)
			{
				for (j=0; j<9; j++)
				{
					sum1[j] += Sample[i][j];
				}
				cout1++;
			}
			if (Label[i]==2)
			{
				for (j=0; j<9; j++)
				{
					sum2[j] += Sample[i][j];
				}
				cout2++;
			}
			if (Label[i]==3)
			{
				for (j=0; j<9; j++)
				{
					sum3[j] += Sample[i][j];
				}
				cout3++;
			}
		}
		for (i=0; i<9; i++)
		{
			Centroid[0][i] = sum0[i]/cout0;
			Centroid[1][i] = sum1[i]/cout1;
			Centroid[2][i] = sum2[i]/cout2;
			Centroid[3][i] = sum3[i]/cout3;
		}
	}
 
    number1:
	//output the result
    for (i=0;i<12;i++)
	{
		cout<<Label[i]<<',';
	}
	cout<<endl;
	return 0;
}
