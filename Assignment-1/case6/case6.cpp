/*
filename: case4.cpp
details: Program to access given class with two private member vairables int* and char[20]
author: J.P.Prakash
date: 07/04/2020
*/
#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
class Name
{
//declaration of variables in private
private:
	char cName[20];
	int *iNumb;
public:
	//default constructor
	Name()
	{
		cout<<"Default constructor invoked"<<endl;
	}
	//parametrised constructor
	Name(char *str)
	{
		cout<<"Parametrised constructor invoked"<<endl;
		strcpy(cName,str);//coping string
	}
	//Display function
	void Display()
	{
		cout<<"value: "<<*iNumb<<endl;
	}
	//Show function
	void Show()
	{
		cout<<"Name: "<<cName<<endl;
	}
	//overloading oprator'+'
	Name operator+(Name s)
	{
		Name temp=cName;
		strcat(temp.cName,s.cName);	//adding two strings
		return temp;
	}
	//setValue function
	void setValue(int *iVal)
	{
		iNumb=iVal;
	}
	//setName function
	void setName(char cName[])
	{
		cName=cName;
	}
	//destructor 
	~Name()
	{
		cout<<"Destructor invoked"<<endl;
	}
};

int main(int argc,char **argv)
{
	if(argc==2) 
	{
		if(strcmp(argv[1],"-h")==0)     //created a help command
        {
			cout<<"\n Usage of file --> \n"
					"\t filename.exe & enter"<<endl<<
					"\t Program used to access pointer to integer and char variables. "<<endl<<
					"\t insert an integer and any two strings. ";
		}	
	}
	else
	{	
		int iValue; //declaring integer value
		char fname[30],sname[30]; //declaring character value
		cout<<"enter value:";
		cin>>iValue;
		cout<<"First Name: ";
		cin>>fname;
		cout<<"Second Name: ";
		cin>>sname;
		//object declaration for class "Name"
		Name str1(fname);
		Name str2=(sname);
		Name str3;
		Name s;
		str3=str1+str2;
		s.setValue(&iValue);
		s.Display();
		str3.Show();
	}
}
