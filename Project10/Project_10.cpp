// ****************************************
// Program Title: Project 10
// Project File: Cpp_header.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 7/26/18
// program description:
/*
Write a program that opens an input file that contains one or more sets of a code followed by
one or two 3x3 matrices of integer values. The program reads the code that indicates what
action to perform, and then reads one (for Determinant or Transpose) or two (for addition,
subtraction or multiplication) 3x3 matrices. The task to perform and its code are the following.
Code Task
	1 Determinant (requires 1 matrix)
	2 Transpose (requires 1 matrix)
	3 Addition (requires 2 matrices)
	4 Subtraction (requires 2 matrices)
	5 Multiplication (requires 2 matrices)
The program is to continue to read a code followed by the appropriate number of matrices until all
entries in the input file are processed. After reading the code and the matrix(ces), the output of
the program is a description of the action to be performed, the input matrix(ces) and the result
matrix. Run the sample solution to see the input and output order and information


*/
// ****************************************
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

enum FSTATUS
{
	FSUCCESS,
	FFAILURE
};

enum MATRIX_OP
{
	//req 1 matrix
	DETERMINANT = 1,
	//req 1 matrix
	TRANSPOSE = 2,
	//req 2 matrix
	ADDITION = 3,
	//req 2 matrix
	SUBTRACTION = 4,
	//req 2 matrix
	MULTIPLICATION = 5
};

typedef int matrix[3][3];

FSTATUS openInputFile(ifstream &istream, string &inputName);
void printMatrix(const matrix mat);
void readMatrix(ifstream &istream, matrix ret);
void addMatrix(const matrix mat1, const matrix mat2, matrix ret);
//Pick which row you'd like to find the determinant from even though it really doesn't matter =(
//pick from 0-2, not 1-3
int detMatrix(const matrix mat, int row);
void trnspMatrix(const matrix mat, matrix ret);
void multMatrix(const matrix mat1, const matrix mat2, matrix ret);
void subMatrix(const matrix mat1, const matrix mat2, matrix ret);

int main(int argc, char** argv)
{
	string inputFileName;
	ifstream inputStream;

	//file return status
	FSTATUS fret;

	if((fret = openInputFile(inputStream, inputFileName)) != FSUCCESS)
	{
		//handle bad file open
		do {
			cout << endl << string(15,'*') << " File Open Error " << string(15,'*') << endl;
			cout << "==> Input file failed to open properly!!" << endl;
			cout << "==> Attempted to open file: " << inputFileName << endl;
			cout << "==> Please try again..." << endl;
			cout << string(47,'*') << endl;
			inputStream.clear();
			fret = openInputFile(inputStream, inputFileName);
		} while(fret != FSUCCESS);
	}

	//Matrix A
	matrix matA;
	//Matrix B
	matrix matB;
	//Return Matrix
	matrix retMatrix;


	int readMode = 0;
	inputStream >> readMode;
	cout << "Read mode: " << readMode << endl;
	bool bExit = false;
	do
	{
		MATRIX_OP op = static_cast<MATRIX_OP>(readMode);
		switch(op)
		{
			case DETERMINANT:
			cout << endl << string(47,'*') << endl;
			cout << left;
			cout << string(15, '*') << setfill('*') << setw(32)
				<< " Find Determinant " << setfill(' ') << endl << endl;
				readMatrix(inputStream, matA);
				cout << "Input matrix:" << endl;
				printMatrix(matA);
				cout << endl;
				cout << "The determinant is: " << detMatrix(matA, 0) << endl;
				break;
			case TRANSPOSE:
				cout << endl << string(47,'*') << endl;
				cout << string(15,'*') << " Find Transpose ****************" << endl << endl;
				readMatrix(inputStream, matA);
				cout << "Input matrix:" << endl;
				printMatrix(matA);
				trnspMatrix(matA, retMatrix);
				cout << endl << "The transpose is:" << endl;
				printMatrix(retMatrix);
				break;
			case ADDITION:
				cout << endl << string(47,'*') << endl;
				cout << string(15,'*') << " Add Two Matrices **************" << endl << endl;
				readMatrix(inputStream, matA);
				cout << "Matrix A:" << endl;
				printMatrix(matA);
				cout << endl;
				readMatrix(inputStream, matB);
				cout << "Matrix B:" << endl;
				printMatrix(matB);
				cout << endl;
				addMatrix(matA, matB, retMatrix);
				cout << "Matrix A + Matrix B:" << endl;
				printMatrix(retMatrix);
				break;
			case SUBTRACTION:
				cout << endl << string(47,'*') << endl;
				cout << string(15,'*') << " Subtract Two Matrices *********" << endl << endl;
				readMatrix(inputStream, matA);
				cout << "Matrix A:" << endl;
				printMatrix(matA);
				cout << endl;
				cout << "Matrix B:" << endl;
				readMatrix(inputStream, matB);
				printMatrix(matB);
				cout << endl;
				subMatrix(matA, matB, retMatrix);
				cout << "Matrix A - Matrix B:" << endl;
				printMatrix(retMatrix);
				break;
			case MULTIPLICATION:
				cout << endl << string(47,'*') << endl;
				cout << string(15,'*') << " Multiply Two Matrices *********" << endl << endl;
				readMatrix(inputStream, matA);
				cout << "Matrix A:" << endl;
				printMatrix(matA);
				cout << endl;
				readMatrix(inputStream, matB);
				cout << "Matrix B:" << endl;
				printMatrix(matB);
				cout << endl;
				cout << "Matrix A * Matrix B:" << endl;
				multMatrix(matA, matB, retMatrix);
				printMatrix(retMatrix);
				break;
			default:
				break;
		}
		cout << endl << string(15,'*') << " Task Finished *****************" << endl;
		cout << string(47,'*') << endl;
		inputStream >> readMode;
		if(inputStream.fail())
		{
			bExit = true;
		}
	}while(!bExit);

	return 0;
}

FSTATUS openInputFile(ifstream &istream, string &inputName)
{
	cout << endl << "Enter name of input file or Control-C to quit program: ";
	cin >> inputName;
	cout << inputName << endl;
	istream.open(inputName.c_str());
	if(istream.fail())
	{
		return FFAILURE;
	}
	return FSUCCESS;
}

void printMatrix(const matrix mat)
{
	for(int r = 0; r < 3; r++)
	{
		cout << left;
		for(int c = 0; c < 3; c++)
		{
			cout << setfill(' ') << setw(6) << mat[r][c];
		}
		cout << endl;
	}
}
void readMatrix(ifstream &istream, matrix ret)
{

	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			istream >> ret[r][c];
		}
		istream.ignore(16, '\n');
	}
}
void addMatrix(const matrix mat1, const matrix mat2, matrix ret)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			ret[r][c] = mat1[r][c] + mat2[r][c];
		}
	}
}

int detMatrix(const matrix mat, int row)
{

	int z = 0;
	for(int c = 0; c < 3; c++)
	{
		//doing this hurt my brain
		//but it was still cool
		//I worked on this line for roughly 4 hours
		z += (mat[row][c] * ((mat[(row + 1) % 3][(c + 1) % 3] * mat[(row + 2) % 3][(c + 2) % 3]) - (mat[(row + 2) % 3][(c + 1) % 3] * mat[(row + 1)%3][(c + 2)%3])));
	}
	return z;
}
void multMatrix(const matrix mat1, const matrix mat2, matrix ret)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			ret[r][c] = 0;
			for(int x = 0; x < 3; x++)
			{

				ret[r][c] += (mat1[r][x] * mat2[x][c]);
			}
		}
	}
}
void subMatrix(const matrix mat1, const matrix mat2, matrix ret)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			ret[r][c] = mat1[r][c] - mat2[r][c];
		}
	}
}
void trnspMatrix(const matrix mat, matrix ret)
{
	for(int r = 0; r < 3; r++)
	{
		for(int c = 0; c < 3; c++)
		{
			ret[r][c] = mat[c][r];
		}
	}
}
