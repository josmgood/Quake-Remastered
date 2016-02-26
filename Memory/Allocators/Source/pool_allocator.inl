#include "..\Include\pool_allocator.hpp"

template<size_t chunkSize>
PoolAllocator<chunkSize>::_Chunk::_Chunk(void)
	: block(new internal::Byte[chunkSize]), next(nullptr), state(_Chunk::STATE::FREE)
{
}

template<size_t chunkSize>
bool PoolAllocator<chunkSize>::_ChunkPacket::operator!=(const _ChunkPacket& other)
{
	return(this->curr != other.curr
		&& this->prev != other.prev);
}

template<size_t chunkSize>
PoolAllocator<chunkSize>::_ChunkPacket::_ChunkPacket(_Chunk* cu, _Chunk* pr)
	: curr(cu), prev(pr)
{
}

template<size_t chunkSize>
PoolAllocator<chunkSize>::PoolAllocator(size_t capacity, bool allowExpansion)
	: _front(nullptr), _back(nullptr), _free(nullptr), _capacity(capacity), _numAllocatedChunks(),
	DEAD_CHUNK_PACKET(nullptr, nullptr)
{
	setExpansionAllowance(allowExpansion);

	size_t backPos = capacity - 1;
	_front = _back = new _Chunk;
	_Chunk* chunk = _front;
	for (size_t i = 0; i < capacity; i++)
	{	
		_setNext(chunk, new _Chunk);
		chunk = _getNext(chunk);
		if (i == backPos)
		{
			_back = chunk;
		}
	}
}

template<size_t chunkSize>
PoolAllocator<chunkSize>::~PoolAllocator(void)
{
	destroy();
}

template<size_t chunkSize>
Block PoolAllocator<chunkSize>::allocate(void)
{
	size_t allocatedSize = _numAllocatedChunks;
	size_t capacity = _capacity;
	if (allocatedSize++ > capacity && isAllowingExpansion())
	{
		size_t expanSize = (capacity > 1) ? capacity / 2 : 1;
		expand(expanSize);
	}
	bool hasFreeChunks = (capacity - allocatedSize > 0);
	if (hasFreeChunks)
	{
		_ChunkPacket packet = _findFree();
		if (packet != DEAD_CHUNK_PACKET)
		{
			Block block(reinterpret_cast<void*>(packet.curr->block), chunkSize);
			packet.curr->state = _Chunk::STATE::ALLOCATED;
			_setNext(_back, packet.curr);
			_setNext(packet.prev, _getNext(packet.curr));
			if (_isFree(packet.prev))
			{
				_free = packet.prev;
			}
			_back = _getNext(_back);
			_numAllocatedChunks++;
			return(block);
		}
	}
	return(DEAD_BLOCK);
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::deallocate(Block& block)
{
	_ChunkPacket packet = _findChunk(block);
	if (packet != DEAD_CHUNK_PACKET)
	{
		block.free();
		packet.curr->state = _Chunk::STATE::FREE;
		_setNext(packet.prev, _getNext(packet.curr));
		_setNext(packet.curr, _front);
		_front = packet.curr;
		_numAllocatedChunks--;
	}
}

template<size_t chunkSize>
bool PoolAllocator<chunkSize>::owns(Block block)
{
	for (_Chunk* itr = _front; itr; itr = _getNext(itr))
	{
		if ((void*)itr->block == block.address)
		{
			return(true);
		}
	}
	return(false);
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::expand(size_t amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		_allocateNewChunk();
	}
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::reset(void)
{
	_front = nullptr;
	_capacity = 0;
	_numAllocatedChunks = 0;
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::destroy(void)
{
	size_t capacity = _capacity;
	_Chunk* itr = _getNext(_front);
	for (size_t i = 0; i < capacity; i++)
	{
		_Chunk* tmp = itr;
		if (_getNext(itr))
		{
			itr = _getNext(itr);
		}
		delete[] tmp->block;
		delete tmp;
	}
	reset();
}

template<size_t chunkSize>
size_t PoolAllocator<chunkSize>::getChunkCapacity(void) const
{
	return(_capacity);
}

template<size_t chunkSize>
size_t PoolAllocator<chunkSize>::getNumAllocatedChunks(void) const
{
	return(_numAllocatedChunks);
}

template<size_t chunkSize>
typename PoolAllocator<chunkSize>::_Chunk* 
PoolAllocator<chunkSize>::_getNext(_Chunk* chunk) const
{
	return(chunk->next);
}

template<size_t chunkSize>
void PoolAllocator<chunkSize>::_setNext(_Chunk* chunk, _Chunk* _next)
{
	chunk->next = _next;
}

template<size_t chunkSize>
typename PoolAllocator<chunkSize>::_ChunkPacket
PoolAllocator<chunkSize>::_findFree(void)
{
	for (_Chunk* pItr = _front, *cItr = _front;
		pItr && cItr; 
		pItr = _getNext(pItr), cItr = _getNext(cItr))
	{
		if (_isFree(cItr))
		{
			return(_ChunkPacket(cItr, pItr));
		}
		cItr = _getNext(cItr);
	}
	return(DEAD_CHUNK_PACKET);
}

template<size_t chunkSize>
typename PoolAllocator<chunkSize>::_ChunkPacket
PoolAllocator<chunkSize>::_findChunk(Block& block)
{
	for (_Chunk* pItr = _front, *cItr = _front;
		pItr && cItr;
		pItr = _getNext(pItr), cItr = _getNext(cItr))
	{
		if ((void*)cItr->block == block.address)
		{
			return(_ChunkPacket(cItr, pItr));
		}
		cItr = _getNext(cItr);
	}
	return(DEAD_CHUNK_PACKET);
}

template<size_t chunkSize>
bool PoolAllocator<chunkSize>::_isFree(_Chunk* chunk)
{
	return(chunk->state == _Chunk::STATE::FREE);
}

template<size_t chunkSize>
typename PoolAllocator<chunkSize>::_Chunk*
PoolAllocator<chunkSize>::_allocateNewChunk(void)
{
	_Chunk* newChunk = new _Chunk;
	_setNext(newChunk, _front);
	_front = newChunk;
	_capacity++;
	return(newChunk);
}