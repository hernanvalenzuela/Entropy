// Entropy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <list>
#include "Block.h"
#include "BlockManager.h"

using namespace std;

bool ValidateInput(int argc, char* argv[], std::string* fileName, int* blocksize);

int main(int argc, char* argv[])
{
	int blocksize = 1024;
	std::string fileName;
	if (!ValidateInput(argc, argv, &fileName, &blocksize) )
	{
		return -1;
	}
	BlockManager* mb = new BlockManager(fileName, blocksize);
	mb->Process();
	mb->GenerateReport();
	delete mb;
	return 0;
}

bool ValidateInput(int argc, char* argv[], std::string* fileName, int* blocksize)
{
	string regex_filename = "[a-zA-Z_][a-zA-Z_0-9]*\\.[a-zA -Z0-9]+";
	string regex_number = "[0-9]+";
	regex regNumber(regex_number, regex_constants::icase);
	regex regFileName(regex_filename, regex_constants::icase);
	bool b = std::regex_match(std::string(argv[2]), regNumber);
	if (argc == 1)
	{
		std::cout << "Invalid parameter's numbers, entropy [ -b <blocksize> ] <filename> ";
		return false;
	}
	//check if its file name
	if (std::regex_match(std::string(argv[1]), regFileName))
	{
		*fileName =  std::string(argv[1]);
		return true;
	}
	//check pattern  [ -b <blocksize> ] <filename> 
	else if ((argc == 4)
		&& (std::string(argv[1]) == "-b")
		&& (std::regex_match(std::string(argv[2]), regNumber))
		//&& (std::regex_match(std::string(argv[3]), regFileName))
		)
	{
		*blocksize = atoi(argv[2]);
		*fileName = std::string(argv[3]);
		return true;
	}
	else
	{
		std::cout << "Invalid parameter's numbers, entropy [ -b <blocksize> ] <filename> ";
		return false;
	}
}


