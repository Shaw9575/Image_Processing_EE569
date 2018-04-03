//Name: Shuang Yuan
//USC ID: 3904204605
//USC e-mail: shuangy@usc.edu
//Submission data: 03/01/2018

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <memory.h>

using namespace std;


int compare(string *chart,string imput,int chartsize)
{
    int hit2 = 0;
	for(int i=0; i<chartsize; i++)
    {
		if(chart[i]==imput)
        {
			hit2 = 1;
			i = chartsize;
		}
	}
	return hit2;
}
int uncondition_ST(string imput)
{
    int hit = 0;
    string chart[364]={"001010000","100010000","000010010","000011000","001011000","011010000","110010000","100110000","000110100",
"000010110","000010011","000011001","011110000","110011000","010011001","001011010","001011100","011010100","011011100",
"110010001","100110001","110110001","001010110","001110100","001110110","100011001","100010011","100011011",
"110110000","110110001","110111000","110111001","111110000","111110001","111111000",
"111111001","110110010","110110011","110111010","110111011","111110010","111110011",
"111111010","111111011","110110100","110110101","110111100","110111101","111110100","111110101",
"111111100","111111101","110110110","110110111","110111110","110111111","111110110","111110111","111111110","111111111",
"010110010","011110010","110110010","111110010","010110010","010110011","010110110","010110111",
"010011010","010011011","010011110","010011111","010011010","011011010","110011010","111011010",
"010111000","010111100","110111000","110111100","010111000","010111001","011111000","011111001",
"000111010","000111011","001111010","001111011","000111010","000111110","100111010","100111110",
"100010101","100011100","100011101","101010100","101010101","101011100",
"101011101","100010111","100011110","100011111","101010110","101010111",
"101011110","101011111","110010101","110011100","110011101","111010100",
"111010101","111011100","111011101","110010111","110011110","110011111",
"111010110","111010111","111011110","111011111","100110101","100111100",
"100111101","101110100","101110101","101111100","101111101","100110111",
"100111110","100111111","101110110","101110111","101111110","101111111",
"110110101","110111100","110111101","111110100","111110101","111111100",
"111111101","110110111","110111110","110111111","111110110","111110111",
"111111110","111111111",
"101010100","101010010","101010110","101010001","101010101","101010011",
"101010111","101011100","101011010","101011110","101011001","101011101",
"101011011","101011111","111010100","111010010","111010110","111010001",
"111010101","111010011","111010111","111011100","111011010","111011110",
"111011001","111011101","111011011","111011111","101110100","101110010",
"101110110","101110001","101110101","101110011","101110111","101111100",
"101111010","101111110","101111001","101111101","101111011","101111111",
"111110100","111110010","111110110","111110001","111110101","111110011",
"111110111","111111100","111111010","111111110","111111001","111111101",
"111111011","111111111",
"001010101","001110001","001110101","101010001","101010101","101110001",
"101110101","001011101","001111001","001111101","101011001","101011101",
"101111001","101111101","001010111","001110011","001110111","101010011",
"101010111","101110011","101110111","001011111","001111011","001111111",
"101011011","101011111","101111011","101111111","011010101","011110001",
"011110101","111010001","111010101","111110001","111110101","011011101",
"011111001","011111101","111011001","111011101","111111001","111111101",
"011010111","011110011","011110111","111010011","111010111","111110011",
"111110111","011011111","011111011","011111111","111011011","111011111",
"111111011","111111111",
"001010101","010010101","011010101","100010101","101010101","110010101",
"111010101","001011101","010011101","011011101","100011101","101011101",
"110011101","111011101","001010111","010010111","011010111","100010111",
"101010111","110010111","111010111","001011111","010011111","011011111",
"100011111","101011111","110011111","111011111","001110101","010110101",
"011110101","100110101","101110101","110110101","111110101","001111101",
"010111101","011111101","100111101","101111101","110111101","111111101",
"001110111","010110111","011110111","100110111","101110111","110110111",
"111110111","001111111","010111111","011111111","100111111","101111111",
"110111111","111111111",
"001110010","001110011","101110010","101110011",
"010110001","011110001","010110101","011110101","010011100","010011101","110011100","110011101",
"100011010","101011010","100011110","101011110","110110000","110110001","110111000","110111001","111110000","111110001",
"111111000","111111001","110110010","110110011","110111010","110111011",
"111110010","111110011","111111010","111111011","110110100","110110101",
"110111100","110111101","111110100","111110101","111111100","111111101",
"110110110","110110111","110111110","110111111","111110110","111110111",
"111111110","111111111"};
    /*string chart[133]={"001010000","100010000","000010010","000011000",
    "001011000","011010000","110010000","100110000","000110100","000010110","000010011","000011001",
    "011110000","110011000","010011001","001011010",
    "001011100","011011100","011010100","001011100","110110001","100110001","110010001","001110110","001110100","001010110","100011011","100011001",
    "100010011","110110000","111111111","110111100","010111000","011111001","001111011","000111010","100111110","111110010","010110010","010110111","010011111","010011010","111011010",
    "101010100","111111100","101010010","111111010","101010110","111111110","101010001","111111001","101010101","111111101","101010011","111111011","101010111",
    "101010001","111110011","100011001","110111011","101011001","111111011","100010101","110110111","101010101","111110111","100011101","110111111","101011101",
    "100010101","100111111","010010101","010111111","110010101","110111111","001010101","001111111","101010101","101111111","011010101","011111111","111010101",
    "001010101","011011111","001110100","011111110","001110101","011111111","101010100","111011110","101010101","111011111","101110100","111111110","101110101",
    "110011101","010011100","011110101","010110001","101110011","001110010","101011110","100011010",
    "110110010","110110011","111110110","110111110","110110110","111110101","110110100","110111010","111111000",
    "101011010","100011110","110111000","110111001","111110000","111110001","110011100","010011101","010110101",
    "011110001","001110011","001110111","010111101","011111101","100111101","101111101","110111101","001111101","101110101","100110101",
    "100011111"};*/
    hit = compare(chart,imput,364);
    return hit;
}

int uncondition_K(string imput)
{
    int hit = 0;
    string chart[169]={"001010000","100010000","000010100","000010001","000010010","000011000","010010000","000110000","010011000","010110000","000011010","000110010",
    "100011010","001110010","011110101","110011101","011010101","101010101","001110101","001110100","010010101","110010101","100011001",
    "101011001","100010101","100011101","111010101","101110011","101110100","101011101","101011110","101010111","101010011","101010001","010111111",
    "101010110","101010010","101010100","000111010","001010101","010011010","010110010","011111110","111111011","111011110","111011111","101111111",
	"110110000","110111000","111110000","111111000","110110100","110111100","111110100","111111100","110110010","110111010",
    "111110010","111111010","110110110","110111110","111110110","111111110","110110001","110111001","111110001","111111001",
    "110111101","111110101","111111101","110111011","111110011","110110111","110111111","111110111","111111111",
	"000011011","000111011","001011011","000011111","000111111","001011111","001111111","010011011","010111011",
    "011011011","011111011","010011111","011011111","011111111","100111011","101111011","100011111","100111111",
    "101011111","110011011","111011011","001111011","110011110","010111010","011110010","011111010","010110110","010111110","011110110",
    "010110011","011110011","010110111","011110111","110110011","011011010","010011110","011011110",
    "110011010","111011010","001111010","000111110","100111010","101111010","100111110","101111110","101011100",
    "101110001","101110111","101111100","101111001","101111101","111010010","111010110","111010001",
    "100110111","111011001","111011101","111010011","100010111","100111001","100110101","101110101","100111101","010010111",
    "110010111","011010111","111010111","110110101","011011101","110011111","010111101","001010111","001110111","001011101",//140
    "001111100","001111101","001111110", "111010100","011111100","011111101","111011100","010011001","010011101","110011001",
    "010110100","010110101","011110100","001110110","101110010","101110110","100011011","101011010","101011011"};
    /*string chart[85] = {"001010000","100010000","000010100","000010001","000010010","000011000","010010000","000110000","010011000","010110000","000011010","000110010",
    "111111111","110110000","000011011","010111000","010110010","000111010","010011010","111111100","101010010","111111010",
    "101010110","111111110","101010001","111111001","101010101","111111101","101010011","111111011","101010111","111111111",
    "111110011","100011001","110111011","101011001","111111011","100010101","110110111","111110111","100011101","110111111",
    "100111111","010010101","010111111","110010101","110111111","001111111","101111111","011010101","011111111","111010101",
    "001010101","011011111","001110100","011111110","001110101","011111111","101010100","111011110","111011111","101110100","111111110","101110101",
    "110011101","010011100","011110101","010110001","101110011","001110010","101011110","100011010","101011101","111111111"};*/
    hit = compare(chart,imput,130);
    return hit;
}

int FirstStage_S(string imput)
{
	string shrink[58] ={"001010000","100010000","000010100","000010001",
    "000011000","010010000","000110000","000010010",
    "001011000","011010000","110010000","100110000","000110100","000010110","000010011","000011001",
    "001011001","111010000","100110100","000010111",
    "110011000","010011001","011110000","001011010","011011000","110110000","000110110","000011011",
    "110011001","011110100","111011000","011011001","111110000","110110100","100110110","000110111","000011111","001011011",
    "111011001","111110100","100110111","001011111","011011011","111111000","110110110","000111111",
    "111011011","011011111","111111100","111111001","111110110","110110111","100111111","001111111","111011111","111111101","111110111","101111111"};
    int hit=0;
    hit = compare(shrink,imput,58);
    return hit;
}
int FirstStage_K(string imput)
{
    string skelet[40] = {"010011000","010110000","000110010","000011010","001011001","111010000","100110100","000010111",
    "111011000","011011001","111110000","110110100","100110110","000110111","000011111","001011011","111011001","111110100","100110111","001011111",
    "011011011","111111000","110110110","000111111","111011011","011011111","111111100","111111001","111110110","110110111","100111111","001111111",
    "111011111","111111101","111110111","101111111","111111011","111111110","110111111","011111111"};
    int hit=0;
    hit = compare(skelet,imput,40);
    return hit;
}
int FirstStage_T(string imput)
{
    string thining[46]={"001011001","111010000","100110100","000010111","010011000","010110000","000110010","000011010","110011000","010011001","011110000","001011010","011011000","110110000","000110110","000011011",
    "110011001","011110100","111011000","011011001","111110000","110110100","100110110","000110111","000011111","001011011",
    "111011001","111110100","100110111","001011111","011011011","111111000","110110110","000111111",
    "111011011","011011111","111111100","111111001","111110110","110110111","100111111","001111111",
    "111011111","111111101","111110111","101111111"};
    int hit=0;
    hit = compare(thining,imput,46);
    return hit;
}
