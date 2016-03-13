#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\Internal\boolset.h"

#include "..\..\..\Core\Include\common.h"
#include "..\..\..\Container\Include\qbool.h"

#define DEFAULT_ALLOCATOR_CAPACITY	512

#define ALLOCATED	1
#define FREE		0
#define UNALLOCATED	0

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

struct Block
{
	Block(void* mem, size_t len)
		: memory(mem), length(len) {}
	Block()
		: memory(nullptr), length() {}

	void free()
	{
		memory = nullptr;
		length = 0;
	}

	operator bool() const
	{
		return(memory && length);
	}

	void*		memory;
	size_t		length;
};

#define UNALLOCATED_BLOCK		Block()

//template<size_t maxSize>
//struct AddressVolume
//{
//	AddressVolume()
//		: flags(), current(), size(maxSize) {}
//	void add(Address address)
//	{
//		if (!addresses[current])
//		{
//			for (size_t i = 0; i < size; i++)
//			{
//
//			}
//		}
//		else
//		{
//			addresses[current] = address;
//			current++;
//		}
//	}
//	void remove(Address address);
//	QBool owns(Address address);
//
//	Address addresses[maxSize];
//	internal::QBoolSet flags;
//	size_t current;
//	size_t size;
//};