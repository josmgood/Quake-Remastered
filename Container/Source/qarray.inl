#include "..\Include\qarray.hpp"

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
QArray<Type, TAllocator, TIterator>::QArray(size_t size)
	: QBaseContainer(size), QArray(size)
{
	Block* blocks = _allocator.allocate(size);
	size_t blockSize = blocks->size;
	for (size_t i = 0; i < size; i++)
	{
		_array = reinterpret_cast<Pointer>(blocks[i].address);
		_array++;
	}
}

template<typename Type, 
	typename TAllocator, 
	typename TIterator>
QArray<Type, TAllocator, TIterator>::~QArray()
{
	clear();
}

template<typename Type,
	typename TAllocator,
	typename TIterator>
void QArray<Type, TAllocator, TIterator>::clear()
{
	while (!isEmpty())
	{
		popBack();
	}
}

template<typename Type,
	typename TAllocator,
	typename TIterator>
void QArray<Type, TAllocator, TIterator>::swap(QArray& other)
{
	QArray<Type> tmp = other._array;
	size_t size = (other.getSize() > getSize()) ?
		other.getSize() : getSize();
	for (size_t i = 0; i < size; i++)
	{
		other._array[i] = _array[i];
		_array[i] = tmp._array[i];
	}
	other._setSize(getSize());
	other._setAllocator(tmp.getAllocator());

	_setSize(tmp.getSize());
	_setAllocator(tmp.getAllocator());
}

template<typename Type
	typename TAllocator,
	typename TIterator>
bool QArray<Type, TAllocator, TIterator>::has(ConstReference value)
{
	size_t size = _size;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] == value)
		{
			return(true);
		}
	}
	return(false);
}