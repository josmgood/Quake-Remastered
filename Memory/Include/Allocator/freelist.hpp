#pragma once

#pragma warning(disable : 4522)
#pragma warning(disable : 4521)

#include "base_allocator.h"
#include "null_allocator.h"

#include "..\Internal\auxiliary.h"
#include "..\Internal\traits.h"

#include "..\..\..\Container\Include\qbool.h"
#include "..\..\..\common.h"

/*Batching is incorrect. Make freelist weave many blocks into one block*/

class FreeList
{
public:
	struct Node
	{
		Node* next;
	};
	inline FreeList();
	inline FreeList(size_t capacity, size_t blockSize);

	inline void allocate(Block& block);
	inline Block deallocate();
	inline QBool owns(Block block) const;
	inline void init(size_t capacity, size_t blockSize);

	inline QBool isFull() const;
	inline QBool hasSpaceFor(size_t num) const;
	inline QBool hasNumFree(size_t num) const;
	inline QBool hasFreeNodes() const;

	inline size_t getCapacity() const;
	inline size_t getNumAllocated() const;
	inline size_t getNumNodes() const;
	inline size_t getMemoryUsed() const;
	inline size_t getBlockSize() const;
	inline QBool isInitialized() const;
private:
	inline Node* _getNext(Node* current);
	inline void _setNext(Node* current, Node* next);

	inline void _incrementNumAllocated();
	inline void _decrementNumAllocated();

	inline void _addMemoryUsed();
	inline void _subtractMemoryUsed();

	inline QBool _supports(Block block);

	Node* _root;
	size_t _capacity;
	size_t _blockSize;
	size_t _numAllocated;
	size_t _numNodes;
	size_t _memoryUsed;
	QBool _isInitialized;

	FreeList(FreeList&) = delete;
	FreeList(const FreeList&) = delete;
	FreeList(FreeList&&) = delete;
	FreeList operator=(FreeList&) = delete;
	FreeList& operator=(const FreeList&) = delete;
	FreeList* operator&() = delete;

	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
};

#include "..\..\Source\Allocator\freelist.inl"