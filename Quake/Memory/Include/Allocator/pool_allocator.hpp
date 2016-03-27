#pragma once

#pragma warning(disable : 4522)
#pragma warning(disable : 4521)

#include <iostream>
#include <limits>

#include "base_allocator.h"
#include "freelist.hpp"

#include "..\Internal\auxiliary.h"
#include "..\Internal\boolset.h"

#include "..\..\..\Math\Include\math.h"

/*Allocate gives same memory every time*/
/*Batching gives access errors*/

template<typename TBlock>
class PoolAllocator
{
public:
	inline PoolAllocator(size_t capacity = DO_NOT_INIT_SIZE);
	inline ~PoolAllocator();

	inline Block allocate();
	inline void deallocate(Block& block);
	inline Batch batchAllocate(size_t size);
	inline void batchDeallocate(Batch& batch);
	inline QBool owns(Block block) const;
	inline ALLOCATOR_INIT_STATUS init(size_t capacity);
	inline void destroy();

	inline size_t getCapacity() const;
	inline size_t getMemoryUsed() const;
	inline size_t getBlockSize() const;
	inline size_t getPadding() const;
	inline size_t getTrueSize() const;
	inline size_t getNumBlocks() const;
	inline size_t getNumAllocated() const;
	inline QBool isInitialized() const;
	inline QBool isFull() const;
	inline QBool hasFreeMemory() const;
private:
	inline void _addMemoryUsed(size_t amount);
	inline void _subtractMemoryUsed(size_t amount);
	
	inline void _incrementNumAllocated();
	inline void _decrementNumAllocated();
	inline void _addNumAllocated(size_t amount);
	inline void _subtractNumAllocated(size_t amount);

	inline QBool _hasSpace(size_t addedSize);

	size_t _capacity;
	size_t _trueSize;
	size_t _padding;
	size_t _blockSize;
	size_t _memoryUsed;
	size_t _numAllocated;
	size_t _numBlocks;
	internal::Byte* _memory;
	FreeList _freeList;
	QBool _isInitialized;

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