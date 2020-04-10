/*
filename: case3_2.cpp
details: Program to demonstrate Modifier types
author: J.P.Prakash
date: 07/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

// main function
int main(int argc,char *argv[])
{
	int iNumb;
	short int a;		// declaring varible short integer
	long int b;			// declaring varible long integer 
	unsigned short c;	// declaring varible unsigned short 
	signed short d;		// declaring varible signed short
	
    if(argc>1) 
	{
		cout<<"\n Usage of file --> \n"
		"\t filename.exe and enter"<<endl<<
		"		or"<<endl<<
		"\t ./filename.out and enter"<<endl;
	}
	else
	{		
		cout << "enter value: ";
		cin>>iNumb;
		a=c=d=b=iNumb;    //value of a, b, c and d is assigned same 
		
		cout << " short int = " << a << endl;        //outputs of the values based on modifiers
		cout << " long int = " << b << endl;
		cout << " unsigned short = " << c << endl;
		cout << " signed short = " << d << endl;
		
		return 0;
	} 
}
