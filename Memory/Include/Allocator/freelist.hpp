#pragma once

#include "base_allocator.h"
#include "null_allocator.h"

#include "..\Internal\auxiliary.h"
#include "..\Internal\traits.h"

#include "..\..\..\Container\Include\qbool.h"
#include "..\..\..\Core\Include\common.h"

/*Batching is incorrect. Make freelist weave many blocks into one block*/

class FreeList
{
public:
	struct Node
	{
		Node* next;
	};
	inline FreeList(size_t capacity, size_t blockSize);
	inline ~FreeList();

	inline Block allocate();
	inline void deallocate(Block& block);
	inline QBool owns(Block block);
	inline void destroy();

	inline QBool isFull() const;
	inline QBool hasFreeMemory() const;

	inline size_t getCapacity() const;
	inline size_t getNumNodes() const;
	inline size_t getMemoryUsed() const;
private:
	inline Node* _getNext(Node* current);
	inline void _setNext(Node* current, Node* next);

	inline Node* _blockToNode(Block& block);

	inline void _incrementNumNodes();
	inline void _decrementNumNodes();

	inline void _addMemoryUsed();
	inline void _subtractMemoryUsed();

	Node* _root;
	size_t _capacity;
	size_t _blockSize;
	size_t _numNodes;
	size_t _memoryUsed;
};

#include "..\..\Source\Allocator\freelist.inl"