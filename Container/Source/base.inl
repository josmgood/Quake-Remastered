#include "..\Include\base.hpp"

template<typename Type,
	typename TAllocator>
QAuxiliary<Type, TAllocator>::QAuxiliary(size_t maxSize)
	: _allocator(sizeof(Type) * maxSize), _size(), _maxSize(maxSize)
{
}

template<typename Type,
	typename TAllocator>
bool QAuxiliary<Type, TAllocator>::isEmpty() const
{
	return !_size;
}

template<typename Type,
	typename TAllocator>
bool QAuxiliary<Type, TAllocator>::isFull() const
{
	return _size == _maxSize;
}

template<typename Type,
	typename TAllocator>
size_t QAuxiliary<Type, TAllocator>::getSize() const
{
	return _size;
}

template<typename Type,
	typename TAllocator>
size_t QAuxiliary<Type, TAllocator>::getMaxSize() const
{
	return _maxSize;
}

template<typename Type,
	typename TAllocator>
void QAuxiliary<Type, TAllocator>::_incrementSize()
{
	_size++;
}

template<typename Type,
	typename TAllocator>
void QAuxiliary<Type, TAllocator>::_decrementSize()
{
	_size--;
}