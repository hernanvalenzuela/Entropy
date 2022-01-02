#pragma once
#include <string>
#include <map>
#include <vector>
class Block
{
private:
	std::vector<char> mBuffer;
	int mSize;
	unsigned int mBlockNumber = 0;
	std::map<char, unsigned int> characters;
	std::map<char, unsigned int>::iterator it;
	bool CouldBeProcess = false;
	double entropyblockvalue;
	void CollectData();

public:
	Block(std::vector<char> buffer, int size,unsigned int blockNum)
	{
		mBuffer = buffer;
		mSize = size;
		mBlockNumber = blockNum;
	}
	void Process();
	std::string GenerateReport();
	double GetEntropy();
	unsigned int GetBlockNumber();
	~Block()
	{

	}
};