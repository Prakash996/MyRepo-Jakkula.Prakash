/*
filename: case5.cpp
details: Program to show different way to initialize the private member variables in a class & Order of the construction and destruction of objects with and without virtual. 
author:J.P.Prakash
date:08/04/2020
*/

#include <iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

// forward declaration of class B. so, that it can specify in friend declaration.
class B;
class A 
{
    private:
      	int iNumA; // declaring int iNumA as Private variable.
    public:
    	//constructor for class A
      	A()
		{ 
			cout<<" Class A constructor called"<<endl; 
      		setA();
    		getA();
	  	}
	  	
	  	//setter function
	  	void setA() 
		{
	  		cout<<"\tEnter A value: ";
    		cin>>iNumA;
		} 
		//getter function
		int getA()
		{
			return iNumA;
		}
		// destructorclass for class A with virtual keyword
	  	virtual ~A() 
		{
	  		cout<<"\n Class A destructor called"<<endl;
		}
		
      // friend function declaration
      friend int add(A, B);
};

class B 
{
    private:
       int iNumB;
    public:
       	B()
	   	{ 
	   		cout<<" Class B constructor called"<<endl;
	   		/*this->numB=numB;
			cout<<"\tEnter B value: ";
    		cin>>numB;	*/
    		setB();
    		getB();
	   	}
	   	void setB(){
	  		cout<<"\tEnter B value: ";
    		cin>>iNumB;
		  }
		int getB(){
			return iNumB;
		}
		// destructorclass for class B without any virtual keyword
	    ~B()
	   	{
			cout<<"\n Class B destructor called"<<endl;
		}
       	// friend function declaration
       	friend int add(A , B);
};

// Function add() is the friend function of classes A and B
// that accesses the member variables iNumA and iNumB
int add(A objA, B objB)
{
   	return (objA.iNumA + objB.iNumB);
}

int main(int argc,char *argv[])
{
	if(argc>=2)
    {
        if(strcmp(argv[1],"-h")==0)     //created a help command
        {
            cout<<"Program is used to access private variable in a class & Order of the construction and destruction of objects with and without virtual"<<endl;
            cout<<"Enter any two numbers as input. ";
        }
    }
    else
    {
	    A objA;
	    B objB;
	    
	    cout<<"\n Sum: "<< add(objA, objB) <<endl;
	}
	return 0;
}
