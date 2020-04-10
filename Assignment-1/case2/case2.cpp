/*
filename: case2.cpp
details: Program to find the formula for give expression.  Expression: 1+4+9+16+….+100
author:J.P.Prakash
date:07/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

//main function
int main(int argc,char *argv[])
{
    int iSum,iNumb; //declaring integer variables
    if(argc==1) 
	{
		cout<<"\n Usage of file --> \n"
		"\t filename.exe argument"<<endl<<
		"			or"<<endl<<
		"\t ./filename.out argument"<<endl;
		
		cout<<"Enter Input: ";
		cin>>iNumb; //read 'iNumb'
		iSum=0;
    	for(int i=1; i<=iNumb; ++i)	//checks the argument value
        	iSum += (i*i);	//gives output based on the expression: 1+4+9+16+….+100
     	cout << "Output: " << iSum;
     	return 0;
	}
	else
	{	
		iNumb = atoi(argv[1]); //assigning the argument to 'n'
    	iSum=0;
    	for(int i=1; i<=iNumb; ++i)	//checks the argument value
        	iSum += (i*i);	//gives output based on the expression: 1+4+9+16+….+100
     	cout << "Output: " << iSum;
     	return 0;
	} 
}
