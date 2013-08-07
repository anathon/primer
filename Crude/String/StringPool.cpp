#include "StringPool.h"

namespace Crude {

	StringPool::StringPool() {

		CreateMemoryBlock();

		MemoryBlocks.SlideFront();

	}

	StringPool::~StringPool() {

		MemoryBlocks.SlideFront();

		while (!MemoryBlocks.Finished()) {
		
			delete MemoryBlocks.Get();

		}

	}

	void StringPool::InsertString(Crude::String TargetString) {

		unsigned int MemoryUsed = MemoryBlocks.Get()->MemoryUsed;

		if ((MemoryUsed + TargetString.Length()) >= MEMORYBLOCK_SIZE) {

			CreateMemoryBlock();

			MemoryBlocks.Slide();

		}

		cstrncpy(TargetString.Data(), MemoryBlocks.Get()->Memory + (MemoryUsed), TargetString.Length() + 1);

		MemoryBlocks.Get()->MemoryUsed += TargetString.Length() + 1;
	}

	void StringPool::CreateMemoryBlock() {

		char* InitalMemory = new char[2048];

		StringPoolMemoryBlock* InitalBlock = new StringPoolMemoryBlock();
		InitalBlock->Memory = InitalMemory;
		InitalBlock->MemoryUsed = 0;

		MemoryBlocks.Insert(InitalBlock);
	}

};