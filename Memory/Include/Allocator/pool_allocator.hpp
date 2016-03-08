#pragma once
#include <iostream>

#include "base_allocator.h"
#include "freelist_allocator.hpp"

#include "..\Internal\auxiliary.h"
#include "..\Internal\boolset.h"

#include "..\..\..\Math\Include\math.h"

//template<typename TBlock>
//class PoolAllocator
//{
//public:
//	//struct BlockInfo
//	//{
//	//	BlockInfo(Address addr = nullptr, size_t i = 0);
//	//	Address address;
//	//	size_t index;
//
//	//	operator bool() const;
//	//};
//
//	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY);
//	inline ~PoolAllocator();
//
//	inline Block allocate(size_t size);
//	inline void deallocate(Block& block);
//	inline bool owns(Block block) const;
//	inline void expand(size_t size);
//	inline void destroy();
//
//	inline size_t getCapacity() const;
//	inline size_t getMemoryUsed() const;
//	inline size_t getBlockSize() const;
//	inline size_t getNumBlocks() const;
//	inline size_t getPadding() const;
//	inline size_t getTrueSize() const;
//private:
//	/*bool _isFree(size_t index) const;
//	bool _isAllocated(size_t index) const;
//
//	BlockInfo _findFree() const;*/
//
//	//internal::Byte* _memory;
//	//Block* _blocks;
//	//internal::BoolSet _flags;
//	FreeList _freeList;
//
//	size_t _capacity;
//	size_t _memoryUsed;
//	size_t _blockSize;
//	size_t _numBlocks;
//	size_t _padding;
//	size_t _trueSize;
//};

template<typename TBlock>
class PoolAllocator
{
public:
	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY);
	inline ~PoolAllocator();

	inline Block& allocate();
	inline void deallocate(Block& block);
	inline bool owns(Block block) const;
	inline void expand(size_t amount);
	inline void destroy();

	inline size_t getCapacity() const;
	inline size_t getMemoryUsed() const;
	inline size_t getBlockSize() const;
	inline size_t getPadding() const;
	inline size_t getTrueSize() const;
private:
	FreeList _freeList;
	size_t _memoryUsed;
	size_t _blockSize;
	size_t _padding;
	size_t _trueSize;
};

#include "..\..\Source\Allocator\pool_allocator.inl"