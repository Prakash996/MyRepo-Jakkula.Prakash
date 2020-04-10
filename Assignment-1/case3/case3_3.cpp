/*
filename: case3_3.cpp
details: Program to demonstrate different storage classes
author: J.P.Prakash
date: 08/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;


// declaring the extern variable
int x='a'; 

void autoStorageClass(auto int a);
void registerStorageClass(register int b);
void externStorageClass(int iValue);
void staticStorageClass(int iValue);

// main function
int main(int argc,char *argv[])
{
	auto int a;
	register int b;
	static int p;
	int q;
	int iValue;
	if(argc>1) 
	{
		cout<<"\n Usage of file --> \n"
		"\t filename.exe and enter"<<endl<<
		"		or"<<endl<<
		"\t ./filename.out and enter"<<endl;
	}
	else
	{
	/*	cout<<"Enter auto variable: ";
			cin>>a;
		cout<<"Enter register variable: ";
			cin>>b;
		cout<<"Enter static variable: ";
			cin>>p;
		cout<<"Enter non-static variable: ";
			cin>>q;
		*/
		cout<<"Enter a value: ";
			cin>>iValue;
		a=b=p=q=iValue;
		cout<<"\nStorage Classes \n"<<endl; 
	
		// To demonstrate auto Storage Class 
		autoStorageClass(a); 
	
		// To demonstrate register Storage Class 
		registerStorageClass(b); 
	
		// To demonstrate extern Storage Class 
		externStorageClass(iValue); 
	
		// To demonstrate static Storage Class 
		staticStorageClass(iValue); 
	
		return 0; 
	} 
}

void autoStorageClass(auto int a) //auto storage class
{ 
	// declaring an auto variable 
	//auto int a = 'a';

	// print auto variable 
	cout<<" Value of the auto variable : "<<a<<endl; 
	cout<<"--------------------------------"<<endl; 
} 

void registerStorageClass(register int b) 
{ 
	// declaring a register variable 
	//register int b = 'a'; 

	// print register variable
	cout<<" Value of the register variable : "<<b<<endl; 
	cout<<"--------------------------------"<<endl;  
} 

void externStorageClass(int iValue) 
{ 

	// telling the compiler that the variable is an extern variable
	extern int x; 

	// print extern variables  
	cout<<" Value of the extern variable: "<<x<<endl; 

	// value of extern variable modified 
	x = iValue; 

	// print modified extern variables  
	cout<<" Value of the modified extern variable : "<<x<<endl; 
	cout<<"--------------------------------"<<endl; 
} 


void staticStorageClass(int iValue) 
{ 	
	// printing a static variable & non-static variables with in a loop
	cout<<" Declaring static & non-static variable inside a loop \n"<<endl; 
	
	for (int i = 1; i <= 3; i++) { 

		// Declaring the static variable
		static int p = iValue; 

		// Declare a non-static variable 
		int q = iValue; 

		// Incrementing the values  
		p++; 
		q++; 

		cout<<"	Static variable = "<<p<<endl; 
		cout<<"	Non-Static variable =  "<<q<<endl; 
	} 
	cout<<"--------------------------------"<<endl; 
} 

