#include "..\..\Include\Allocator\pool_allocator.hpp"

template<typename TBlock>
PoolAllocator<TBlock>::PoolAllocator(size_t capacity, QBool expandStatus)
	: _capacity(internal::alignToPowerOfTwo(capacity)),
	_memoryUsed(),
	_flags(),
	_canExpand(expandStatus)
{
	_trueSize = sizeof(TBlock);
	_padding = (!internal::isPowerOfTwo(_trueSize) ? internal::alignToPowerOfTwo(_trueSize) - _trueSize : 0);
	_blockSize = _trueSize + _padding;
	_numBlocks = _capacity / _blockSize;
	_memory = new internal::Byte[_numBlocks];
	_blocks = new Block[_numBlocks];
	_flags = internal::BoolSet(_numBlocks);

	internal::Byte* itr = _memory;
	for (size_t i = 0; i < _numBlocks; i++)
	{
		_blocks[i] = Block(itr, _blockSize);
		itr += _blockSize;
	}
}

template<typename TBlock>
PoolAllocator<TBlock>::~PoolAllocator()
{
	destroy();
}

template<typename TBlock>
Block PoolAllocator<TBlock>::allocate()
{
	bool hasSpace = (_memoryUsed + _blockSize <= _capacity);
	if (_canExpand && !hasSpace)
	{
		size_t size = internal::alignToPowerOfTwo(_capacity / 3);
		//expand(size);
	}
	Block block = _findBlock();
	if (block)
	{
		_memoryUsed += _blockSize;
		return block;
	}
	return UNALLOCATED_BLOCK;
}

template<typename TBlock>
void PoolAllocator<TBlock>::deallocate(Block& block)
{
	void* memory = block.memory;
	for (size_t i = 0; i < _numBlocks; i++)
	{
		if (_isAllocated(i))
		{
			void* blockMemory = _blocks[i].memory;
			if (internal::memoryMatch(memory, blockMemory))
			{
				_flags[i] = FREE;
				block.free();
			}
		}
	}
}

template<typename TBlock>
QBool PoolAllocator<TBlock>::owns(Block block) const
{
	void* memory = block.memory;
	for (size_t i = 0; i < _numBlocks; i++)
	{
		void* blockMemory = _blocks[i].memory;
		if (_isAllocated(i))
		{
			if (internal::memoryMatch(memory, blockMemory))
			{
				return true;
			}
		}
	}
	return false;
}

template<typename TBlock>
void PoolAllocator<TBlock>::destroy()
{
	delete[] _memory;
	delete[] _blocks;
	_freeList.destroy();
	_memoryUsed = 0;
	_flags.clear();
}

template<typename TBlock>
void PoolAllocator<TBlock>::setExpandProtocol(QBool protocol)
{
	_canExpand = protocol;
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

template<typename TBlock>
QBool PoolAllocator<TBlock>::_isFree(size_t index) const
{
	return _flags[index] == FREE;
}

template<typename TBlock>
QBool PoolAllocator<TBlock>::_isAllocated(size_t index) const
{
	return _flags[index] == ALLOCATED;
}

template<typename TBlock>
Block PoolAllocator<TBlock>::_findBlock()
{
	if (!_flags.all())
	{
		for (size_t i = 0; i < _numBlocks; i++)
		{
			if (_isFree(i))
			{
				_flags[i] = ALLOCATED;
				return _blocks[i];
			}
		}
	}
	return UNALLOCATED_BLOCK;
}