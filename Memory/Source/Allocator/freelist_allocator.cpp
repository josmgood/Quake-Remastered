#include "..\..\Include\Allocator\freelist_allocator.h"

FreeList::Chunk::Chunk(size_t size)
	: block(), next(nullptr)
{
	size_t numBytes = size / sizeof(internal::Byte);
	Address memory = new internal::Byte[numBytes];
	block = Block(memory, size);
}

FreeList::Chunk::Chunk(Block& block)
{
	this->block = block;
}

FreeList::FreeList(size_t capacity, size_t blockSize)
	: _capacity(), _blockSize(), _front(nullptr)
{
	_capacity = (!internal::isPowerOfTwo(capacity) ? internal::alignToPowerOfTwo(capacity) : capacity);
	_blockSize = (!internal::isPowerOfTwo(blockSize) ? internal::alignToPowerOfTwo(blockSize) : blockSize);
	_front = new Chunk(_blockSize);

	size_t numToAlloc = _capacity / _blockSize;
	Chunk* chunk = _front;
	for (size_t i = 1; i < numToAlloc; i++)
	{
		_setNext(chunk, new Chunk(_blockSize));
		chunk = _getNext(chunk);
	}
}

FreeList::~FreeList()
{
	destroy();
}

Block& FreeList::allocate()
{
	if (!_front)
	{
		return(DEAD_BLOCK);
	}

	Chunk* chunk = _front;
	_setNext(_front, _getNext(_front));
	_memoryUsed += _blockSize;
	return(chunk->block);
}

void FreeList::deallocate(Block& block)
{
	if (_matchingSize(block.length, _blockSize))
	{
		Chunk* chunk = new Chunk(block);
		_setNext(chunk, _front);
		_front = chunk;
		block.free();
		_memoryUsed -= _blockSize;
	}
}

void FreeList::expand(size_t amount)
{
	size_t expandSize = (!internal::isPowerOfTwo(amount) ? internal::alignToPowerOfTwo(amount) : amount);
	size_t chunksToAdd = expandSize / _blockSize;
	for (size_t i = 0; i < chunksToAdd; i++)
	{
		Chunk* chunk = new Chunk(_blockSize);
		_setNext(chunk, _front);
		_front = chunk;
	}
	_capacity += expandSize;
}

void FreeList::destroy()
{
	while (_front)
	{
		Chunk* chunk = _front;
		_front = _getNext(_front);
		delete chunk;
	}
}

FreeList::Chunk* FreeList::_getNext(Chunk* chunk)
{
	return(chunk->next);
}

void FreeList::_setNext(Chunk* current, Chunk* next)
{
	current->next = next;
}

bool FreeList::_matchingSize(size_t one, size_t two)
{
	return(one == two);
}