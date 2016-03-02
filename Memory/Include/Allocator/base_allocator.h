#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\..\..\Core\Include\common.h"

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
*
*======================================================================
*/

namespace mem
{
	typedef void* Address;

	struct Block
	{
		Block(Address base, size_t len)
			: baseAddr(base), freeAddr(nullptr), length(len) {}
		Block()
			: baseAddr(nullptr), freeAddr(nullptr), length() {}
		void free()
		{
			freeAddr = nullptr;
			baseAddr = nullptr;
			length = 0;
		}

		operator bool() const
		{
			return(baseAddr && length);
		}

		Address		freeAddr;
		Address		baseAddr;
		size_t		length;
	};
}

#define DEAD_BLOCK		Block()
#define DEAD_BLOCKS		nullptr