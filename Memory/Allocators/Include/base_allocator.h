#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\..\..\Core\common.h"

#define DEFAULT_ALLOCATOR_CAPACITY	512

#define ALLOCATED	1
#define FREE		0

/*
*======================================================================
* 
* MEMORY BLOCK
*
* Fundamental data structure in an allocator.
*
* void* memory -		memory held within the block
* size_t size -			size of the block
* size_t alignment -	alignment to fit perfectly in an allocator
*
*======================================================================
*/

typedef void* Address;

struct Block
{
	Block(Address addr, size_t size)
		: address(addr), size(size) {}
	Block()
		: address(nullptr), size() {}
	void free()
	{
		address = nullptr;
		size = 0;
	}

	operator bool() const
	{
		return(address && size);
	}

	Address		address;
	size_t		size;
};

#define DEAD_BLOCK		Block()
#define DEAD_BLOCKS		nullptr