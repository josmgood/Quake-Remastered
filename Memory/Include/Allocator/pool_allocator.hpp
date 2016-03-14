#pragma once
#include <iostream>

#include "base_allocator.h"
#include "freelist.hpp"

#include "..\Internal\auxiliary.h"
#include "..\Internal\boolset.h"

#include "..\..\..\Math\Include\math.h"

template<typename TBlock>
class PoolAllocator
{
public:
	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY);
	inline ~PoolAllocator();

	inline Block* allocate(size_t size);
	inline void deallocate(Block* blocks, size_t count);
	inline QBool owns(Block block) const;
	inline void destroy();

	inline size_t getCapacity() const;
	inline size_t getMemoryUsed() const;
	inline size_t getBlockSize() const;
	inline size_t getPadding() const;
	inline size_t getTrueSize() const;
private:
	size_t _capacity;
	size_t _trueSize;
	size_t _padding;
	size_t _blockSize;
	size_t _memoryUsed;
	size_t _numBlocks;
	internal::Byte* _memory;
	FreeList _freeList;

	PoolAllocator(PoolAllocator&) = delete;
	PoolAllocator(const PoolAllocator&) = delete;
	PoolAllocator(PoolAllocator&&) = delete;
	PoolAllocator operator=(PoolAllocator&) = delete;
	PoolAllocator& operator=(const PoolAllocator&) = delete;
	PoolAllocator* operator&() = delete;

	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
};

#include "..\..\Source\Allocator\pool_allocator.inl"