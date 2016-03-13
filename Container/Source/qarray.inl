#include "..\Include\qarray.hpp"

//template<typename Type, 
//	typename TAllocator, 
//	typename TIterator>
//QArray<Type, TAllocator, TIterator>::QArray(size_t size)
//	: QBaseContainer(size), QArray(size)
//{
//	Block* blocks = _allocator.allocate(size);
//	size_t blockSize = blocks->size;
//	for (size_t i = 0; i < size; i++)
//	{
//		_array = reinterpret_cast<Pointer>(blocks[i].address);
//		_array++;
//	}
//}
//
//template<typename Type, 
//	typename TAllocator, 
//	typename TIterator>
//QArray<Type, TAllocator, TIterator>::~QArray()
//{
//	clear();
//}
//
//template<typename Type,
//	typename TAllocator,
//	typename TIterator>
//void QArray<Type, TAllocator, TIterator>::clear()
//{
//	while (!isEmpty())
//	{
//		popBack();
//	}
//}
//
//template<typename Type,
//	typename TAllocator,
//	typename TIterator>
//void QArray<Type, TAllocator, TIterator>::swap(QArray& other)
//{
//	QArray<Type> tmp = other._array;
//	size_t size = (other.getSize() > getSize()) ?
//		other.getSize() : getSize();
//	for (size_t i = 0; i < size; i++)
//	{
//		other._array[i] = _array[i];
//		_array[i] = tmp._array[i];
//	}
//	other._setSize(getSize());
//	other._setAllocator(tmp.getAllocator());
//
//	_setSize(tmp.getSize());
//	_setAllocator(tmp.getAllocator());
//}
//
//template<typename Type
//	typename TAllocator,
//	typename TIterator>
//bool QArray<Type, TAllocator, TIterator>::has(ConstReference value)
//{
//	size_t size = _size;
//	for (size_t i = 0; i < size; i++)
//	{
//		if (_array[i] == value)
//		{
//			return(true);
//		}
//	}
//	return(false);
//}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::QArray(size_t maxSize, ConstReference initial)
	: QAuxiliary(maxSize), _array(new Node[maxSize]), _back()
{
	for (size_t i = 0; i < _maxSize; i++)
	{
		_array[i] = initial;
	}
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::~QArray()
{
	delete[] _array;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::pushFront(ConstReference value)
{
	Node front = _array[0];
	_array[0] = value;
	for (size_t i = 1; i < _back; i++)
	{
		Node tmp = _array[i];
		_array[i] = front;
		front = _array[i];
	}
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::pushBack(ConstReference value)
{
	if (!isFull())
	{
		_array[_back] = value;
		_back++;
		_incrementSize();
	}
}

template<typename Type,
	typename TAllocator>
const Type& QArray<Type, TAllocator>::getFront() const
{
	return _array[0];
}

template<typename Type,
	typename TAllocator>
const Type& QArray<Type, TAllocator>::getBack() const
{
	/*_back holds the value directly after the back*/
	return _array[_back];
}

template<typename Type,
	typename TAllocator>
bool QArray<Type, TAllocator>::owns(ConstReference value)
{
	for (size_t i = 0; i < _back; i++)
	{
		if (_array[i] == value)
		{
			return true;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::clear(size_t index)
{
	_array[index] = 0;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::clear()
{
	for (size_t i = 0; i < _back; i++)
	{
		_array[i] = Value();
	}
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::swap(QArray& other)
{
	size_t size = (_maxSize > other._maxSize) ? _maxSize : other._maxSize;
	Array tmp = new Node[size];
	for (size_t i = 0; i < size; i++)
	{
		//tmp[i] = other[i];

	}
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::pack()
{
	for (size_t i = 0; i < _back; i++)
	{
	}
}

template<typename Type,
	typename TAllocator>
Type& QArray<Type, TAllocator>::operator[](size_t index) const
{
	return _array[index];
}

template<typename Type,
	typename TAllocator>
Type& QArray<Type, TAllocator>::at(size_t index) const
{
	retunr _array[index];
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::set(size_t index, ConstReference value)
{
	_array[index] = value;
	if (index > _back)
	{
		_back = index;
	}
}

template<typename Type,
	typename TAllocator>
std::ostream& QArray<Type, TAllocator>::operator<<(std::ostream& os)
{
	
}