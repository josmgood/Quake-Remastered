#include "..\..\Include\Allocator\freelist.hpp"

FreeList::FreeList(size_t capacity,size_t blockSize)
	: _root(nullptr), 
	_capacity(internal::alignToPowerOfTwo(capacity)),
	_blockSize(internal::alignToPowerOfTwo(blockSize)), 
	_numNodes(), 
	_memoryUsed()
{
}

FreeList::~FreeList()
{
	destroy();
}

Block FreeList::allocate()
{
	if (hasFreeMemory())
	{
		Block block(_root, _blockSize);
		_root = _getNext(_root);
		_decrementNumNodes();
		_subtractMemoryUsed();
		return(block);
	}
	return(UNALLOCATED_BLOCK);
}

void FreeList::deallocate(Block& block)
{
	size_t length = block.length;
	if (block)
	{
		if (_memoryUsed + length <= _capacity)
		{
			Node* node = _blockToNode(block);
			_setNext(node, _root);
			_root = node;
			_incrementNumNodes();
			_addMemoryUsed();
		}
	}
}

QBool FreeList::owns(Block block)
{
	return block.length == _blockSize;
}

void FreeList::destroy()
{
	for (size_t i = 0; i < _numNodes; i++)
	{
		Node* node = _root;
		_root = _getNext(_root);
		delete node;
	}
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
