//#pragma once
//
///*Standard Library*/
//#include <iostream>
//#include <memory>
//#include <bitset>
//
///*Custom Library*/
//#include "base_allocator.h"
//
//#include "..\Internal\auxiliary.h"
//#include "..\Internal\boolset.h"
//
////template<typename Type>
////class PoolAllocator
////	:	public BaseAllocator,
////		public alloc::GetAllocate,
////		public alloc::GetDeallocate,
////		public alloc::GetExpand
////{
////public:
////	inline PoolAllocator(size_t capacity = 16, bool allowExpansion = true);
////	virtual inline ~PoolAllocator() override;
////
////	virtual inline Block* allocate(size_t amount = 1) override;
////	virtual inline void deallocate(Block* blocks, size_t amount = 1) override;
////	virtual inline void expand(size_t amount);
////	virtual inline bool owns(Block block) override;
////	virtual inline void reset() override;
////	virtual inline void destroy() override;
////
////	inline size_t getBlockSize() const;
////	inline size_t getNumBlocks() const;
////private:
////	inline bool _isFree(bool flag);
////	inline bool _isAllocated(bool flag);
////	inline void* _addressAt(size_t index);
////
////	inline void _setNumBlocks(size_t num);
////	inline void _setBlocks(Block* blocks);
////	inline void _setFlags(const internal::BoolSet& flgs);
////
////	size_t _blockSize;
////	size_t _numBlocks;
////	Block* _blocks;
////	internal::BoolSet _flags;
////};
//
//template<typename Type>
//class PoolAllocator
//{
//public:
//	inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY, bool canExpand = true);
//	inline ~PoolAllocator();
//
//	inline Block* allocate(size_t amount);
//	inline void deallocate(Block* block, size_t size);
//	inline void expand(size_t amount);
//	inline bool owns(Block block) const;
//	inline void destroy();
//	
//	inline bool canExpand() const;
//	inline size_t getCapacity() const;
//	inline size_t getNumAllocations() const;
//	inline size_t getBlockSize() const;
//private:
//	inline bool _isFree(bool flag) const;
//	inline bool _isAllocated(bool flag) const;
//
//	inline Address _getAddressAt(size_t index) const;
//
//	inline void _addCapacity(size_t amount);
//	inline void _setCapacity(size_t capacity);
//
//	inline void _incrementNumAllocations();
//	inline void _decrementNumAllocations();
//	inline void _setNumAllocations(size_t num);
//
//	inline void _setBlocks(Block* blocks);
//	inline void _setFlags(const internal::BoolSet& flags);
//
//	bool _canExpand;
//	size_t _blockSize;
//	size_t _capacity;
//	size_t _numAllocations;
//	Block* _blocks;
//	internal::BoolSet _flags;
//};
//
//#include "..\..\Source\Allocator\pool_allocator.inl"

#include "..\Internal\auxiliary.h"
#include "base_allocator.h"

#include "..\..\..\Math\Include\math.h"

namespace mem
{
	template<typename TBlock>
	class PoolAllocator
	{
	public:
		inline PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY);
		~PoolAllocator();

		inline Block allocate(size_t size);
		inline void deallocate(Block block);
		inline void destroy();
	private:

		internal::Byte* _memory;
		size_t _capacity;
		size_t _memoryUsed;
		size_t _blockSize;
		size_t _padding;
		size_t _trueSize;
	};
}

#include "..\..\Source\Allocator\pool_allocator.inl"