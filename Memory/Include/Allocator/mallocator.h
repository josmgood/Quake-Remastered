#pragma once

#include "base_allocator.h"

#include "..\..\..\Container\Include\qbool.h"

class MAllocator
{
public:
	MAllocator();

	Block allocate(size_t size);
	void deallocate(Block& block);
private:
	size_t _numAllocations;
};