// ****************************************
// Program Title: Project 6
// Project File: Project_06.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 6/27/18
// program description: sample
/*
For this project, you will write a complete C++ program that performs all of the following tasks. Remember,
your program must contain appropriate comments in order to receive full credit:

(1) Prompt for, read, echo print and open a user defined input file. If the user inputs the name of a file that
will not open, a loop is entered that prints out an appropriate error message, resets the input stream
(see the end of the hints section), prompts for the name of the input file again and tries to open the new
file name. The loop is to continue executing until the user successfully enters the name of a file or types
ctrl-c to terminate the program.

(2) Print out a 5 column heading for the data to be printed

(3) Read every character (tabs, spaces and new-lines are characters) on a line-by-line basis from the input
file and count them as indicated:
a. Count the number of characters on a line that are letters only
b. Count the number of characters on a line that are digits only
c. Count the number of other characters that are neither a letter or a digit

(4) Output the character counts on a line by line basis (counting stops for a line when the new line character
is encountered - be sure to count the new line character)

(5) After reading all lines, output a total line for each column of data printed. Below this line, print out a line
indicating the percent (shown to two decimal places) of the total characters that each column
represents. Run the sample solution to see the output format.

(6) The columns of information printed are: Line number, number of letters, number of digits, number of
other characters and the total number of characters for the line.
*/
// ****************************************
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
using namespace std;

int main()
{

	string inputFileName;
	ifstream inputFile;
	ofstream outputFile;

	cout << endl << "Enter in the name of the input file: ";
	cin >> inputFileName;
	cout << inputFileName << endl << endl;
	inputFile.open(inputFileName.c_str());
	while(inputFile.fail())
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inputFileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		inputFile.clear();
		cout << "Enter in the name of the input file: ";
		cin >> inputFileName;
		cout << inputFileName << endl << endl;
		inputFile.open(inputFileName.c_str());
	}
	int lineNum = 0;
	int letterNum = 0;
	int digitNum = 0;
	int otherNum = 0;
	int total = 0;

	int tempLetterNum = 0;
	int tempDigitNum = 0;
	int tempOtherNum = 0;
	int tempTotal = 0;
	char temp;
	inputFile.get(temp);
	if(inputFile.eof())
	{
		cout << string(13, '*') << " Input File Is Empty " << string(13, '*') << endl;
		cout << "==> The input file is empty." << endl;
		cout << "==> Terminating the program." << endl;
		cout << string(47, '*') << endl << endl;
		return -1;
	}
	else
	{
		cout << left << fixed << setprecision(2);
		cout << setw(15) << "Line number";
		cout << setw(10) << "Letters";
		cout << setw(10) << "Digits";
		cout << setw(10) << "Other";
		cout << setw(10) << "Total" << endl;
		cout << setw(15) << string(string("Line Number").length(), '-');
		cout << setw(10) << string(string("Letters").length(), '-');
		cout << setw(10) << string(string("Digits").length(), '-');
		cout << setw(10) << string(string("Other").length(), '-');
		cout << setw(10) << string(string("Total").length(), '-') << endl;
		if(isdigit(temp))
		{
			tempDigitNum++;
		}
		else if(isalpha(temp))
		{
			tempLetterNum++;
		}
		else
		{
			tempOtherNum++;
		}
		tempTotal++;

	}

	while(inputFile.get(temp))
	{
		tempTotal++;
		if(isdigit(temp))
		{
			tempDigitNum++;
		}
		else if(isalpha(temp))
		{
			tempLetterNum++;
		}
		else
		{
			if(temp == '\n')
			{
				cout << setw(15) << ++lineNum;
				cout << setw(10) << tempLetterNum;
				cout << setw(10) << tempDigitNum;
				cout << setw(10) << ++tempOtherNum;
				cout << setw(10) << tempTotal << endl;
				letterNum += tempLetterNum;
				digitNum += tempDigitNum;
				otherNum += tempOtherNum;
				total += tempTotal;
				tempTotal = 0;
				tempOtherNum = 0;
				tempDigitNum = 0;
				tempLetterNum = 0;
			}
			else
			{
				tempOtherNum++;
			}
		}
	}

	if(tempTotal >= 0 && temp != '\n')
	{
		cout << setw(15) << ++lineNum;
		cout << setw(10) << tempLetterNum;
		cout << setw(10) << tempDigitNum;
		cout << setw(10) << ++tempOtherNum;
		cout << setw(10) << tempTotal << endl;
		letterNum += tempLetterNum;
		digitNum += tempDigitNum;
		otherNum += tempOtherNum;
		total += tempTotal;
		tempTotal = 0;
		tempOtherNum = 0;
		tempDigitNum = 0;
		tempLetterNum = 0;
	}

	cout << string(50, '-') << endl;
	cout << setw(15) << "Totals" << setw(10) << letterNum << setw(10) << digitNum << setw(10) << otherNum << setw(10) << total << endl;
	cout << setw(15) << "Percent" << setw(10) << letterNum / (float)total * 100.f << setw(10) <<
		digitNum / (float)total * 100.f << setw(10) << otherNum / (float)total * 100.f << endl << endl;
	return 0;
}
