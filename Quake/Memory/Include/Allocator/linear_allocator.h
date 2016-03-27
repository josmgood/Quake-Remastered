#pragma once

/*Custom Library*/
#include "..\Internal\auxiliary.h"

#include "base_allocator.h"

#define MIN_FRAG = 64

template<size_t minBlockSize, size_t maxBlockSize, size_t minFrag = MIN_FRAG>
class LinearAllocator
{
public:
	inline LinearAllocator(size_t capacity, QBool expandStatus = false);
private:
	internal::Byte* _memory;
	Block* _blocks;
	size_t _numBlocks;

	LinearAllocator(LinearAllocator&) = delete;
	LinearAllocator(const LinearAllocator&) = delete;
	LinearAllocator(LinearAllocator&&) = delete;
	LinearAllocator operator=(LinearAllocator&) = delete;
	LinearAllocator& operator=(const LinearAllocator&) = delete;
	LinearAllocator* operator&() = delete;

	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
};