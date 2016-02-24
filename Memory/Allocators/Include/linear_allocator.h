#pragma once

/*Custom Library*/
#include "..\..\Internal\Include\auxiliary.h"

#include "base_allocator.h"

/*
*======================================================================
*
* LINEAR ALLOCATOR
*
* A linear line of memory to be allocated when needed.
* Once initialised, the buffer cannot be resized.
* Capable of holding different forms of memory(NOT a memory pool)
*
*
* /tparam - minimum size a block can be
* /tparam - maximum size a block can be
* /tparam - maximum size of the memory buffer
*
* /inh - BaseAllocator
* /inh - alloc::GetOwns
* /inh - alloc::GetReallocate
* /inh - alloc::GetDeallocateAll
*
*======================================================================
*/
template<size_t minBlockSize, 
	size_t maxBlockSize, 
	size_t heapCapacity>
class LinearAllocator
	:	public BaseAllocator,
		public alloc::GetOwns,
		public alloc::GetReallocate,
		public alloc::GetDeallocateAll
{
public:
	LinearAllocator					(void);
	virtual ~LinearAllocator		(void) override;

	virtual Block allocate			(size_t size) override;
	virtual bool owns				(Block block) override;
	virtual bool reallocate			(Block& block, size_t newSize);
	virtual bool deallocateAll		(void);
private:
	internal::Byte		_heap[heapCapacity];
	size_t				_filledSize;
	size_t				_blocksAllocated;
};