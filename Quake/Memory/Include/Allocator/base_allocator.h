#pragma once

#include <string>
#include <type_traits>

#include "..\Internal\boolset.h"

#include "..\..\..\common.h"
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
#define UNALLOCATED_BLOCKS		nullptr

struct Batch
{
	Batch(Block* blks, size_t sz)
		: blocks(blks), size(sz) {}
	Batch(size_t sz)
		: blocks(new Block[sz]), size(sz) {}
	Batch()
		: blocks(nullptr), size() {}

	Block& operator[](size_t index)
	{
		return index >= 0 && index <= size ?
			blocks[index] : UNALLOCATED_BLOCK;
	}

	operator bool()
	{
		return blocks && size;
	}

	Block* blocks;
	size_t size;
};

#define UNALLOCATED_BATCH Batch()

enum ALLOCATION_SIZES
	: size_t
{
	DO_NOT_INIT_SIZE = 0,
	SMALL_SIZE = 128,
	MEDIUM_SIZE = 256,
	DEFAULT_SIZE = 512,
	LARGE_SIZE = 1024,
	MAX_SIZE = 4294967295
};

enum ALLOCATOR_INIT_STATUS
	: int8
{
	NONE = -1,
	SUCCESS = 0,
	ALREADY_INITIALIZED = 1,
	BAD_CAPACITY = 2,
	BAD_MEMORY = 3,
	INTERNAL_ERROR = 4
};

//std::string aisToString(ALLOCATOR_INIT_STATUS status)
//{
//	switch (status)
//	{
//	case ALLOCATOR_INIT_STATUS::NONE:
//		return "NONE";
//	case ALLOCATOR_INIT_STATUS::SUCCESS:
//		return "SUCCESS";
//	case ALLOCATOR_INIT_STATUS::ALREADY_INITIALIZED:
//		return "ALREADY INITIALIZED";
//	case ALLOCATOR_INIT_STATUS::BAD_CAPACITY:
//		return "BAD CAPACITY";
//	case ALLOCATOR_INIT_STATUS::BAD_MEMORY:
//		return "BAD MEMORY";
//	case ALLOCATOR_INIT_STATUS::INTERNAL_ERROR:
//		return "INTERNAL ERROR";
//	default:
//		return "NULL STATUS";
//	}
//}