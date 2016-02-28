#include "..\Include\pool_allocator.hpp"

template<typename Type>
PoolAllocator<Type>::PoolAllocator(size_t numBlocks, bool allowExpansion)
	: BaseAllocator(sizeof(Type) * numBlocks), _blockSize(sizeof(Type)), 
	_numBlocks(numBlocks), _blocks(), _flags(numBlocks)
{
	setExpansionAllowance(allowExpansion);
	size_t blockSize = _blockSize;
	_blocks = new Block[numBlocks];
	for (size_t i = 0; i < numBlocks; i++)
	{
		void* addrs = new internal::Byte[blockSize];
		_blocks[i] = Block(addrs, blockSize);
	}
}

template<typename Type>
PoolAllocator<Type>::~PoolAllocator()
{
	destroy();
}

template<typename Type>
Block* PoolAllocator<Type>::allocate(size_t amount)
{
	size_t capacity = _capacity;
	size_t allocedSize = _allocatedSize;
	size_t reqSize = amount * _blockSize;
	size_t numBlocks = _numBlocks;
	bool hasEnoughSpace = (allocedSize + reqSize <= capacity);
	if (!hasEnoughSpace)
	{
		size_t expandSize = (numBlocks == 1) ? 1 : numBlocks / 2;
		expand(expandSize);
	}
	Block* allocated = new Block[amount];
	size_t max = _numBlocks;
	size_t allocsNeeded = amount;
	size_t blockSize = _blockSize;
	for (size_t i = 0, j = 0; i < max && j != allocsNeeded; i++)
	{
		if (_isFree(_flags[i]))
		{
			allocated[j] = _blocks[i];
			_flags[i] = ALLOCATED;
			j++;
		}
		if (i == max - 1 && j < allocsNeeded)
		{
			return(DEAD_BLOCKS);
		}
	}
	_incrementNumAllocations();
	_addAllocationSize(amount * blockSize);
	return(allocated);
}

template<typename Type>
void PoolAllocator<Type>::deallocate(Block* toDealloc, size_t amount)
{
	size_t max = _capacity;
	size_t deallocsNeeded = amount;
	size_t blockSize = _blockSize;
	for (size_t i = 0, j = 0; i < max && j != deallocsNeeded; i++)
	{
		if (_isAllocated(_flags[i]))
		{
			void* address = _addressAt(i);
			void* blockAddr = toDealloc[j].address;
			if (internal::addressMatch(blockAddr, address))
			{
				_flags[i] = FREE;
				toDealloc[j].free();
				_decrementNumAllocations();
				_subAllocationSize(blockSize);
				j++;
			}
		}
	}
}

template<typename Type>
void PoolAllocator<Type>::expand(size_t amount)
{
	size_t blockSize = _blockSize;
	size_t newCapacity = _capacity + (amount * blockSize);
	size_t newNumBlocks = _numBlocks + amount;
	size_t oldCapacity = _capacity;
	size_t oldNumBlocks = _numBlocks;
	Block* newBlocks = new Block[newNumBlocks];
	internal::BoolSet newFlags(newNumBlocks);
	for (size_t i = 0, j = 0; i < newNumBlocks; i++)
	{
		if (j < oldNumBlocks)
		{
			if (_isAllocated(_flags[j]))
			{
				newBlocks[i] = _blocks[j];
				newFlags[j] = ALLOCATED;
			}
			j++;
		}
		else
		{
			void* address = new internal::Byte[blockSize];
			newBlocks[i] = Block(address, blockSize);
		}
	}
	_setCapacity(newCapacity);
	_setNumBlocks(newNumBlocks);
	_setBlocks(newBlocks);
	_setFlags(newFlags);
}

template<typename Type>
bool PoolAllocator<Type>::owns(Block block)
{
	size_t capacity = _capacity;
	for (size_t i = 0; i < capacity; i++)
	{
		if (_isAllocated(_flags[i]))
		{
			void* address = _blocks[i].address;
			void* blockAddress = block.address;
			if (internal::addressMatch(blockAddress, address))
			{
				return(true);
			}
		}
	}
	return(false);
}

template<typename Type>
void PoolAllocator<Type>::reset()
{
	BaseAllocator::reset();
	_blocks = nullptr;
	_flags.reset();
}

template<typename Type>
void PoolAllocator<Type>::destroy()
{
	size_t capacity = _capacity;
	for (size_t i = 0; i < capacity; i++)
	{
		delete[] _blocks[i].address;
	}
	delete[] _blocks;
	reset();
}

template<typename Type>
size_t PoolAllocator<Type>::getBlockSize() const
{
	return(_blockSize);
}

template<typename Type>
size_t PoolAllocator<Type>::getNumBlocks() const
{
	return(_numBlocks);
}

template<typename Type>
bool PoolAllocator<Type>::_isFree(bool flag)
{
	return(flag == FREE);
}

template<typename Type>
bool PoolAllocator<Type>::_isAllocated(bool flag)
{
	return(flag == ALLOCATED);
}

template<typename Type>
void* PoolAllocator<Type>::_addressAt(size_t index)
{
	return((!_blocks[index]) 
		? nullptr : _blocks[index].address);
}

template<typename Type>
void PoolAllocator<Type>::_setNumBlocks(size_t num)
{
	_numBlocks = num;
}

template<typename Type>
void PoolAllocator<Type>::_setBlocks(Block* blocks)
{
	_blocks = blocks;
}

template<typename Type>
void PoolAllocator<Type>::_setFlags(const internal::BoolSet& flgs)
{
	_flags = flgs;
}