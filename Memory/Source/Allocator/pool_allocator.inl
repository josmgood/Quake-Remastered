#include "..\..\Include\Allocator\pool_allocator.hpp"

//template<typename TBlock>
//PoolAllocator<TBlock>::BlockInfo::BlockInfo(Address addr, size_t i)
//	: address(addr), index(i)
//{
//}
//
//template<typename TBlock>
//PoolAllocator<TBlock>::BlockInfo::operator bool() const
//{
//	return(address != nullptr);
//}
//
//template<typename TBlock>
//PoolAllocator<TBlock>::PoolAllocator(size_t capacity)
//	: _memory(nullptr), _blocks(nullptr), _flags(),
//	_capacity(), _memoryUsed(), _blockSize(), _numBlocks(), _padding()
//{
//	_trueSize = sizeof(TBlock);
//	_padding = (!internal::isPowerOfTwo(_trueSize) ? internal::alignToPowerOfTwo(_trueSize) - _trueSize : 0);
//	_blockSize = _trueSize + _padding;
//	_capacity = (capacity < _blockSize) ? internal::alignToPowerOfTwo(capacity + _blockSize) : internal::alignToPowerOfTwo(capacity);
//
//	_numBlocks = _capacity / _blockSize;
//	_memory = new internal::Byte[_numBlocks];
//	_blocks = new Block[_numBlocks];
//	_flags = internal::BoolSet(_numBlocks);
//	internal::Byte* itr = _memory;
//	for (size_t i = 0; i < _numBlocks; i++)
//	{
//		_blocks[i] = Block(itr, _blockSize);
//		_flags[i] = FREE;
//		itr += _blockSize;
//	}
//}
//
//template<typename TBlock>
//PoolAllocator<TBlock>::~PoolAllocator()
//{
//	//destroy();
//}
//
//template<typename TBlock>
//Block PoolAllocator<TBlock>::allocate(size_t size)
//{
//	size_t allocSize = size;
//	size_t extra = size % _blockSize;
//	if (extra)
//	{
//		allocSize += internal::alignTo(extra, _blockSize) - extra;
//	}
//	if (!internal::isPowerOfTwo(allocSize))
//	{
//		allocSize = internal::alignToPowerOfTwo(allocSize);
//	}
//	bool hasSpace = (allocSize + _memoryUsed <= _capacity);
//	if (!hasSpace)
//	{
//		size_t allocCapac = _capacity + allocSize;
//		size_t expandSize = internal::alignToPowerOfTwo(allocCapac) * 2;
//		//expand(expandSize);
//	}
//	BlockInfo info = _findFree();
//	if (info)
//	{
//		size_t index = info.index;
//		_memoryUsed += allocSize;
//		_flags[index] = ALLOCATED;
//		return(_blocks[index]);
//	}
//	return(DEAD_BLOCK);
//}
//
//template<typename TBlock>
//void PoolAllocator<TBlock>::deallocate(Block& block)
//{
//	Address address = block.address;
//	for (size_t i = 0; i < _numBlocks; i++)
//	{
//		if (_isAllocated(i))
//		{
//			Address blockAddress = _blocks[i].address;
//			if (internal::addressMatch(blockAddress, address))
//			{
//				block.free();
//				_flags[i] = FREE;
//				_memoryUsed -= _blockSize;
//			}
//		}
//	}
//}
//
//template<typename TBlock>
//void PoolAllocator<TBlock>::expand(size_t size)
//{
//
//}
//
//template<typename TBlock>
//void PoolAllocator<TBlock>::destroy()
//{
//}
//
//template<typename TBlock>
//bool PoolAllocator<TBlock>::owns(Block block) const
//{
//	Address address = block.address;
//	for (size_t i = 0; i < _numBlocks; i++)
//	{
//		if (_isAllocated(i))
//		{
//			Address blockAddress = _blocks[i].address;
//			if (internal::addressMatch(blockAddress, address))
//			{
//				return(true);
//			}
//		}
//	}
//	return(false);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getCapacity() const
//{
//	return(_capacity);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getMemoryUsed() const
//{
//	return(_memoryUsed);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getBlockSize() const
//{
//	return(_blockSize);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getNumBlocks() const
//{
//	return(_numBlocks);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getPadding() const
//{
//	return(_padding);
//}
//
//template<typename TBlock>
//size_t PoolAllocator<TBlock>::getTrueSize() const
//{
//	return(_trueSize);
//}
//
//template<typename TBlock>
//bool PoolAllocator<TBlock>::_isFree(size_t index) const
//{
//	return(_flags[index] == FREE);
//}
//
//template<typename TBlock>
//bool PoolAllocator<TBlock>::_isAllocated(size_t index) const
//{
//	return(_flags[index] == ALLOCATED);
//}
//
//template<typename TBlock>
//typename PoolAllocator<TBlock>::BlockInfo
//PoolAllocator<TBlock>::_findFree() const
//{
//	if (!_flags.all())
//	{
//		for (size_t i = 0; i < _numBlocks; i++)
//		{
//			if (_isFree(i))
//			{
//				BlockInfo block(_blocks[i].address, i);
//				return(block);
//			}
//		}
//	}
//	return(BlockInfo());
//}

#include "../../Include/Allocator/pool_allocator.hpp"
