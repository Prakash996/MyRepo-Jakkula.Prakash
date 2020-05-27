/*
filename: MatrixCheckRepeating.cpp
details: matrix program to check either the given input contains repeatation or not. if found any it will be replaced with '*'.
author: J.P.Prakash
date: 11/05/2020
*/

#include<iostream>
#include<string.h>
#define MAX 10

using namespace std;
class Matrix{
	public:
		int iRows, iCols;
		char matrix[MAX][MAX];
		char traverseMatrix[MAX][MAX];	
		
	public:	
		Matrix(){
			this->iRows=iRows;
			this->iCols=iCols;
		}
		void readMatrix(char matrix[MAX][MAX],int iRows,int iCols);
		void display(char matrix[MAX][MAX],int iRows,int iCols);
		Matrix checkRepeating(char matrix[MAX][MAX],int iRows,int iCols);
		Matrix traverse(char matrix[MAX][MAX], char traverseMatrix[MAX][MAX], int iRows, int iCols);
		Matrix diagonalCheck(char matrix[MAX][MAX], int iRows, int iCols);	
};


int main(int argc,char *argv[]){
	if(argc==2) 
	{
		if(strcmp(argv[1],"-h")==0)     //created a help command
        {
			cout<<"\n Usage of file --> \n"
					"\t filename.exe & enter"<<endl<<
					"\t -Enter the number of rows & number of columns "<<endl<<
					"\t -Enter data into the array "<<endl<<
					"\t -choose the option to perform certain operation "<<endl<<
					"Note: please don't give any spaces as input as the code maybe fall into infinite loop."<<endl;
		}	
	} else {
		Matrix *data=new Matrix();
		//int iRows, iCols, 
		int iChoice;
		char matrix[MAX][MAX];
		char traverseMatrix[MAX][MAX];	
		char iContinue;
		
		cout<<"Enter the number of Rows : ";
	    cin>>data->iRows;
		cout<<"Enter the number of Columns : ";
	    cin>>data->iCols;
	    
		data->readMatrix(matrix,data->iRows,data->iCols);	//calls readMatrix function
		data->display(matrix,data->iRows,data->iCols);		//calls display function
		
		do {
			cout<<"\n Chose an option : "<<endl;
		    cout<<"\t 1. row check"<<endl<<
				"\t 2. column check"<<endl<<
				"\t 3. Adjecent check"<<endl<<
				"\t 4. re-enter inputs"<<endl;
		    cin>>iChoice;
		    cout<<endl;
		    switch(iChoice) {
		    	case 1:
		    		cout<<"\n Row wise check : "<<endl;
					data->checkRepeating(matrix, data->iRows, data->iCols);	//calls checkRepeating function
					data->display(matrix, data->iRows, data->iCols);
		    		break;
		    	case 2:
		    		cout<<"\n Column wise check : "<<endl;
		    		data->traverse(matrix, traverseMatrix, data->iRows, data->iCols);	//calls traverse function
		    		data->checkRepeating(traverseMatrix, data->iRows, data->iCols);	//calls checkRepeating function
					data->traverse(traverseMatrix, matrix, data->iRows, data->iCols);	//recalls traverse function
		    		data->display(matrix, data->iRows, data->iCols);
		    		break;	
		    	case 3:
		    		cout<<"\n Diagonal wise check : "<<endl;
		    		data->diagonalCheck(matrix, data->iRows, data->iCols);		//calls diagonalCheck function
		    		data->display(matrix, data->iRows, data->iCols);
		    		break;
		    	case 4:
		    		cout<<"\n Enter Input Data : "<<endl;
		    		data->readMatrix(matrix, data->iRows, data->iCols);			//calls readMatrix function
		    		data->display(matrix, data->iRows, data->iCols);
		    		break;
				default: "invalid option";
					break;
			}
			cout<<"do want to continue (Y/N) : ";
			cin>>iContinue;
		} while(iContinue == 'y');
		
		delete[] data;
		return 0;
	}	
}

/* function reads input and check either the input is 0's and 1's or not */
void Matrix::readMatrix(char matrix[MAX][MAX],int iRows,int iCols){
	
    for(int countRow=0; countRow<iRows; countRow++)
    {
        for(int countColumn=0; countColumn<iCols; countColumn++)
        {
            bool checkInput=true;
            cout<<"Enter ("<<countRow<<","<<countColumn<<") : ";
            cin>>matrix[countRow][countColumn];
            while(checkInput)		//check either the input is 1's and 0's or not
            {
                if(matrix[countRow][countColumn]=='0' || matrix[countRow][countColumn]=='1')	
                {
                    checkInput=false;
                }
                else
                {
                    cout<<"please enter 0 or 1.."<<endl;
                    cout<<"Enter ("<<countRow<<","<<countColumn<<") : ";
                    cin>>matrix[countRow][countColumn];
                }
            }
        }
    }
}

/*function displays the data with in the Matrix Array*/
void Matrix::display(char matrix[MAX][MAX],int iRows,int iCols){
	cout<<endl;
	for(int countRow=0; countRow<iRows; countRow++)
	{
		for(int countColumn=0; countColumn<iCols; countColumn++)
		{
			cout<<matrix[countRow][countColumn]<<"\t";
		}
		cout<<endl;
	}
}

/* checks the Matrix array row wise and replaces the data with '*' when a repeatation occurs*/
Matrix Matrix::checkRepeating(char matrix[MAX][MAX],int iRows,int iCols){
   	int countRepetition;
    int iCols1;
    int temp;
    for(int countRow=0; countRow<iRows; countRow++)
    {
    	countRepetition=0;
    	iCols1=iCols;
        temp = matrix[countRow][0];						
		/*assigns temp with the initial position of matrix and based on the following conditions if repeations occured it will be replaced with '*' */
        for(int countColumn=1; countColumn<iCols1;)						
        {
            if(temp == matrix[countRow][countColumn])
            {
                for(int changeData=countColumn; changeData<iCols1-1; changeData++)
                {
                    matrix[countRow][changeData] = matrix[countRow][changeData+1];
                }
                iCols1--;
                if(temp != matrix[countRow][countColumn])
                {
                    temp = matrix[countRow][countColumn];
                    countColumn++;
                }                
                countRepetition++;
            }
            else
            {
                temp = matrix[countRow][countColumn];
                countColumn++;
            }
        }
        while(countRepetition>0)
        {
            matrix[countRow][iCols-countRepetition]='*';
            countRepetition--;
        }
    }
}

/*Converst the matrix array's data into tarvers*/
Matrix Matrix::traverse(char matrix[MAX][MAX], char traverseMatrix[MAX][MAX], int iRows, int iCols){
    for(int countRow=0; countRow<iRows; countRow++)
    {
        for(int countColumn=0; countColumn<iCols; countColumn++)
        {
            traverseMatrix[countColumn][countRow] = matrix[countRow][countColumn];
        }
    }
}

/*checks the matrix arrya data diagonally for repeatations and replace it with '*' */
Matrix Matrix::diagonalCheck(char matrix[MAX][MAX], int iRows, int iCols){
	int temp;
	int countRepetition=0;
    int iRows1=iRows,iCols1=iCols;
    
    temp=matrix[0][0];
    /*checks the left side diagonally for repeatations data with '*' */
    for(int countRow=1, countColumn=1; countRow<iRows1; countRow++, countColumn++)
    {
        if(temp == matrix[countRow][countColumn])
        {             
            for(int changeRow=countRow, changeColumn=countColumn; changeRow<iRows1-1; changeRow++, changeColumn++)
            {
                matrix[changeRow][changeColumn] = matrix[changeRow+1][changeColumn+1];
            }  
			iRows1--;
            if(temp != matrix[countRow][countColumn])
            {
                temp = matrix[countRow][countColumn];
            }            
            countRepetition++;
        }
        else
        {
            temp = matrix[countRow][countColumn];
        }
    }
    while(countRepetition>0)
    {
        matrix[iRows-countRepetition][iCols-countRepetition]='*';
        countRepetition--;
    }

	/*checks the right side diagonally for repeatations data with '*' */
    countRepetition=0;
    iRows1=iRows;
	iCols1=iCols;	
	temp = matrix[0][iCols1-1];
    for( int countRow=1, countColumn=iCols1-2; countRow<iRows1; countRow++, countColumn--)
    {
        if(temp == matrix[countRow][countColumn])
        {
            for(int changeRow=countRow, changeColumn=countColumn; changeRow<iRows1-1; changeRow++, changeColumn--)
            {
                matrix[changeRow][changeColumn] = matrix[changeRow+1][changeColumn-1];                
            }
            iRows1--;
            if(temp != matrix[countRow][countColumn])
            {
                temp = matrix[countRow][countColumn];
            }
            countRepetition++;
        }
        else
        {
            temp = matrix[countRow][countColumn];
        }
    }
    
    for(int changeRow=iRows-1, changeColumn=0; countRepetition>0 ; changeRow--, changeColumn++)
    {
        matrix[changeRow][changeColumn]='*';
        countRepetition--;        
    }
}
