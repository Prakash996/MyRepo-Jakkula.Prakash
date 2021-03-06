/*
filename: case1.cpp
details: Program to parse the command line and dispaly the output
author:J.P.Prakash
date:06/04/2020
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

//function to check length of string is '1' or not
bool checkDatatype(string sStr);

//main using command line arguments
int main(int argc,char *argv[])
{
	int iCheckInt;		//declaring integer variables
	float fCheckFloat;	//declaring float variable
	if(argc==2)
	{
		if(strcmp(argv[1],"-h")==0)     //created a help command
        {
			cout<<"\n usage of file --> \n"
			"\t filename.exe arg1 arg2 arg3 arg4.."<<endl<<
			"			or"<<endl<<
			"\t ./filename.out arg1 arg2 arg3 arg4.."<<endl;
		}		
		else
		{
			cout<<"Type \t\tValue \t\tSizeof"<<endl;
			for(int i=1;i<argc;i++)
			{
				iCheckInt=atoi(argv[i]);		//atoi convert ascii to int
				fCheckFloat=atof(argv[i]);	//atof convert ascii to float
	
				if(iCheckInt==0) //checks the argument and print the specific datatype & size of the argument
				{
					if(checkDatatype(argv[i]))	
					{
						cout<<"Char"<<"\t\t"<<argv[i]<<"\t\t"<<strlen(argv[i])<<endl;
					}
					else	
					{
						cout<<"String"<<"\t\t"<<argv[i]<<"\t\t"<<strlen(argv[i])<<endl;
					}
				}
				else
				{
				if(iCheckInt==fCheckFloat)
					cout<<"Int"<<"\t\t"<<iCheckInt<<"\t\t"<<sizeof(iCheckInt)<<endl;
				else
					cout<<"Float/Double"<<"\t"<<fCheckFloat<<"\t\t"<<sizeof(fCheckFloat)<<endl;
				}
			}
			return 0;
		}
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
