#pragma once

#include "Heap.h"

#define USE_CUSTOM_ALLOC

#ifdef USE_CUSTOM_ALLOC
#define cnew Crude::new
#else
#define cnew new
#endif

namespace Crude {

	struct AllocBlock {
		int BlockHeader;
		int BlockNumber;
		int BlockSize;
		Heap* BlockHeap;
	};

	void * operator new (size_t size);
	void * operator new (size_t size, Heap * pHeap);
	void operator delete (void * pMem, size_t size); 

}