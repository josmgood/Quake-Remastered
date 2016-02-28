#pragma once

/*Standard Library*/
#include <iostream>
#include <memory>
#include <bitset>

/*Custom Library*/
#include "base_allocator.h"

#include "..\..\Internal\Include\auxiliary.h"
#include "..\..\Internal\Include\boolset.h"

template<typename Type>
class PoolAllocator
	:	public BaseAllocator,
		public alloc::GetAllocate,
		public alloc::GetDeallocate,
		public alloc::GetExpand
{
public:
	inline PoolAllocator(size_t capacity = 16, bool allowExpansion = true);
	virtual inline ~PoolAllocator() override;

	virtual inline Block* allocate(size_t amount = 1) override;
	virtual inline void deallocate(Block* blocks, size_t amount = 1) override;
	virtual inline void expand(size_t amount);
	virtual inline bool owns(Block block) override;
	virtual inline void reset() override;
	virtual inline void destroy() override;

	inline size_t getBlockSize() const;
	inline size_t getNumBlocks() const;
private:
	inline bool _isFree(bool flag);
	inline bool _isAllocated(bool flag);
	inline void* _addressAt(size_t index);

	inline void _setNumBlocks(size_t num);
	inline void _setBlocks(Block* blocks);
	inline void _setFlags(const internal::BoolSet& flgs);

	size_t _blockSize;
	size_t _numBlocks;
	Block* _blocks;
	internal::BoolSet _flags;
};

#include "..\Source\pool_allocator.inl"