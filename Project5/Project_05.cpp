// ****************************************
// Program Title: Project 5
// Project File: Project_05.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 6/20/18
// program description:
/*
For this project, you will  write a complete C++ program that performs all of the following tasks.    
Use variables of Data Type float to contain all numerical values.

(1)Because command line arguments are used, first action of the program is to test to make sure 
that 2 file names were provided.  Use the test if (argc != 3).  If the argc value is not 3, print out 
an error message and what the correct format should be for running the program and terminate 
the program.(see page 4)

(2)Using command line arguments for an input file and output file name (see command line 
argument slides and page 3), open the input file provided as the first command line argument.  
Verify that the file opened successfully.  If it did not open successfully, output an error message 
and terminate the program. 

See page 4 for information on this test.

(3)If the input file is successfully opened, open the output file provided as the second command line argument.  
Verify that the output file opened successfully.  If it did not open successfully, output an error message and terminate.
Use the filename “Bad/file” to cause the open function to fail for the output file.

(4)For steps 1 and 2 output a statement stating the name of the file being opened-see the solution.

(5)The upper case letters A, B and C appear on the first, second and third line of the input file 
respectively.  The input file contains a single occurrence of these letters.  Immediately after 
each letter is a floating point number which must be read, and there may or may not be more 
characters after the numbers on each line

(6)Read in the three numbers and then test to see if any of them are less than 0.  If any are 
negative, determine which ones are negative, output a message as shown in the sample 
solution and terminate the program.

(7)If all numbers are greater than or equal to 0, add them up and determine their average.
From the average determine if the average is High (average >= 75), Medium (average <75 and average >= 25) or Low (average < 25)

(8)Write the numbers read, their sum, their average and the word High, Medium or Low based on the average to the output file -
run the sample solution to see the formatting necessary for the output.  The row of *’s is 47 *’s long and the phrases are in a field width of 35.

(9)Output of the program shallmatch that of the sample solution
*/
// ****************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <climits>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << std::endl << std::string(9, '*') << " Command Line Argument Error " 
			<< std::string(9, '*') << std::endl;
		std::cout << "==> Incorrect number of Command Line Arguments!\n";
		std::cout << "==> Command for running the program is:\n";
		std::cout << "==> ./Project_05 inputFileName  outputFileName" << std::endl;
		std::cout << std::string(47,'*') << std::endl << std::endl;
		return 1;
	}
	
	std::ifstream inFile;
	std::ofstream outFile;
	std::string opener = argv[0];
	std::string inFileName = argv[1];
	std::string outFileName = argv[2];
	
	char delim_char = 'A';
	float a_num;
	float b_num;
	float c_num;
	std::cout << std::endl << "Opening Input File: " << inFileName << std::endl << std::endl;
	inFile.open(inFileName.c_str());
	if(inFile.fail())
	{
		std::cout << std::string(15, '*') << " File Open Error " << std::string(15, '*') << std::endl;
		std::cout << "==> Input file failed to open properly!!\n";
		std::cout << "==> Attempted to open file: " << inFileName << std::endl;
		std::cout << "==> Terminating program!!!\n";
		std::cout << std::string(47, '*') << std::endl << std::endl;
		return 1;
	}
	std::cout << "Opening Output File: " << outFileName << std::endl << std::endl;
	outFile.open(outFileName.c_str());
	if(outFile.fail())
	{
		std::cout << std::string(15, '*') << " File Open Error " << std::string(15, '*') << std::endl;
		std::cout << "==> Output file failed to open properly!!\n";
		std::cout << "==> Attempted to open file: " << outFileName << std::endl;
		std::cout << "==> Terminating program!!!\n";
		std::cout << std::string(47, '*') << std::endl << std::endl;
		return 1;
	}
	inFile.ignore(INT_MAX, delim_char++);
	inFile >> a_num;
	inFile.ignore(INT_MAX, delim_char++);
	inFile >> b_num;
	inFile.ignore(INT_MAX, delim_char++);
	inFile >> c_num;
	if(a_num < 0 || b_num < 0 || c_num < 0)
	{
		std::cout << std::string(15, '*') << " Negative Number " << std::string(15, '*') << std::endl;
		if(a_num < 0.f)
		{
			std::cout << "==> First number is less than 0" << std::endl;
		}

		if(b_num < 0.f)
		{
			std::cout << "==> Second number is less than 0" << std::endl;
		}

		if(c_num < 0.f)
		{
			std::cout << "==> Third number is less than 0" << std::endl;
		}
		std::cout << "==> All numbers should be positive" << std::endl;
		std::cout << "==> Terminating program!!!" << std::endl;
		std::cout << std::string(47, '*') << std::endl << std::endl;
		return 1;
	}
	else
	{
		float sum = a_num + b_num + c_num;
		float avg = sum / 3.f;
		outFile << std::string(47, '*') << std::endl;
		outFile << std::fixed << std::setprecision(2) << std::left;
		outFile << std::setw(35) << "The numbers read are: " << a_num << " " << b_num << " " << c_num << std::endl;
		outFile << std::setw(35) << "The sum of the numbers is: " << sum << std::endl;
		outFile << std::setw(35) << "The average of these numbers is: " << avg << std::endl;
		outFile << std::setw(35) << "This average is: " << (avg >= 75.f ? "High" : avg >= 25.f ? "Medium" : "Low") << std::endl;
		outFile << std::string(47, '*') << std::endl;
	}
	return 0;
}

