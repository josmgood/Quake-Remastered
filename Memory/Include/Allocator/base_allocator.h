#pragma once

/*Standard Library*/
#include <type_traits>

/*Custom Libraries*/
#include "..\Internal\boolset.h"

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

typedef void* Address;

struct Block
{
	Block(Address base, size_t len)
		: address(base), length(len) {}
	Block()
		: address(nullptr), length() {}
	void free()
	{

		address = nullptr;
		length = 0;
	}

	operator bool() const
	{
		return(address && length);
	}

	Address		address;
	size_t		length;
};

#define DEAD_BLOCK		Block()
#define DEAD_BLOCKS		nullptr

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
//	bool owns(Address address);
//
//	Address addresses[maxSize];
//	internal::BoolSet flags;
//	size_t current;
//	size_t size;
//};