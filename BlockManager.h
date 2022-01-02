#pragma once
#include <string>
#include "Block.h"
#include <list>
#include <ppl.h>
#include <concurrent_vector.h>

using namespace Concurrency;
class BlockManager
{
private:
	int mblocksize = 1024;
	std::string mfileName;
	Concurrency::concurrent_vector <Block> blocks;
	Concurrency::concurrent_vector <Block>::iterator itBlock;
	const int LoWEntropyValue = 2;
	const int HihgEntropyValue = 7;
public:
	BlockManager(std::string fileName, int blocksize)
	{
		mblocksize = blocksize;
		mfileName = fileName;
	}

	~BlockManager()
	{
		blocks.clear();
	}
	void Process();
	void GenerateReport();
};