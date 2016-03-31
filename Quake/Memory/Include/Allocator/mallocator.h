#pragma once

#include "base_allocator.h"

//#include "..\..\..\Container\Include\qbool.h"

#define MALLOCATOR_MAX UINT_MAX

class MAllocator
{
public:
	inline MAllocator();
	inline Block allocate(size_t size);
	inline void deallocate(Block& block);
	inline ALLOCATOR_ID getID() const;
private:
	size_t _numAllocations;
};