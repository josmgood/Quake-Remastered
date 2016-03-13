#include "..\..\Include\Allocator\mallocator.h"

MAllocator::MAllocator()
	: _numAllocations()
{
}

Block MAllocator::allocate(size_t size)
{
	void* mem = malloc(size);
	if (mem)
	{
		Block block(mem, size);
		_numAllocations++;
		return(block);
	}
	return(UNALLOCATED_BLOCK);
}

void MAllocator::deallocate(Block& block)
{
	if (_numAllocations && block)
	{
		free(block.memory);
		block.length = 0;
		_numAllocations--;
	}
}