#include "..\Include\pool_allocator.hpp"

template<size_t chunkSize>
PoolAllocator<chunkSize>::PoolAllocator(size_t chunkCapacity)
	: _pool(), _front(nullptr), _chunkCapacity(chunkCapacity),
	_numAllocatedChunks()
{
	setExpansionAllowance(true);
	_pool = new internal::Byte*[chunkCapacity];
	for (size_t i = 0; i < chunkCapacity; i++)
	{
		_pool[i] = new internal::Byte[FULL_CHUNK];
	}
	_front = _pool[0];
}

template<size_t chunkSize>
PoolAllocator<chunkSize>::~PoolAllocator(void)
{
	destory();
}

template<size_t chunkSize>
Block PoolAllocator<chunkSize>::allocate(void)
{
	size_t capacity =	_chunkCapacity;
	size_t numChunks =	_numAllocatedChunks;
	size_t size =		FULL_CHUNK;
	//std::cout << "Num Chunks: " << numChunks << std::endl;
	if (numChunks++ >= capacity && isAllowingExpansion())
	{
		expand(_chunkCapacity / 2);
	}
	else if(numChunks++ > capacity && !isAllowingExpansion())
	{
		return(DEAD_BLOCK);
	}
	Block block(reinterpret_cast<void*>(_front), size);
	//std::cout << _numAllocatedChunks << std::endl;
	_numAllocatedChunks++;
	//_front = _pool[0];
	_front = _pool[_numAllocatedChunks];
	return block;

	/*//size_t cap = _chunkCapacity;
	//size_t numChunks = _numAllocatedChunks;
	//bool allowExpan = _allowExpansion;
	//if (numChunks++ > cap && allowExpan)
	//{
	//	expand(cap / 2);
	//}
	//else if(numChunks++ > cap && !allowExpan)
	//{
	//	return(DEAD_BLOCK);
	//}
	//internal::Byte* addr = _front;
	////_getNext(_front);
	//_front += FULL_CHUNK;//= _getNext(_front);
	//Block block(reinterpret_cast<void*>(addr + FULL_CHUNK), FULL_CHUNK);
	//_numAllocatedChunks++;
	//return(block);*/
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::deallocate(Block& block)
{
	//internal::Byte* freeBlock = ((internal::Byte*)block.address) - CHUNK_HEADER_SIZE;
	block.free();
	_numAllocatedChunks--;
	_front = _pool[0];
	//_setNext(freeBlock, _front);
}

template<size_t chunkSize>
bool PoolAllocator<chunkSize>::owns(Block block)
{
	size_t counter = 0;
	for (internal::Byte* itr = _pool[0]; counter < _numAllocatedChunks; itr++, counter++)
	{
		if (itr == block.address)
		{
			return(true);
		}
	}
	return(false);
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::expand(size_t amount)
{
	size_t newCapacity = _chunkCapacity + amount;
	size_t oldCapacity = _chunkCapacity;
	internal::Byte** newPool = new internal::Byte*[newCapacity];
	for (size_t i = 0; i < newCapacity; i++)
	{
		newPool[i] = new internal::Byte[FULL_CHUNK];
	}
	for (size_t i = 0; i < oldCapacity; i++)
	{
		newPool[i] = _pool[i];
	}
	_chunkCapacity = newCapacity;
	_front = (newPool[0] + (_numAllocatedChunks * FULL_CHUNK));
	_pool = newPool;
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::reset(void)
{
	_pool = nullptr;
	_front = nullptr;
	_chunkCapacity = 0;
	_numAllocatedChunks = 0;
	_allowExpansion = true;
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::destory(void)
{
	for (size_t i = 0; i < _chunkCapacity; i++)
	{
		free(_pool[i]);
	}
	free(_pool);
	reset();
}

template<size_t chunkSize>
size_t PoolAllocator<chunkSize>::getChunkCapacity(void) const
{
	return(_chunkCapacity);
}

template<size_t chunkSize>
size_t PoolAllocator<chunkSize>::getNumAllocatedChunks(void) const
{
	return(_numAllocatedChunks);
}

//template<size_t chunkSize>
//internal::Byte* PoolAllocator<chunkSize>::_getNext(internal::Byte* block)
//{
//	internal::Byte** chunkHeader = (internal::Byte**)block;
//	std::cout << "Block: " << block << std::endl;
//	std::cout << "Next Block: " << chunkHeader[0] << std::endl;
//	return chunkHeader[0];
//}
//
template<size_t chunkSize>
void PoolAllocator<chunkSize>::_setNext(internal::Byte* block, internal::Byte* next)
{
	internal::Byte** chunkHeader = (internal::Byte**)block;
	chunkHeader[0] = next;
}

template<size_t chunkSize>
internal::Byte* PoolAllocator<chunkSize>::_search(void)
{

}