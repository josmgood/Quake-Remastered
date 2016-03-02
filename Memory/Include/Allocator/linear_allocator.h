#pragma once

/*Custom Library*/
#include "..\Internal\auxiliary.h"

#include "base_allocator.h"



template<size_t minBlockSize, size_t maxBlockSize, size_t minFrag>
class LinearAllocator
{
public:
	LinearAllocator(size_t size);
	LinearAllocator();
	~LinearAllocator();

	Block allocate(size_t size);
	void deallocate(Block& block);
private:
	Block _memory;
};