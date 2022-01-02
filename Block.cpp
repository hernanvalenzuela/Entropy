#include "Block.h"


void Block::CollectData()
{
	for (int i = 0; i < mSize; i++)
	{
		it = characters.find(mBuffer[i]);
		if (it != characters.end())
		{
			(*it).second++;
		}
		else
		{
			characters.insert(std::pair<char, unsigned int>(mBuffer[i], 1));
		}
	}
}

void Block::Process()
{
	try {
		CollectData();
		for (it = characters.begin(); it != characters.end(); it++)
		{
			double pb = ((double) (*it).second / (double) mSize);
			entropyblockvalue += - pb * log2(pb);
		}
		CouldBeProcess = true;
	}
	catch (...){
		CouldBeProcess = false;
	}
}

std::string Block::GenerateReport()
{
	std::string s("");
	return s;
}

double Block::GetEntropy()
{
	return  this->entropyblockvalue;
}

unsigned int Block::GetBlockNumber()
{
	return this->mBlockNumber;
}

