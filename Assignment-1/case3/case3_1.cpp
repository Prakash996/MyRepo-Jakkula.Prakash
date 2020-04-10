/*
filename: case3_1.cpp
details: Program to demonstrate Variable Scope
author: J.P.Prakash
date: 07/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

// global variable 
int iGlobal = 5; 

// variable accessed from 
inline display() 
{ 
	cout<<iGlobal<<endl; 
} 

// main function
int main(int argc,char *argv[])
{
    if(argc>1) 
	{
		cout<<"\n Usage of file --> \n"
		"\t filename.exe and enter"<<endl<<
		"			or"<<endl<<
		"\t ./filename.out and enter"<<endl;
	}
	else
	{	
	  	// prints the variable iGlobal
	   	cout<<"Global value: ";
		display(); 

		iGlobal=50;
		// changing value of iGlobal by assigning value locally
		// local variable defined with same name as that of a global variable then the compiler will give precedence to the local variable
		cout<<"Local value: ";
		display(); 
	} 
}
