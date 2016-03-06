////#include "..\..\Include\Allocator\pool_allocator.hpp"
////
////template<typename Type>
////PoolAllocator<Type>::PoolAllocator(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY, bool canExpand = true)
////	: _capacity(capacity), _canExpand(canExpand), _numAllocations(), _blockSize(sizeof(Type)), _blocks(), _flags(capacity)
////{
////	size_t maxBlocks = _capacity;
////	_blocks = new Block[maxBlocks];
////	for (size_t i = 0; i < maxBlocks; i++)
////	{
////		Address address = new internal::Byte[_blockSize];
////		_blocks[i] = Block(address, _blockSize);
////	}
////}
////
////template<typename Type>
////PoolAllocator<Type>::~PoolAllocator()
////{
////	destroy();
////}
////
////template<typename Type>
////Block* PoolAllocator<Type>::allocate(size_t amount)
////{
////	size_t newAllocSize = _numAllocations + amount;
////	bool hasEnoughSpace = (newAllocSize <= _capacity);
////	if (!hasEnoughSpace && _canExpand)
////	{
////		size_t expandSize = (_numAllocations == 1) ? 1 : _numAllocations / 2;
////		expand(expandSize);
////	}
////	else if (!hasEnoughSpace && !_canExpand)
////	{
////		return(DEAD_BLOCKS);
////	}
////	Block* allocated = new Block[amount];
////	size_t max = _capacity;
////	size_t allocsNeeded = amount;
////	for (size_t i = 0, j = 0; i < max && j != allocsNeeded; i++)
////	{
////		if (_isFree(_flags[i]))
////		{
////			allocated[j] = _blocks[i];
////			_flags[i] = ALLOCATED;
////			j++;
////		}
////		if (i == max && j < allocsNeeded)
////		{
////			return(DEAD_BLOCKS);
////		}
////	}
////	_incrementNumAllocations();
////	return(allocated);
////}
////
////template<typename Type>
////void PoolAllocator<Type>::deallocate(Block* toDealloc, size_t amount)
////{
////	size_t max = _capacity;
////	size_t deallocsNeeded = amount;
////	for (size_t i = 0, j = 0; ji < max && j != deallocsNeeded; i++)
////	{
////		if (_isAllocated(_flags[i]))
////		{
////			Address address = _getAddressAt(i);
////			Address blockAddress = toDealloc[j].address;
////			if (internal::addressMatch(addressMatch(address, blockAddress)))
////			{
////				_flags[i] = FREE;
////				toDealloc[j].free();
////				_decrementNumAllocations();
////				j++;
////			}
////		}
////	}
////}
////
////template<typename Type>
////void PoolAllocator<Type>::expand(size_t amount)
////{
////	size_t oldCapacity = _capacity;
////	size_t newCapacity = oldCapacity + amount;
////	Block* newBlocks = new Block[newCapacity];
////	internal::BoolSet newFlags(newCapacity);
////	for (size_t i = 0, j = 0; i < newCapacity; i++)
////	{
////		if (j < oldCapacity)
////		{
////			if (_isAllocated(_flags[j]))
////			{
////				newBlocks[j] = _blocks[j];
////				newFlags[j] = ALLOCATED;
////			}
////			j++;
////		}
////		else
////		{
////			Address address = new internal::Byte[_blockSize];
////			newBlocks[i] = Block(address, _blockSize);
////		}
////	}
////	_setCapacity(newCapacity);
////	_setBlocks(newBlocks);
////	_setFlags(newFlags);
////}
////
////template<typename Type>
////bool PoolAllocator<Type>::owns(Block block) const
////{
////	size_t capacity = _capacity;
////	for (size_t i = 0; i < capacity; i++)
////	{
////		if (_isAllocated(_flags[i]))
////		{
////			Address address = _getAddressAt(i);
////			Address blockAddress = block.address;
////			if (internal::addressMatch(address, blockAddress))
////			{
////				return(true);
////			}
////		}
////	}
////	return(false);
////}
////
////template<typename Type>
////void PoolAllocator<Type>::destroy()
////{
////	size_t capacity = _capacity;
////	for (size_t i = 0; i < capacity; i++)
////	{
////		delete[] _blocks[i].address;
////	}
////	delete[] _blocks;
////	_canExpand = true;
////	_setCapacity(0);
////	_setNumAllocations(0);
////	_flags.clear();
////}
////
////template<typename Type>
////bool PoolAllocator<Type>::canExpand() const
////{
////	return(_canExpand);
////}
////
////template<typename Type>
////size_t PoolAllocator<Type>::getCapacity() const
////{
////	return(_capacity);
////}
////
////template<typename Type>
////size_t PoolAllocator<Type>::getNumAllocations() const
////{
////	return(_numAllocations);
////}
////
////template<typename Type>
////size_t PoolAllocator<Type>::getBlockSize() const
////{
////	return(_blockSize);
////}
////
////template<typename Type>
////bool PoolAllocator<Type>::_isFree(bool flag) const
////{
////	return(flag == FREE);
////}
////
////template<typename Type>
////bool PoolAllocator<Type>::_isAllocated(bool flag) const
////{
////	return(flag == ALLOCATED);
////}
////
////template<typename Type>
////Address PoolAllocator<Type>::_getAddressAt(size_t index) const
////{
////	return((_blocks[index]) ? _blocks[index].address : nullptr);
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_addCapacity(size_t amount)
////{
////	_capacity += amount;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_setCapacity(size_t capacity)
////{
////	_capacity = capacity;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_incrementNumAllocations()
////{
////	_numAllocations++;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_decrementNumAllocations()
////{
////	_numAllocations--;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_setNumAllocations(size_t num)
////{
////	_numAllocations = num;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_setBlocks(Block* blocks)
////{
////	_blocks = blocks;
////}
////
////template<typename Type>
////void PoolAllocator<Type>::_setFlags(const internal::BoolSet& flags)
////{
////	_flags = flags;
////}
//
#include "../../Include/Allocator/pool_allocator.hpp"

namespace mem
{
	template<typename TBlock>
	PoolAllocator<TBlock>::PoolAllocator(size_t capacity)
		: _memory(), _capacity(), _memoryUsed(), _blockSize(), _padding(), _trueSize()
	{
		_capacity = (!internal::isPowerOfTwo(capacity) ? internal::alignToPowerOfTwo(capacity) : capacity);
		_blockSize = sizeof(TBlock);
		_padding = (!internal::isPowerOfTwo(_blockSize) ? internal::alignToPowerOfTwo(_blockSize) - _blockSize : 0);
		_trueSize = _blockSize + _padding;
		
		size_t numBlocks = _capacity / _trueSize;
		_memory = new internal::Byte[numBlocks];
	}

	template<typename TBlock>
	PoolAllocator<TBlock>::~PoolAllocator()
	{
		//destroy();
	}

	template<typename TBlock>
	Block PoolAllocator<TBlock>::allocate(size_t size)
	{
		//size_t allocSize = (!internal::isPowerOfTwo(size) ? internal::byteAlign(size) : size);
		//size_t allocSize = ((size % _trueSize == 0) 
		//						? internal::alignTo(size, ) : size);

		size_t numBlocks = size % _blockSize;
		std::cout << numBlocks << std::endl;
		size_t allocSize = size;//= (!internal::isPowerOfTwo(size) ? internal:: : size);
		if (size % _trueSize != 0)
		{
			size_t rem = size % _trueSize;
			
		}
		if (!internal::isPowerOfTwo(allocSize) && allocSize < _trueSize)
		{

		}

		bool hasSpace = (allocSize + _capacity <= _capacity);
		if (!hasSpace)
		{
			//expand
		}
		size_t numToAlloc = allocSize / _trueSize;
		return(DEAD_BLOCK);
	}

	template<typename TBlock>
	void PoolAllocator<TBlock>::deallocate(Block& block)
	{

	}

	template<typename TBlock>
	void PoolAllocator<TBlock>::expand(size_t size)
	{

	}

	template<typename TBlock>
	void PoolAllocator<TBlock>::destroy()
	{
	}

	template<typename TBlock>
	bool PoolAllocator<TBlock>::owns(Block block) const
	{
		size_t size = _capacity / _trueSize;
		Block itr(_memory[0], _trueSize);
		for (size_t i = 0; i < size; i++)
		{
			if (itr.baseAddr == block.baseAddr)
			{
				return(true);
			}
		}
		return(false);
	}

	template<typename TBlock>
	size_t PoolAllocator<TBlock>::getCapacity() const
	{
		return(_capacity);
	}

	template<typename TBlock>
	size_t PoolAllocator<TBlock>::getMemoryUsed() const
	{
		return(_memoryUsed);
	}
	
	template<typename TBlock>
	size_t PoolAllocator<TBlock>::getBlockSize() const
	{
		return(_blockSize);
	}

	template<typename TBlock>
	size_t PoolAllocator<TBlock>::getPadding() const
	{
		return(_padding);
	}

	template<typename TBlock>
	size_t PoolAllocator<TBlock>::getTrueSize() const
	{
		return(_trueSize);
	}
}