/*
filename: MatrixCheckRepeating.cpp
details: matrix program to check either the given input contains repeatation or not. if found any it will be replaced with '*'.
author: J.P.Prakash
date: 11/05/2020
*/

#include<iostream>
#define MAX 10

using namespace std;
class Matrix{
	protected:
		int iRows, iCols, iChoice;
		char array[MAX][MAX];
		char trans[MAX][MAX];
		char temp[MAX][MAX];	
		char iContinue;
	public:	
		void readArray(char array[MAX][MAX],int iRows,int iCols);
		void display(char array[MAX][MAX],int iRows,int iCols);
		Matrix checkRepeating(char array[MAX][MAX],int iRows,int iCols);
		Matrix traverse(char array[MAX][MAX], char trans[MAX][MAX], int iRows, int iCols);
		Matrix diagonalCheck(char array[MAX][MAX], int iRows, int iCols);	
};


int main(){
	
	Matrix data;
	int iRows, iCols, iChoice;
	char array[MAX][MAX];
	char trans[MAX][MAX];
	char temp[MAX][MAX];	
	char iContinue;
	
	cout<<"Enter the number of Rows : ";
    cin>>iRows;
    cout<<"Enter the number of Columns : ";
    cin>>iCols;
    
	data.readArray(array,iRows,iCols);	//calls readArray function
	data.display(array,iRows,iCols);		//calls display function
	
	do{
		cout<<"\n Chose an option : "<<endl;
	    cout<<"\t 1. row check"<<endl<<
			"\t 2. column check"<<endl<<
			"\t 3. Adjecent check"<<endl<<
			"\t 4. read Data"<<endl;
	    cin>>iChoice;
	    cout<<endl;
	    switch(iChoice) {
	    	case 1:
	    		cout<<"\n Row wise check : "<<endl;
				data.checkRepeating(array, iRows, iCols);	//calls checkRepeating function
				data.display(array, iRows, iCols);
	    		break;
	    	case 2:
	    		cout<<"\n Column wise check : "<<endl;
	    		data.traverse(array, trans, iRows, iCols);	//calls traverse function
	    		data.checkRepeating(trans, iRows, iCols);	//calls checkRepeating function
				data.traverse(trans, temp, iRows, iCols);	//recalls traverse function
	    		data.display(temp, iRows, iCols);
	    		break;	
	    	case 3:
	    		cout<<"\n Diagonal wise check : "<<endl;
	    		data.diagonalCheck(array,iRows,iCols);		//calls diagonalCheck function
	    		data.display(array, iRows, iCols);
	    		break;
	    	case 4:
	    		cout<<"\n Enter Input Data : "<<endl;
	    		data.readArray(array,iRows,iCols);			//calls readArray function
	    		data.display(array,iRows,iCols);
	    		break;
			default: "invalid option";
				break;
		}
		cout<<"do want to continue (Y/N) : ";
		cin>>iContinue;
	}while(iContinue == 'y');
	return 0;
}

/* function reads input and check either the input is 0's and 1's or not */
void Matrix::readArray(char array[MAX][MAX],int iRows,int iCols){
	
    for(int i=0; i<iRows; i++)
    {
        for(int j=0; j<iCols; j++)
        {
            bool check=true;
            cout<<"Enter ("<<i<<","<<j<<") : ";
            cin>>array[i][j];
            while(check)		//check either the input is 1's and 0's or not
            {
                if(array[i][j]=='0' || array[i][j]=='1')	
                {
                    check=false;
                }
                else
                {
                    cout<<"please enter 0 or 1.."<<endl;
                    cout<<"Enter ("<<i<<","<<j<<") : ";
                    cin>>array[i][j];
                }
            }
        }
    }
}

/*function displays the data with in the Matrix Array*/
void Matrix::display(char array[MAX][MAX],int iRows,int iCols){
	cout<<endl;
	for(int i=0; i<iRows; i++)
	{
		for(int j=0;j<iCols;j++)
		{
			cout<<array[i][j]<<"\t";
		}
		cout<<endl;
	}
}

/* checks the Matrix array row wise and replaces the data with '*' when a repeatation occurs*/
Matrix Matrix::checkRepeating(char array[MAX][MAX],int iRows,int iCols){
   	int count;
    int iCols1;
    int temp;
    for(int i=0; i<iRows; i++)
    {
    	count=0;
    	iCols1=iCols;
        temp = array[i][0];						
		/*assigns temp with the initial position of matrix and based on the following conditions if repeations occured it will be replaced with '*' */
        for(int j=1; j<iCols1; )						
        {
            if(temp == array[i][j])
            {
                for(int k=j; k<iCols1-1; k++)
                {
                    array[i][k] = array[i][k+1];
                }
                iCols1--;
                if(temp != array[i][j])
                {
                    temp = array[i][j];
                     j++;
                }                
                count++;
            }
            else
            {
                temp = array[i][j];
                j++;
            }
        }
        while(count>0)
        {
            array[i][iCols-count]='*';
            count--;
        }
    }
}

/*Converst the matrix array's data into tarvers*/
Matrix Matrix::traverse(char array[MAX][MAX], char trans[MAX][MAX], int iRows, int iCols){
	int i,j;
    for(i=0;i<iRows;i++)
    {
        for(j=0;j<iCols;j++)
        {
            trans[j][i] = array[i][j];
        }
    }
}

/*checks the matrix arrya data diagonally for repeatations and replace it with '*' */
Matrix Matrix::diagonalCheck(char array[MAX][MAX], int iRows, int iCols){
	int temp;
	int count=0;
    int iRows1=iRows,iCols1=iCols;
    
    temp=array[0][0];
    /*checks the left side diagonally for repeatations data with '*' */
    for(int i=1, j=1; i<iRows1; i++)
    {
        if(temp == array[i][j])
        {             
            for(int x=i,y=j; x<iRows1-1; x++,y++)
            {
                array[x][y] = array[x+1][y+1];
            }  
			iRows1--;          
            if(temp != array[i][j])
            {
                temp = array[i][j];
            }            
            count++;
        }
        else
        {
            temp = array[i][j];
        }
    }
    while(count>0)
    {
        array[iRows-count][iCols-count]='*';
        count--;
    }

	/*checks the right side diagonally for repeatations data with '*' */
	temp = array[0][iCols-1];
    count=0;
    iRows1=iRows;
	iCols1=iCols;
    for( int i=1,j=iCols-2; i<iRows1; i++,j--)
    {
        if(temp == array[i][j])
        {
            for(int x=i,y=j; x<iRows1-1; x++,y--)
            {
                array[x][y] = array[x+1][y-1];                
            }
            iRows1--;
            if(temp != array[i][j])
            {
                temp = array[i][j];
            }
            count++;
        }
        else
        {
            temp = array[i][j];
        }
    }
    
    for(int x=iRows-1, y=0;count>0; x--,y++)
    {
        array[x][y]='*';
        count--;        
    }
}
