#include "..\Include\qstack.hpp"

template<typename Type, typename TAllocator, typename TIterator>
QStack<Type, TAllocator, TIterator>::QStack(size_t size, Value initial)
	: QBaseContainer(size), Stackable()
{
	Block* blocks = _allocator.allocate(size);
	size_t blockSize = blocks->size;
	for (size_t i = 0; i < size; i++)
	{
		_stack = reinterpret_cast<Pointer>(blocks[i].address);
		_stack++;
	}
	/*_begin = ArrayIterator<Type>(_stack);
	_end = ArrayIterator<Type>(&_stack[_size]);*/
}

template<typename Type, typename TAllocator, typename TIterator>
QStack<Type, TAllocator, TIterator>::~QStack()
{
	clear();
}

template<typename Type, typename TAllocator, typename TIterator>
const typename QStack<Type, TAllocator, TIterator>::ConstReference
QStack<Type, TAllocator, TIterator>::getTop() const
{
	return(_stack[_size]);
}

template<typename Type, typename TAllocator, typename TIterator>
void QStack<Type, TAllocator, TIterator>::push(ConstReference value)
{
	size_t newTop = _size + 1;
	size_t numBlocks = _allocator.getNumBlocks();
	if (newTop > numBlocks)
	{
		_allocator.expand(4);
		resize(numBlocks + 4);
	}
	bool isSpace = (_allocator.getNumBlocks() - _size > 0);
	if (isSpace)
	{
		Pointer ptr = reinterpret_cast<Pointer>(_allocator.allocate()->address);
		*ptr = value;
		_stack[newTop] = *ptr;
		_incrementSize();
	}
}

template<typename Type, typename TAllocator, typename TIterator>
void QStack<Type, TAllocator, TIterator>::pop()
{
	size_t top = _size;
	if (_stack[top])
	{
		void* address = reinterpret_cast<void*>(_stack[top]);
		size_t size = sizeof(Type);
		Block block(address, size);
		_stack[top] = Value();
		_allocator.deallocate(&block);
		_decrementSize();
	}
}

template<typename Type, typename TAllocator, typename TIterator>
void QStack<Type, TAllocator, TIterator>::resize(size_t amount)
{
	size_t newSize = _size + amount;
	Pointer newStack = new Value[newSize];
	size_t oldSize = _size;
	size_t reser = _allocator.getCapacity();
	size_t dataSize = sizeof(Type);
	if (reser < (newSize * dataSize))
	{
		reser += newSize - reser;
		reserve(reser);
	}
	for (size_t i = 0; i < oldSize; i++)
	{
		newStack[i] = _stack[i];
	}
	_setSize(newSize);
	_setStack(newStack);
}

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
void QStack<Type, TAllocator, TIterator>::reserve(size_t amount)
{
	_allocator.expand(amount);
}

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
void QStack<Type, TAllocator, TIterator>::clear()
{
	while (!isEmpty())
	{
		pop();
	}
}

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
void QStack<Type, TAllocator, TIterator>::swap(QStack& other)
{
	QStack<Type> tmp = other;
	size_t size = (other.getSize() > getSize()) 
		? other.getSize() : getSize();
	for (size_t i = 0; i < size; i++)
	{
		other._stack[i] = _stack[i];
		_stack[i] = tmp._stack[i];
	}
	other._size = getSize();
	other._allocator = _allocator;

	_size = tmp.getSize();
	_allocator = tmp.getAllocator();
}

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
bool QStack<Type, TAllocator, TIterator>::has(ConstReference value)
{
	return false;
}