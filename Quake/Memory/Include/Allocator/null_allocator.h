#pragma once

#include "base_allocator.h"

#include "..\..\..\Container\Include\qbool.h"

class NullAllocator
{
public:
	inline Block allocate(size_t size);
	inline void deallocate(Block& block);
	inline QBool owns(Block block);
	inline ALLOCATOR_ID getID() const;
};