#pragma once
#include <iostream>

#include "base_allocator.h"
#include "freelist.hpp"

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
//	//	operator QBool() const;
//	//};
//
//	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY);
//	inline ~PoolAllocator();
//
//	inline Block allocate(size_t size);
//	inline void deallocate(Block& block);
//	inline QBool owns(Block block) const;
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
//	/*QBool _isFree(size_t index) const;
//	QBool _isAllocated(size_t index) const;
//
//	BlockInfo _findFree() const;*/
//
//	//internal::Byte* _memory;
//	//Block* _blocks;
//	//internal::QBoolSet _flags;
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

	Block& _findBlock(QBool flag = false);

	size_t _capacity;
	size_t _memoryUsed;
	size_t _numBlocks;
	internal::Byte* _memory;
	Block* _blocks;
	size_t _trueSize;
	size_t _padding;
	size_t _blockSize;
	FreeList _freeList;
	internal::BoolSet _flags;
	QBool _canExpand;
};

#include "..\..\Source\Allocator\pool_allocator.inl"