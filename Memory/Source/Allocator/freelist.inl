#include "..\..\Include\Allocator\freelist.hpp"

FreeList::FreeList()
	: _root(nullptr),
	_capacity(),
	_blockSize(),
	_numNodes(),
	_memoryUsed()
{
}

FreeList::FreeList(size_t capacity,size_t blockSize)
	: _root(nullptr), 
	_numNodes(), 
	_memoryUsed()
{
	_blockSize = internal::alignToPowerOfTwo(blockSize);
	_capacity = internal::alignToPowerOfTwo(capacity) * _blockSize;
}

void FreeList::allocate(void* memory)
{
	if (!isFull())
	{
		//Block block(memory, _blockSize);
		Node* node = static_cast<Node*>(memory);
		std::cout << (void*)node << std::endl;
		_setNext(node, _root);
		_root = node;
		_incrementNumNodes();
		_addMemoryUsed();
	}
}

Block FreeList::deallocate()
{
	if (hasFreeMemory() && _memoryUsed + _blockSize <= _capacity)
	{
		Block* block = reinterpret_cast<Block*>(_root);
		_root = _getNext(_root);
		_decrementNumNodes();
		_subtractMemoryUsed();
		return *block;
	}
	return UNALLOCATED_BLOCK;
}

QBool FreeList::owns(Block block) const
{
	return block.length == _blockSize;
}

QBool FreeList::isFull() const
{
	return _memoryUsed == _capacity;
}

QBool FreeList::hasFreeMemory() const
{
	return _numNodes != 0;
}

size_t FreeList::getCapacity() const
{
	return _capacity;
}

size_t FreeList::getNumNodes() const
{
	return _numNodes;
}

size_t FreeList::getMemoryUsed() const
{
	return _memoryUsed;
}

size_t FreeList::getBlockSize() const
{
	return _blockSize;
}

FreeList::Node* FreeList::_getNext(Node* current)
{
	return current->next;
}

void FreeList::_setNext(Node* current, Node* next)
{
	current->next = next;
}

FreeList::Node* FreeList::_blockToNode(Block& block)
{
	return static_cast<Node*>(block.memory);
}

void FreeList::_incrementNumNodes()
{
	_numNodes++;
}

void FreeList::_decrementNumNodes()
{
	_numNodes--;
}

void FreeList::_addMemoryUsed()
{
	_memoryUsed += _blockSize;
}

void FreeList::_subtractMemoryUsed()
{
	_memoryUsed -= _blockSize;
}
