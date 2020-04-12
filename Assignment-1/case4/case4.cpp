/*
filename: case4.cpp
details: Program to demonstrate access specifiers
author: J.P.Prakash
date: 07/04/2020
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Base
{
	private:   // declaring variables a,b,c as private, public, protected.
		int a;
	public:
		int b;
	protected:
		int c;
	public:
	
		void show()
		{
			cout<<"\nEnter any 3 values for base class: "<<endl;
				//cout<<"Enter A: ";
				cin>>a;
				//cout<<"Enter B: ";
				cin>>b;
				//cout<<"Enter C: ";
				cin>>c;
			//Every members can be access here, same class
			cout<<"\nAccessing variable within the class"<<endl;
			
			cout<<"Value of a: "<<a<<endl;
			cout<<"Value of b: "<<b<<endl;
			cout<<"Value of c: "<<c<<endl;
		}
};

class Sub_class: public Base
{
	public:
		void show()
		{
			cout<<"\nEnter any 2 values for sub_class: "<<endl;
				cin>>b;
				cin>>c;
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
    if(argc==2) 
	{
		if(strcmp(argv[1],"-h")==0)     //created a help command
        {
			cout<<"\n Usage of file --> \n"
					"\t filename.exe & enter"<<endl<<
					" Program used to demonstrate different access specifiers "<<endl;
		}	
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
		cout<<"value of b: "<<d.b<<endl; //can also access sub-class b variable  's.b'
		
		//'c' is protected and cannot be accesed here
		//cout<<"value of c: "<<d.c<<endl;
		return 0;
	} 
}
