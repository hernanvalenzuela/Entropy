#include "BlockManager.h"
#include <vector>
#include <ppl.h>
#include <fstream>
#include <iostream>
using namespace concurrency;
using namespace std;

void BlockManager::Process()
{
	std::ifstream file(mfileName, std::ifstream::in);
	/*file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);*/
	try {

		if (file.good() || !file.bad() || file.is_open())
		{
			int blockNumber = 0;
			while (!file.eof())
			{
				std::vector<char> buffer(mblocksize, 0);
				file.read(&buffer[0], mblocksize);
				Block block (buffer, file.gcount(),blockNumber++);
				blocks.push_back(block);
			}
		}
		if (file)
			file.close();
	}
	catch (...)
	{
		if (file)
			file.close();
	}

	int size = blocks.size();
	Concurrency::parallel_for(0, size, 1, [&](int item) {
		cout << "Procesing Block " << blocks[item].GetBlockNumber() << endl;
		blocks[item].Process();
		});
	
}

void BlockManager::GenerateReport()
{//generate Reports
	std::cout << "entropy for file " + mfileName << std::endl;
	int lowEntropy = 0;
	int highEntropy = 0;
	std::cout << "block \t \t entropy " << std::endl;

	for (itBlock = blocks.begin(); itBlock != blocks.end(); itBlock++)
	{
		std::cout << (*itBlock).GetBlockNumber() << " \t \t  " << (*itBlock).GetEntropy()  << std::endl;
		if ((*itBlock).GetEntropy() < this->LoWEntropyValue)
		{
			lowEntropy++;
		}
		else if ((*itBlock).GetEntropy() > this->HihgEntropyValue)
		{
			highEntropy++;
		}
	}
	std::cout << "Low entropy blocks : " << lowEntropy << std::endl;
	std::cout << "High entropy blocks : " << highEntropy << std::endl;	
}
