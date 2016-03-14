#include "..\..\Include\Allocator\pool_allocator.hpp"

template<typename TBlock>
PoolAllocator<TBlock>::PoolAllocator(size_t capacity)
	: _memoryUsed(), 
	_freeList(capacity, sizeof(TBlock))
{
	_trueSize = sizeof(TBlock);
	_padding = (!internal::isPowerOfTwo(_trueSize) ? internal::alignToPowerOfTwo(_trueSize) - _trueSize : 0);
	_blockSize = _trueSize + _padding;
	_capacity = internal::alignToPowerOfTwo(capacity) * _blockSize;
	_numBlocks = _capacity / _blockSize;
	_memory = new internal::Byte[_numBlocks];

	internal::Byte* itr = _memory;
	for (size_t i = 0; i < _numBlocks; i++)
	{
		std::cout << i << ": " << (void*)itr << std::endl;
		_freeList.allocate(itr);
		itr += _blockSize;
	}
}

template<typename TBlock>
PoolAllocator<TBlock>::~PoolAllocator()
{
	destroy();
}

template<typename TBlock>
Block* PoolAllocator<TBlock>::allocate(size_t size)
{
	size_t allocSize = internal::alignToPowerOfTwo(size);
	bool hasSpace = (_memoryUsed + allocSize <= _capacity);
	if (hasSpace)
	{
		size_t numToAlloc = allocSize / _blockSize;
		Block* blocks = new Block[numToAlloc];
		for (size_t i = 0; i < numToAlloc; i++)
		{
			blocks[i] = _freeList.deallocate();
		}
		_memoryUsed += allocSize;
		return blocks;
	}
	return UNALLOCATED_BLOCKS;
}


template<typename TBlock>
void PoolAllocator<TBlock>::deallocate(Block* blocks, size_t count)
{
	if (blocks)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (_freeList.owns(blocks[i]))
			{
				_freeList.allocate(blocks[i].memory);
			}
			size_t allocSize = count * _blockSize;
			_memoryUsed -= allocSize;
		}
	}
}

template<typename TBlock>
QBool PoolAllocator<TBlock>::owns(Block block) const
{
	return _freeList.owns(block);
}

template<typename TBlock>
void PoolAllocator<TBlock>::destroy()
{
	delete[] _memory;
}

template<typename TBlock>
size_t PoolAllocator<TBlock>::getCapacity() const
{
	return _capacity;
}

template<typename TBlock>
size_t PoolAllocator<TBlock>::getMemoryUsed() const
{
	return _memoryUsed;
}

template<typename TBlock>
size_t PoolAllocator<TBlock>::getBlockSize() const
{
	return _blockSize;
}

template<typename TBlock>
size_t PoolAllocator<TBlock>::getPadding() const
{
	return _padding;
}

template<typename TBlock>
size_t PoolAllocator<TBlock>::getTrueSize() const
{
	return _trueSize;
}