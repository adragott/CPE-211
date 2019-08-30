// ****************************************
// Program Title: Project 9
// Project File: Project_09.cpp
// Name: Anthony Dragotta
// Course Section: CPE-211-01
// Lab Section: 1
// Due Date: 7/18/18
// program description: sample
// What program does.
// ****************************************
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <climits>

using namespace std;

enum FILE_ERR
{
	FILE_INPUT = 0,
	FILE_OUTPUT = 1,
	FILE_EMPTY = 2
};

struct SubName
{
	string firstName;
	string lastName;
	int customerId;
};

struct SubAddr
{
	string addr;	//street number and name
	string city;
	string state;
	int zipCode;
};

struct Date
{
	string month;
	int day;
	int year;
};

struct RenewalInfo
{
	int monthsRemaining;
	Date lastNoticeSent;
};

struct Subscriber
{
	SubName subName;
	SubAddr subAddress;
	Date 	subDate;
	RenewalInfo renewalInfo;
};

bool OpenInputFile(ifstream &inputFile, const string &inputName);
bool OpenOutputFile(ofstream &outputFile, const string &outputName);
void HandleError(FILE_ERR err, const string &fileName);
bool DispatchInformation(const Subscriber &sub);
bool GetRecord(ifstream &inputFile, Subscriber &sub);
void HandleExpiredCustomer(ofstream &outputStream, Subscriber &sub, bool bFirstExpired);

int main()
{
	int numSubs = 0;
	int numExpiredSubs = 0;
	ifstream inputStream;
	ofstream outputStream;
	string inputName;
	string outputName;
	bool bInputStreamGood = true;
	cout << endl;
	do {
		bInputStreamGood = true;
		cout << "Enter name of input file or Control-C to quit program: ";
		cin >> inputName;
		cout << inputName << endl << endl;
		if(!OpenInputFile(inputStream, inputName))
		{
			HandleError(FILE_INPUT, inputName);
			bInputStreamGood = false;
			inputStream.clear();
			inputStream.close();
		}
	} while(!bInputStreamGood);

	bool bOutputStreamGood = true;
	do {
		bOutputStreamGood = true;
		cout << "Enter name of output file or Control-C to quit program: ";
		cin >> outputName;
		cout << outputName << endl << endl;
		if(!OpenOutputFile(outputStream, outputName))
		{
			HandleError(FILE_OUTPUT, outputName);
			bOutputStreamGood = false;
			outputStream.clear();
			outputStream.close();
		}
	} while(!bOutputStreamGood);
	bool ret = true;
	bool bFirstRead = true;
	bool bFirstReadExpired = true;
	do {
		Subscriber newSub;
		ret = GetRecord(inputStream, newSub);
		if(bFirstRead)
		{
			bFirstRead = false;
			if(!ret)
			{
				//must be empty!
				HandleError(FILE_EMPTY, inputName);
				outputStream << string(52, '-') << endl;
				outputStream << "==> The input file does not contain any information." << endl;
				outputStream << string(52, '-') << endl;
				return -1;
			}
		}
		if(ret)
		{
			//DispatchInformation returning true here means an expired sub
			if(DispatchInformation(newSub))
			{
				numExpiredSubs++;

				HandleExpiredCustomer(outputStream, newSub, bFirstReadExpired);
				if(bFirstReadExpired)
				{
					bFirstReadExpired = false;
				}
			}
			numSubs++;
		}
	} while(ret);
	cout << endl << string(47, '-') << endl;
	cout << "Number of subscribers processed: " << numSubs << endl;
	cout << "The number of expired subscriptions is: " << numExpiredSubs << endl;
	cout << string(47, '-') << endl << endl;
	if(numExpiredSubs > 0)
	{
		outputStream << endl;
	}

	return 0;
}

//true means success!
bool OpenInputFile(ifstream &inputFile, const string &inputName)
{
	inputFile.open(inputName.c_str());
	if(inputFile.fail())
	{
		return false;
	}
	return true;
}

//true means success!
bool OpenOutputFile(ofstream &outputFile, const string &outputName)
{
	outputFile.open(outputName.c_str());
	if(outputFile.fail())
	{
		return false;
	}
	return true;
}

void HandleError(FILE_ERR err, const string &fileName)
{
	if(err == FILE_INPUT || err == FILE_OUTPUT)
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> " << (err == FILE_INPUT ? "Input" : "Output") << " file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << fileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
	}
	else
	{
		cout << "===> Input file is empty.  Program terminated" << endl << endl;
	}

}

//true means there was a record to obtain
bool GetRecord(ifstream &inputFile, Subscriber &sub)
{
	getline(inputFile, sub.subName.firstName, '\n');
	if(inputFile.fail())
	{
		return false;
	}
	getline(inputFile, sub.subName.lastName, '\n');
	inputFile >> sub.subName.customerId;
	inputFile.ignore(INT_MAX, '\n');
	getline(inputFile, sub.subAddress.addr, '\n');
	getline(inputFile, sub.subAddress.city, '\n');
	getline(inputFile, sub.subAddress.state, '\n');
	inputFile >> sub.subAddress.zipCode;
	inputFile >> sub.renewalInfo.monthsRemaining;
	inputFile.ignore(INT_MAX, '\n');
	getline(inputFile, sub.renewalInfo.lastNoticeSent.month);
	inputFile >> sub.renewalInfo.lastNoticeSent.day;
	inputFile >> sub.renewalInfo.lastNoticeSent.year;
	inputFile.ignore(INT_MAX, '\n');
	return true;
}

//DispatchInformation returning true here means an expired sub
bool DispatchInformation(const Subscriber &sub)
{
	cout << "====> Processing Customer ID: " << sub.subName.customerId << endl;
	if(sub.renewalInfo.monthsRemaining == 0)
	{
		return true;
	}
	return false;
}

void HandleExpiredCustomer(ofstream &outputStream, Subscriber &sub, bool bFirstExpired)
{
	if(!bFirstExpired)
	{
		outputStream << endl;
	}
	outputStream << string(55, '*') << endl;
	outputStream << sub.subName.firstName << " " << sub.subName.lastName << "(" <<
		sub.subName.customerId << ")" << endl;
	outputStream << sub.subAddress.addr << endl;
	outputStream << sub.subAddress.city << ", " << sub.subAddress.state << " " << sub.subAddress.zipCode << endl;
	outputStream << "The last renewal notice was sent on " << sub.renewalInfo.lastNoticeSent.month <<
		" " << sub.renewalInfo.lastNoticeSent.day << ", " << sub.renewalInfo.lastNoticeSent.year << endl;
	outputStream << string(55, '*') << endl;
}
