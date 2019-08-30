// ****************************************
// Program Title: Project 11
// Project File: Project_11.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 7/31/18
// program description:
/*
This project involves working with a one-dimensional array. The maximum size for the one
dimensional array is 50 elements. The program will read floating point numbers from an input
file and store them in a one dimensional array. The following statistical values will be
determined for the numbers read from the input file: The Mean (Average), The median (middle
value), the standard deviation and the variance. Formulas for these values are shown on page 4.

When opening the input file, all code is to be placed in the function that opens the input file. The
program is to continually prompt for an input file and attempt to open it until a file is successfully
opened. Look at the output of the sample solution for examples of invalid input files.

Information in the input file consists of 1 integer and several floating point numbers (1 per line).
The first number in the input file is an integer indicating the number of floating point values to
read. This number will be between 1 and 50 inclusive and no error checking is required.

The program is to read in the integer value (use extraction) and then use that value as the limit
for the loop control variable when reading in the floating point values (use extraction) into the
array. Reading of the values is to be performed in a function. No check for successful reading
is required. You can assume that all numbers are correct in the input file. Furthermore, there
will not be an empty file test requirement.

*/
// What program does.
// ****************************************
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

//return status enum for performing operations
enum STATUS { SUCCESS = 0, FAILURE = 1 };

STATUS fillArray(float* arr, int numValues, ifstream &inputFileStream);
STATUS openInputFile(ifstream &inputFileStream, string &inputName);
float getAvg(const float* arr, int numValues);
float getVariance(const float* arr, int numValues, float avg);
float getDeviation(float variance);
void sortArray(float* arr, int numValues);
float getMedian(const float* arr, int numValues);

int main()
{
	float inputValues[50] = {0};
	STATUS fs = SUCCESS;
	ifstream inputStream;
	string inputFileName;
	if((fs = openInputFile(inputStream, inputFileName)) != SUCCESS)
	{
		do {
			cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
			cout << "==> Input file failed to open properly!!" << endl;
			cout << "==> Attempted to open file: " << inputFileName << endl;
			cout << "==> Please try again..." << endl;
			cout << string(47, '*') << endl;
			fs = openInputFile(inputStream, inputFileName);
		} while(fs != SUCCESS);
	}
	int numValues = 0;
	inputStream >> numValues;
	STATUS arrStatus = SUCCESS;
	if((arrStatus = fillArray(inputValues, numValues, inputStream)) != SUCCESS)
	{
		//this was more for debugging
		//cout << "Array fill failed" << endl;
		return -1;
	}

	cout << string(15, '*') << " File Statistics " << string(15, '*') << endl;
	cout << string(47, '*') << endl;
	sortArray(inputValues, numValues);
	cout << left << fixed << setprecision(3);
	cout << setw(25) << setfill('.') << "Number of Values" << numValues << endl;
	float avg = getAvg(inputValues, numValues);
	cout << setw(25) << setfill('.') << "Average" << avg << endl;
	float median = getMedian(inputValues, numValues);
	cout << setw(25) << setfill('.') << "Median" << median << endl;
	float var = getVariance(inputValues, numValues, avg);
	cout << setw(25) << setfill('.') << "Variance" << var << endl;
	float dev = getDeviation(var);
	cout << setw(25) << setfill('.') << "Standard Deviation" << dev << endl;
	cout << string(47, '*') << endl;

	return 0;
}

STATUS openInputFile(ifstream &inputFileStream, string &inputName)
{
	inputFileStream.clear();
	cout << endl << "Enter the name of the input file (ctrl-c to exit): ";
	cin >> inputName;
	cout << inputName << endl << endl;
	inputFileStream.open(inputName.c_str());
	if(inputFileStream.fail())
	{
		return FAILURE;
	}
	return SUCCESS;
}

STATUS fillArray(float* arr, int numValues, ifstream &inputFileStream)
{
	for(int x = 0; x < numValues; x++)
	{
		if(inputFileStream.eof())
		{
			return FAILURE;
		}
		inputFileStream >> arr[x];
	}
	return SUCCESS;
}

float getAvg(const float* arr, int numValues)
{
	double sum = 0;
	for(int x = 0; x < numValues; x++)
	{
		sum += (double)arr[x];
	}
	return (float)((float)sum/(float)numValues);
}

float getVariance(const float* arr, int numValues, float avg)
{
	double sum = 0;
	for(int x = 0; x < numValues; x++)
	{
		sum += pow((arr[x] - avg), 2);
	}
	return (float)((1/(float)numValues) * sum);
}

float getDeviation(float variance)
{
	return sqrt(variance);
}

void sortArray(float* arr, int numValues)
{
	for(int x = 0; x < numValues - 1; x++)
	{
		for(int z = x + 1; z < numValues; z++)
		{
			if(arr[x] > arr[z])
			{
				float temp = arr[x];
				arr[x] = arr[z];
				arr[z] = temp;
			}
		}
	}
}

float getMedian(const float* arr, int numValues)
{
	float ret = 0.f;
	if(numValues % 2 == 0)
	{
		ret = (arr[(numValues/2)] + arr[(numValues/2) - 1])/2.f;
	}
	else
	{
		ret = arr[numValues/2];
	}
	return ret;

}
