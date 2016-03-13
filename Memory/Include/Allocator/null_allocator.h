#pragma once

#include "base_allocator.h"

#include "..\..\..\Container\Include\qbool.h"

class NullAllocator
{
public:
	Block allocate(size_t size);
	void deallocate(Block& block);
	QBool owns(Block block);
};