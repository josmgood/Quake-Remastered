#pragma once

#include "freelist.hpp"

template<size_t min,
	size_t max,
	size_t capacity = DEFAULT_ALLOCATOR_CAPACITY>
class LaxFreeList
	: public FreeList<capacity>
{
public:
	LaxFreeList();
};