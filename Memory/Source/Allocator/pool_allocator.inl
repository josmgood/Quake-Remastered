#include "..\..\Include\Allocator\pool_allocator.hpp"
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
//	_flags = internal::QBoolSet(_numBlocks);
//	internal::Byte* itr = _memory;
//	for (size_t i = 0; i < _numBlocks; i++)
//	{
//		_blocks[i] = Block(itr, _blockSize);
//		_flags[i] = FREE;
//		itr += _blockSize;
//	}
//}
//
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
//	QBool hasSpace = (allocSize + _memoryUsed <= _capacity);
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
//	return(UNALLOCATED_BLOCK);
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
//QBool PoolAllocator<TBlock>::owns(Block block) const
//{
//	Address address = block.address;
//	for (size_t i = 0; i < _numBlocks; i++)
//	{
//		if (_isAllocated(i))
//		{
//			Address blockAddress = _blocks[i].address;
//			if (internal::addressMatch(blockAddress, address))
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//

#include "../../Include/Allocator/pool_allocator.hpp"

template<typename TBlock>
PoolAllocator<TBlock>::PoolAllocator(size_t capacity, QBool expandStatus)
	: _capacity(internal::alignToPowerOfTwo(capacity)),
	_memoryUsed(),
	_freeList(_capacity, internal::alignToPowerOfTwo(sizeof(TBlock))),
	_canExpand(expandStatus)
{
	_trueSize = sizeof(TBlock);
	_padding = (!internal::isPowerOfTwo(_trueSize) ? internal::alignToPowerOfTwo(_trueSize) - _trueSize : 0);
	_blockSize = _trueSize + _padding;
	_numBlocks = _capacity / _blockSize;
	_memory = new internal::Byte[_numBlocks];
	_blocks = new Block[_numBlocks];
	_flags = internal::BoolSet(_numBlocks);

	//for (size_t i = 0; i < _numBlocks; i++)
	//{
	//	_blocks[i] = UNALLOCATED_BLOCK;
	//	//_flags[i] = FREE;
	//}
}

template<typename TBlock>
PoolAllocator<TBlock>::~PoolAllocator()
{
	//destroy();
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
	Block block = (_freeList.hasFreeMemory() ? _freeList.allocate() : _findBlock(true));
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
	/*void* memory = block.memory;
	for (size_t i = 0; i < _numBlocks; i++)
	{
		if (_isAllocated(i))
		{
			void* blockMemory = _blocks[i].memory;
			if (internal::memoryMatch(memory, blockMemory))
			{
				if (!_freeList.isFull())
				{
					_freeList.deallocate(block);
				}
			}
		}
	}*/
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
QBool PoolAllocator<TBlock>::_isFree(size_t index) const
{
	return _flags[index] == FREE && 
		_blocks[index] != UNALLOCATED_BLOCK;
}

template<typename TBlock>
QBool PoolAllocator<TBlock>::_isAllocated(size_t index) const
{
	return _flags[index] == ALLOCATED && 
		_blocks[index] != UNALLOCATED_BLOCK;
}

template<typename TBlock>
QBool PoolAllocator<TBlock>::_isUnallocated(size_t index) const
{
	return _blocks[index] == UNALLOCATED_BLOCK;
}

template<typename TBlock>
Block& PoolAllocator<TBlock>::_findBlock(QBool flag)
{
	if (!_flags.all())
	{
		for (size_t i = 0; i < _numBlocks; i++)
		{
			if (_isUnallocated(i))
			{
				std::cout << "Unallocated" << std::endl;
				size_t blockPos =  i * _blockSize;
				internal::Byte* bytePos = _memory;
				bytePos += blockPos;
				Block block(bytePos, _blockSize);
				_flags[i] = ALLOCATED;
				return block;
			}
			if (_isFree(i))
			{
				std::cout << "Free" << std::endl;
				if (flag)
				{
					_flags[i] = ALLOCATED;
				}
				return _blocks[i];
			}
		}
	}
	return UNALLOCATED_BLOCK;
}