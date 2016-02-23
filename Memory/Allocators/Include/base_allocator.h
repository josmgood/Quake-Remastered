#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\..\..\Core\common.h"

struct Block
{
	Block				(void* mem, size_t len);
	Block				(void);
	void free			(void);

	operator bool(void) const;

	void*	memory;
	size_t	length;
};

/*
==================================

BASE ALLOCATOR

==================================
*/

class BaseAllocator
{
public:
	virtual Block allocate				(size_t size) = 0;
	virtual void deallocate				(Block& block) = 0;
	virtual void deallocateAll			(void) = 0;
	virtual bool owns					(Block block) = 0;
};