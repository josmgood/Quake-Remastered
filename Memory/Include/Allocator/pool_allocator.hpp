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
	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY, QBool expandStatus = false);
	inline ~PoolAllocator();

	inline Block allocate();
	inline void deallocate(Block& block);
	inline QBool owns(Block block) const;
	inline void expand(size_t amount);
	inline void destroy();

	inline void setExpandProtocol(QBool protocol);

	inline size_t getCapacity() const;
	inline size_t getMemoryUsed() const;
	inline size_t getBlockSize() const;
	inline size_t getPadding() const;
	inline size_t getTrueSize() const;
private:
	QBool _isFree(size_t index) const;
	QBool _isAllocated(size_t index) const;

	Block _findBlock();

	size_t _capacity;
	size_t _memoryUsed;
	size_t _numBlocks;
	internal::Byte* _memory;
	Block* _blocks;
	size_t _trueSize;
	size_t _padding;
	size_t _blockSize;
	internal::BoolSet _flags;
	QBool _canExpand;

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