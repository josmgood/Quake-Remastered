#pragma once

#include "base_allocator.h"

class MAllocator
{
public:
	MAllocator();

	Block allocate(size_t size);
	void deallocate(Block& block);
private:
	size_t _numAllocations;
};