#include "..\Include\base_allocator.h"

Block::Block(void* addr, size_t len)
	: address(addr), size(len)
{
}

Block::Block()
	: address(nullptr), size(0)
{
}

void Block::free()
{
	address = nullptr;
	size = 0;
}

Block::operator bool() const
{
	return(address != nullptr && size > 0);
}

BaseAllocator::BaseAllocator(size_t capacity = 16)
	: _capacity(capacity), _allocatedSize(), _numAllocations()
{
}

void BaseAllocator::reset()
{
	_capacity = 0;
	_allocatedSize = 0;
	_numAllocations = 0;
}

size_t BaseAllocator::getCapacity() const
{
	return(_capacity);
}

size_t BaseAllocator::getAllocatedSize() const
{
	return(_allocatedSize);
}

size_t BaseAllocator::getNumAllocations() const
{
	return(_numAllocations);
}

void BaseAllocator::_setCapacity(size_t capac)
{
	_capacity = capac;
}

void BaseAllocator::_addCapacity(size_t amount)
{
	_capacity += amount;
}

void BaseAllocator::_setAllocationSize(size_t size)
{
	_allocatedSize = size;
}

void BaseAllocator::_addAllocationSize(size_t amount)
{
	_allocatedSize += amount;
}

void BaseAllocator::_subAllocationSize(size_t amount)
{
	if (_allocatedSize - amount >= 0)
	{
		_allocatedSize -= amount;
	}
}

void BaseAllocator::_setNumAllocations(size_t num)
{
	_numAllocations = num;
}

void BaseAllocator::_incrementNumAllocations()
{
	_numAllocations++;
}

void BaseAllocator::_decrementNumAllocations()
{
	_numAllocations--;
}