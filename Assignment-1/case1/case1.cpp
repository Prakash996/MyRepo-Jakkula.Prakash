/*
filename: case1.cpp
details: Program to parse the command line and dispaly the output
author:J.P.Prakash
date:06/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

//function to check length of string is '1' or not
bool checkDatatype(string sStr);

//main using command line arguments
int main(int argc,char *argv[])
{
	int iInt;		//declaring integer variables
	float fFloat;	//declaring float variable
	if(argc==1)
	{
		cout<<"\n usage of file --> \n"
		"\t filename.exe arg1 arg2 arg3 arg4"<<endl<<
		"			or"<<endl<<
		"\t ./filename.out arg1 arg2 arg3 arg4"<<endl;
	}
	else
	{
		cout<<"Type \t\tValue \t\tSizeof"<<endl;
		for(int i=1;i<argc;i++)
		{
			iInt=atoi(argv[i]);		//atoi convert ascii to int
			fFloat=atof(argv[i]);	//atof convert ascii to float

			if(iInt==0) //checks the argument and print the specific datatype & size of the argument
			{
				if(checkDatatype(argv[i]))	
				{
					cout<<"Char";
					cout<<"\t\t"<<argv[i]<<"\t\t"<<sizeof(i)<<endl;
				}
				else	
				{
					cout<<"String";
					cout<<"\t\t"<<argv[i]<<"\t\t"<<sizeof(argv[i])<<endl;
				}
			}
			else
			{
			if(iInt==fFloat)
				cout<<"Int"<<"\t\t"<<iInt<<"\t\t"<<sizeof(iInt)<<endl;
			else
				cout<<"Float/Double"<<"\t"<<fFloat<<"\t\t"<<sizeof(fFloat)<<endl;
			}
		}
		return 0;
	}
}

//function to check length of string is '1' or not
bool checkDatatype(string sStr)
{
	int iLength;
	for(iLength=0;sStr.length()==1;iLength++)
	{
		return true;
	}
}
