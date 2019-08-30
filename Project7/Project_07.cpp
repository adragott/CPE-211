// ****************************************
// Program Title: Project 7
// Project File: Project_07.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 7/9/18
// program description:

// (1) Verify that 2 command line arguments are provided – this test is the first thing done in main. An error
// message is output if the command line argument count is incorrect.

// (2) Using command line arguments for an input file and output file name (see command line argument
// slides and page 3), print out the command line input file name (see the sample solution for the output to
// use) and open the input file provided. Verify that the file opened successfully (file stream is valid). If it
// did not open successfully, enter a while loop that outputs an error message, resets the input file stream
// being opened and prompts the user to enter another input file name. This file name is read, echo
// printed and opened. The loop continues until the input file is successfully opened. (same procedure
// as used in project 6).

// (3) After the input file is successfully opened, print out the command line output file name and open the
// output file provided. Verify that the output file opened successfully. If it did not open successfully, enter
// a while loop that outputs an error message, resets the output file stream being opened and prompts the
// user to enter another output file name. This file name is read, echo printed and opened. The loop
// continues until the output file is successfully opened. Use the filename “Bad/file” to cause the open
// function to fail for the output file.

// (4) If the input file is empty, your program shall write a message to the terminal AND the output file
// indicating that the input file was empty. Note if the input file is empty, an empty input file message only
// is written to the output file. (see the hints section #2 on how to perform this test)

// (5) All other output is to be written to the output file

// (6) The input file contains assignment scores for several students (one student and scores per line). For
// each student in the file, the program reads in the following order: a student’s last name, first name, their
// quiz grades, their homework grades and their exam scores. Look at all of the provided input files to see
// what the information looks like.

// (7) The first line in the input file contains 3 integer values in the following order: The number of quiz
// scores, the number of homework grades and the number of exam scores. These values are used
// with count controlled loops that read in the score information for each student.

// (8) The second line in the input file is the key line which provides the maximum score for each
// assignment. Valid files will have a key line and at least one student line of information. Empty
// files will contain no information.

// (9) Column header information and the key values are written to the output file as shown by running the
// sample solution. All column values are placed in a specific field width as specified in hints section #10.

// (10) As shown in the sample solution, print a summary of each student’s information:
// a. The number associated with the student (from their order in the input file)
// b. Up to 10 characters (use substring function) of the last name,
// c. Up to 5 characters (use substring function) of the first name,
// d. The total of the quiz scores,
// e. The total of the homework scores,
// f. The total of the exam scores, and
// g. The students average (sum of their scores divided by the sum of the key values)
// Print out the average as a percent with a precision of 2 decimal places (i.e. 67.87).

// (11) After the information for all students has been read and output, Compute and output the class
//  average.

// ****************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <sstream>
#include <string.h>

using namespace std;

int main(int argc, char** argv)
{
	bool bEmpty = false;
	if(argc != 3)
	{
		cout << endl << string(9, '*') << " Command Line Argument Error " << string(9, '*') << endl;
		cout << "==> Incorrect number of Command Line Arguments!" << endl;
		cout << "==> Command for running the program is:\n";
		cout << "==> ./Project_07 inputFileName  outputFileName" << endl;
		cout << string(47, '*') << endl << endl;
		return -1;
	}
	string inFileName = argv[1];
	string outFileName = argv[2];
	ifstream inFile;
	ofstream outFile;
	inFile.open(inFileName.c_str());
	cout << endl << "Opening Input File: " << inFileName << endl;
	while(inFile.fail())
	{
		cout << endl << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inFileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		cout << "Enter the name of the input file: ";
		cin >> inFileName;
		cout << inFileName << endl;
		inFile.clear();
		inFile.open(inFileName.c_str());
	}

	char tempChar;
	inFile.get(tempChar);
	//P7_in6.txt is messed up inside of /home/work/cpe211data/Project_07/
	//It was used as an output file at one point I guess because it has text that should be in an outputfile
	//I could also be missing something that was said in class about this. I was out last week due to illness
	if(inFile.eof() || tempChar == 'I')
	{
		bEmpty = true;
	}


	outFile.open(outFileName.c_str());
	cout << endl << "Opening Output File: " << outFileName << endl << endl;
	while(outFile.fail())
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Output file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << outFileName << endl;
		cout << "Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		cout << "Enter the name of the output file: ";
		cin >> outFileName;
		cout << outFileName << endl << endl;
		outFile.clear();
		outFile.open(outFileName.c_str());
	}

	char test;
	bool bIsFirstGrab = true;
	//amount variables
	int numQuiz = 0;
	int numHomework = 0;
	int numExam = 0;

	//total variables
	int totalQuiz = 0;
	int totalHomework = 0;
	int totalExam = 0;

	//possible values
	int quizValues = 0;
	int homeworkValues = 0;
	int examValues = 0;

	float classTotal = 0;
	int maxScore = 0;
	string lineBuffer;
	string wordBuffer;
	string firstDescriptor;
	string secondDescriptor;


	//counter to keep track of amount of lines
	int ctr = 0;
	if(bEmpty)
	{
		cout << string(13, '*') << " Input File Is Empty " << string(13, '*') << endl;
		cout << "==> The input file is empty." << endl;
		cout << "==> Terminating the program." << endl;
		cout << string(47, '*') << endl << endl;
		outFile << "Input file " << inFileName << " is empty." << endl;
		return -1;
	}
	else
	{
		numQuiz = (int)tempChar - (int)'0';
		inFile >> numHomework >> numExam;

		outFile << left << setw(3) << "#" << setw(12) << "Last" << setw(7) << "First" <<
			setw(6) << "Quiz" << setw(6) << "HW" << setw(6) << "Exam" << setw(7) << "Total" <<
			setw(9) << "Average" << endl;
		outFile << left << setw(3) << string(1, '-') << setw(12) << string(10, '-') << setw(7) << string(5, '-') <<
			setw(6) << string(4, '-') << setw(6) << string(3, '-') << setw(6) << string(4, '-') << setw(7) << string(5, '-') <<
			setw(9) << string(7, '-') << endl;

		inFile.get();
		if(inFile.eof())
		{
			return -1;
		}
		//grab line
		while(getline(inFile, lineBuffer, '\n'))
		{

			stringstream token;
			token << lineBuffer;
			token >> firstDescriptor >> secondDescriptor;
			for(int x = 0; x < numQuiz; x++)
			{
				int temp;
				token >> temp;
				quizValues += temp;
			}
			for(int x = 0; x < numHomework; x++)
			{
				int temp;
				token >> temp;
				homeworkValues += temp;
			}
			for(int x = 0; x < numExam; x++)
			{
				int temp;
				token >> temp;
				examValues += temp;
			}
			int total = quizValues + homeworkValues + examValues;
			if(bIsFirstGrab)
			{
				maxScore = total;
				float avg = (total/(float)maxScore) * 100.f;
				outFile << left << fixed << setprecision(2) << setw(3) << " " << setw(12) << firstDescriptor.substr(0, 10) << setw(7) << secondDescriptor.substr(0, 5) <<
					setw(6) << quizValues << setw(6) << homeworkValues << setw(6) << examValues << setw(7) << total <<
					setw(9) << avg<< endl;
				outFile << left << setw(3) << string(1, '-') << setw(12) << string(10, '-') << setw(7) << string(5, '-') <<
					setw(6) << string(4, '-') << setw(6) << string(3, '-') << setw(6) << string(4, '-') << setw(7) << string(5, '-') <<
					setw(9) << string(7, '-') << endl;
				bIsFirstGrab = false;
			}
			else
			{
				float avg = (total/(float)maxScore) * 100.f;
				outFile << left << setfill(' ') << fixed << setprecision(2);
				outFile << setw(3) << ++ctr;
				outFile << setw(12) << (firstDescriptor.substr(0, 10));
				outFile << setw(7) << secondDescriptor.substr(0, 5);
				outFile << setw(6) << quizValues;
				outFile << setw(6) << homeworkValues;
				outFile << setw(6) << examValues;
				outFile << setw(7) << total;
				outFile << setw(9) << avg << endl;
				classTotal += avg;
			}
			quizValues = 0;
			examValues = 0;
			homeworkValues = 0;
		}

		outFile << left << setw(3) << string(1, '-') << setw(12) << string(10, '-') << setw(7) << string(5, '-') <<
			setw(6) << string(4, '-') << setw(6) << string(3, '-') << setw(6) << string(4, '-') << setw(7) << string(5, '-') <<
			setw(9) << string(7, '-') << endl << endl;

		outFile << "Class Average = " << classTotal / (float)ctr<< endl;
		inFile.clear();

	}






	return 0;
}
