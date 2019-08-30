// ****************************************
// Program Title: Sample header file
// Project File: Cpp_header.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 6/7/18
// program description: sample
// What program does.
// ****************************************
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>

using namespace std;

void printMenu();
int getInput();
bool openInputFile(ifstream &stream, const string &inputName);
bool openOutputFile(ofstream &stream, const string &inputName);
string compress(const string &text);
string decompress(const string &text);
bool getDataFromFile(ifstream &stream, string &istring);
string getline__();

int main()
{
	cout << endl;
	printMenu();
	cout << endl << "Input your selection now: ";
	int i = getInput();
	cout << (isalpha(i) ? i + '0' : i)  << endl << endl;
	int numi = i;
	while(numi != 0)
	{
		if((numi == 1) || (numi == 2))
		{
			//handle input decision
			ifstream inputStream;
			cout << "Enter the name of the input file: ";
			string inputStreamName = getline__();
			cout << inputStreamName << endl << endl;
			ofstream outputStream;
			string outputStreamName;
			if(openInputFile(inputStream, inputStreamName))
			{
				cout << "Enter the name of the output file: ";
				outputStreamName = getline__();
				cout << outputStreamName << endl << endl;
				if(numi == 1)
				{
					//compression selected
					if(openOutputFile(outputStream, outputStreamName))
					{
						string text;
						//if input is not empty
						if(getDataFromFile(inputStream, text))
						{
							outputStream << compress(text);
							cout << "==> File has been Compressed" << endl;
						}
						else
						{
							cout << string(15, '*') << " Empty Input File " << string(14, '*') << endl;
							cout << "==> Empty file for Compression" << endl;
							cout << "==> Nothing written to the output file" << endl;
							cout << string(47, '*') << endl;
						}
					}
				}
				else if(numi == 2)
				{
					//decompression selected
					if(openOutputFile(outputStream, outputStreamName))
					{
						string text;
						//if input is not empty
						if(getDataFromFile(inputStream, text))
						{
							outputStream << decompress(text);
							cout << "==> File has been Decompressed" << endl;
						}
						else
						{
							cout << string(15, '*') << " Empty Input File " << string(14, '*') << endl;
							cout << "==> Empty file for Decompression" << endl;
							cout << "==> Nothing written to the output file" << endl;
							cout << string(47, '*') << endl;
						}
					}
				}
			}
		}
		else if(!isalpha(i))
		{
			cout << string(14, '*') << " Invalid Selection " << string(14, '*') << endl;
			cout << "==> Invalid integer value entered" << endl;
			cout << "==> Please enter 0, 1 or 2" << endl;
			cout << string(47, '*') << endl;
		}
		else
		{
			cout << string(14, '*') << " Invalid Selection " << string(14, '*') << endl;
			cout << "==> Invalid character entered!!" << endl;
			cout << "==> Please enter 0, 1 or 2" << endl;
			cout << string(47, '*') << endl;
		}
		cout << endl;
		printMenu();
		cout << endl << "Input your selection now: ";
		i = getInput();
		cout << (isalpha(i) ? i + '0' : i) << endl << endl;
		numi = i;
	}
	cout << "Quit selected.  Terminating program now..." << endl << endl;
	return 0;
}

void printMenu()
{
	cout << string(10, '*') << "  Compression Menu  " << string(10, '*') << endl;
	cout << "0. Exit Program" << endl;
	cout << "1. Compress File" << endl;
	cout << "2. Uncompress File" << endl;
	cout << string(40, '*') << endl;
}
int getInput()
{
	bool bWaiting = true;
	int temp;
	cin >> temp;
	while(islower(temp))
	{
		cin >> temp;
	}
	return temp;
}
bool openInputFile(ifstream &stream, const string &inputName)
{
	stream.open(inputName.c_str());
	if(stream.fail())
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inputName << endl;
		cout << "==> Selected operation has been canceled" << endl;
		cout << string(47, '*') << endl;
		return false;
	}
	return true;
}
bool openOutputFile(ofstream &stream, const string &inputName)
{
	stream.open(inputName.c_str());
	if(stream.fail())
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Output file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inputName << endl;
		cout << "==> Selected operation has been canceled" << endl;
		cout << string(47, '*') << endl;
		return false;
	}
	return true;
}
string compress(const string &text)
{

	char tempChar = 32;
	char activeChar;

	//string stream for outputting ints and characters to a string
	stringstream oss;
	//make a string stream for parsing
	stringstream ss(text);
	bool bWatch = false;
	int numTempChar = 1;
	ss.get(activeChar);
	ss.get(tempChar);
	while(ss.good())
	{
		if(activeChar == tempChar)
		{
			numTempChar++;
		}
		else
		{
			oss << numTempChar << activeChar;
			activeChar = tempChar;
			numTempChar = 1;
		}
		ss.get(tempChar);
		if(tempChar == ' ')
		{
			if(bWatch)
			{
				if(activeChar == ' ')
				{
					break;
				}
				else
				{
					bWatch = false;
				}

			}
			bWatch = true;
		}


	}
	oss << numTempChar - 1 << activeChar;
	string retString = oss.str();
	oss.clear();
	ss.clear();
	return retString;


}
string decompress(const string &text)
{
	stringstream ss(text);
	stringstream oss;
	char x;
	ss.get(x);
	while(ss.good())
	{
		int numCycles = (int(x) - 48);
		ss.get(x);
		for(int ctr = 0; ctr < numCycles; ctr++)
		{
			oss << x;
		}
		ss.get(x);
	}
	string ret = oss.str();
	oss.clear();
	ss.clear();
	return ret;
}
bool getDataFromFile(ifstream &stream, string &istring)
{
	if(stream.is_open())
	{
		char x;
		stream.get(x);
		if(stream.eof())
		{
			return false;
		}
		else
		{
			istring += x;
		}

		while(stream.good())
		{

			stream.get(x);
			istring += x;
		}
	}
	else
	{
		return false;
	}
	return true;
}
string getline__()
{
	string x;
	cin >> x;
	return x;
}
