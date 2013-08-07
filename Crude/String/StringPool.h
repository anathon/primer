#pragma once

#include "../Containers/LinkedList.h"

#define MEMORYBLOCK_SIZE 2048

struct StringPoolMemoryBlock {

	char* Memory;
	unsigned int MemoryUsed;

};

namespace Crude {

	class StringPool {

	public:
		StringPool();
		~StringPool();

	private:
		Crude::LinkedList<StringPoolMemoryBlock> MemoryBlocks;

	public:
		void InsertString(Crude::String TargetString);

	private:
		void CreateMemoryBlock();

	};

}