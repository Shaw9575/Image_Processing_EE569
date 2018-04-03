//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/28/2018

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int GetNewLabel(double *distance, int classnum)
{
    int i,j;
    j=0;
    double min = distance[0];
    for (i=0; i<classnum-1; i++)
    {
        if (min > distance[i+1])
        {
            min = distance[i+1];
            j = i+1;
        }
    }
    return j;
} 
