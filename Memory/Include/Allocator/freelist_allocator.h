#pragma once

#include "base_allocator.h"

#include "..\Internal\auxiliary.h"

class FreeList
{
public:
	struct Chunk
	{
		Chunk(size_t size);
		Chunk(Block& block);
		Block block;
		Chunk* next;
	};
	FreeList(size_t capacity = DEFAULT_ALLOCATOR_CAPACITY, size_t blockSize = 1);
	~FreeList();

	Block& allocate();
	void deallocate(Block& block);
	void expand(size_t amount);
	void destroy();
private:
	Chunk* _getNext(Chunk* chunk);
	void _setNext(Chunk* current, Chunk* next);
	bool _matchingSize(size_t one, size_t two);

	size_t _capacity;
	size_t _memoryUsed;
	size_t _blockSize;
	Chunk* _front;
};