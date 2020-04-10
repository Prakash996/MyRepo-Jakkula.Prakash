/*
filename: case4.cpp
details: Program to demonstrate access specifiers
author: J.P.Prakash
date: 07/04/2020
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

class Base
{
	private:
		int a;
	public:
		int b;
	protected:
		int c;
	public:
	
		void show()
		{
			cout<<"enter a: ";
				cin>>a;
			cout<<"enter b: ";
				cin>>b;
			cout<<"enter c: ";
				cin>>c;
			/*a=10;
			b=20;
			c=30;
			*/
			//Every members can be access here, same class
			cout<<"\nAccessing variable within the class"<<endl;
			
			cout<<"Value of a: "<<a<<endl;
			cout<<"Value of b: "<<b<<endl;
			cout<<"Value of c: "<<c<<endl;
		}
};

class Sub_class:public Base
{
	public:
		void show()
		{
			b=5;
			c=6;
			cout<<"\nAccessing variable in Sub class"<<endl;
		
			// a is not accessible here it is private
			//cout<<"Value of a: "<<a<<endl;
			//b is public so it is accessible any where
			cout<<"Value of b: "<<b<<endl;
			//'c' is declared as protected, so it is accessible in sub class
			cout<<"Value of c: "<<c<<endl;
		}
};

// main function
int main(int argc,char *argv[])
{
    if(argc>1) 
	{
		cout<<"\n Usage of file --> \n"
		"\t filename.exe and enter"<<endl<<
		"		or"<<endl<<
		"\t ./filename.out and enter"<<endl;
	}
	else
	{							
		Base d; // create object
		d.show();
		
		Sub_class s; // create object
		s.show();    // Sub class show() function
		
		cout<<"\nAccessing variable Outside the class"<<endl;
		//'a' cannot be accessed as it is private
		//cout<<"value of a: "<<d.a<<endl;
		
		//'b' is public as can be accessed from any where
		cout<<"value of b: "<<d.b<<endl;
		
		//'c' is protected and cannot be accesed here
		//cout<<"value of c: "<<d.c<<endl;
		return 0;
	} 
}


