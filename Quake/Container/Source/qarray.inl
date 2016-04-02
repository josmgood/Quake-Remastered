#include "..\Include\qarray.hpp"

template<typename Type,
	typename TAllocator>
const QArray<Type, TAllocator> QArray<Type, TAllocator>::EMPTY_ARRAY(0);

template<typename Type,
	typename TAllocator>
const Arr_Value<Type, TAllocator> QArray<Type, TAllocator>::EMPTY_VALUE = QArray<Type, TAllocator>::Value();

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::QArray(size_t maxSize)
	: _array(), _size(), _maxSize(maxSize), _allocator()
{
	_array = _allocator.allocate(sizeof(Index) * maxSize);
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::QArray(Iterator begin, Iterator end)
	: _array(), _size(), _maxSize(), _allocator()
{
	size_t distance = iterator_distance(end, begin);
	size_t size = distance - 1;
	_array = _allocator.allocate(sizeof(Index) * size);
	_maxSize = size;
	_size = size;
	std::memcpy(_array, begin.ptr(), size * sizeof(Index));
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::QArray(const C_Array& carray)
	: _array(), _size(carray.size), _maxSize(carray.max), _allocator()
{
	_array = _allocator.allocate(sizeof(Index) * _size);
	std::memcpy(_array, carray.arra, _size * sizeof(Index));
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>::QArray(const QArray& other)
	: _array(), _size(other._size), _maxSize(other._maxSize), _allocator()
{
	_array = _allocator.allocate(sizeof(Index) * _size);
	std::memcpy(_array, other._array, _size * sizeof(Index));
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::setFront(ConstReference reference)
{
	if (!isEmpty())
	{
		_array[0] = reference;
	}
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::setFront(const C_Array& carray)
{
	size_t size = carray.size;
	if (_size >= size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			Value value = carray.arra[i];
			carray.arra[i] = _array[i];
			_array[i] = value;
		}
	}
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::setFront(const QArray& other)
{
	size_t size = other._size;
	if (_size >= size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			Value value = other[i];
			other[i] = _array[i];
			_array[i] = value;
		}
	}
}

template<typename Type,
	typename TAllocator>
Arr_Reference<Type, TAllocator>
QArray<Type, TAllocator>::getFront() const
{
	return _array[0];
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>
QArray<Type, TAllocator>::subarray(size_t start) const
{
	if (_checkIndex(start))
	{
		size_t size = _size - start;
		QArray qarray(start);
		std::memcpy(qarray._array, _array + start, size);
		return qarray;
	}
	return EMPTY_ARRAY;
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>
QArray<Type, TAllocator>::subarray(size_t begin, size_t end) const
{
	if (_checkIndices(begin, end))
	{
		size_t size = end - begin;
		QArray qarray(size);
		std::memcpy(qarray._array, _array + begin, size);
		return qarray;
	}
	return EMPTY_ARRAY;
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>
QArray<Type, TAllocator>::subarray(const Iterator start) const
{
	if (_checkIterator(start))
	{
		Iterator end = getEnd();
		size_t distance = iterator_distance(end, start);
		size_t size = distance - 1;
		QArray qarray(size);
		std::memcpy(qarray._array, start.ptr(), size);
		return qarray;
	}
	return EMPTY_ARRAY;
}

template<typename Type,
	typename TAllocator>
QArray<Type, TAllocator>
QArray<Type, TAllocator>::subarray(const Iterator begin, const Iterator end) const
{
	if (_checkIterators(begin, end))
	{
		size_t distance = iterator_distance(end, begin);
		size_t size = distance - 1;
		QArray qarray(size);
		std::memcpy(qarray._array, begin.ptr(), size);
		return qarray;
	}
	return EMPTY_ARRAY;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::find(ConstReference reference, size_t buffer) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (i.get() == refrence && !buffer--)
		{
			return i;
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::find(const C_Array& carray, size_t buffer) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while(i < end)
	{
		if (carray[0] == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(carray, start, distance);
			if (comparison.isEqual && !buffer--)
			{
				return i;
			}
			if (_size - distance < carray.size)
			{
				break;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::find(const QArray& other, size_t buffer) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while (i < end)
	{
		if (other.getFront() == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(other._array, start, distance);
			if (comparison.isEqual && !buffer--)
			{
				return i;
			}
			if (_size - distance < other.getSize())
			{
				break;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::findLast(ConstReference reference) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	size_t found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (reference == i.get())
		{
			found = i;
		}
	}
	return found;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::findLast(const C_Array& carray) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator found = end;
	Iterator i = begin;
	while (i < end)
	{
		if (carray[0] == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(carray, start, distance);
			if (comparison.isEqual)
			{
				found = i;
			}
			else if (_size - distance < carray.size)
			{
				return found;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return found;
}

template<typename Type,
	typename TAllocator>
Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::findLast(const QArray& other) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator found = end;
	Iterator i = begin;
	while (i < end)
	{
		if (other.getFront() == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(other._array, start, distance);
			if (comparison.isEqual)
			{
				found = i;
			}
			else if (_size - distance < other.getSize())
			{
				return found;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return found;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::has(ConstReference reference) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (i.get() == reference)
		{
			return true;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::has(const C_Array& carray) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while (i < end)
	{
		if (carray[0] == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(carray.arra, start, distance);
			if (comparison.isEqual)
			{
				return true;
			}
			else if (_size - distance < carray.size)
			{
				return false;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::has(const QArray& other) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while (i < begin)
	{
		if (other.getFront() == i.get())
		{
			size_t distance = iterator_distance(i, begin);
			Array start = _array + distance;
			Comparison comparison = _compare(other._array, start, distance);
			if (comparison.isEqual)
			{
				return true;
			}
			else if (_size - distance < other.getSize())
			{
				return false;
			}
			else
			{
				i += comparison.traversed;
			}
		}
		else
		{
			++i;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
size_t QArray<Type, TAllocator>::occurances(ConstReference reference) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	size_t count = 0;
	for (Iterator i = begin; i < end; ++i)
	{
		if (reference == i.get())
		{
			count++;
		}
	}
	return count;
}

template<typename Type,
	typename TAllocator>
size_t QArray<Type, TAllocator>::occurances(const C_Array& carray) const
{

}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::isEmpty() const
{
	return _size == 0;
}

template<typename Type,
	typename TAllocator>::
QBool QArray<Type, TAllocator>::isFull() const
{
	return _size == _maxSize;
}

template<typename Type,
	typename TAllocator>
Arr_CArray<Type, TAllocator>
QArray<Type, TAllocator>::toCArray() const
{	
	C_Array carray;
	carray.size = _size;
	carray.max = _maxSize;
	carray.array = new Index[_maxSize];
	std::memcpy(carray.arra, _array, _size * sizeof(Index));
	return carray;
}

template<typename Type,
	typename TAllocator>
Arr_Reference<Type, TAllocator>
QArray<Type, TAllocator>::at(size_t index) const
{
	return _checkIndex(index) ? _array[index] : EMPTY_VALUE;
}

template<typename Type,
	typename TAllocator>
Arr_Reference<Type, TAllocator>
QArray<Type, TAllocator>::operator[](size_t index) const
{
	return at(index);
}

template<typename Type,
	typename TAllocator>
const Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::getBegin() const
{
	return Iterator(_array[0]);
}

template<typename Type,
	typename TAllocator>
const Arr_Iterator<Type, TAllocator>
QArray<Type, TAllocator>::getEnd() const
{
	return Iterator(_array[_size]);
}

template<typename Type,
	typename TAllocator>
const Arr_ConstIterator<Type, TAllocator>
QArray<Type, TAllocator>::getCBegin() const
{
	return ConstIterator(_array[0]);
}

template<typename Type,
	typename TAllocator>
const Arr_ConstIterator<Type, TAllocator>
QArray<Type, TAllocator>::getCEnd() const
{
	return ConstIterator(_array[_size]);
}

template<typename Type,
	typename TAllocator>
const Arr_ReverseIterator<Type, TAllocator>
QArray<Type, TAllocator>::getRBegin() const
{
	return ReverseIterator(_array[_size - 1]);
}

template<typename Type,
	typename TAllocator>
const Arr_ReverseIterator<Type, TAllocator>
QArray<Type, TAllocator>::getREnd() const
{
	return ReverseIterator(_array[-1]);
}

template<typename Type,
	typename TAllocator>
const Arr_ConstReverseIterator<Type, TAllocator>
QArray<Type, TAllocator>::getCRBegin() const
{
	return Arr_ConstReverseIterator(_array[_size - 1]);
}

template<typename Type,
	typename TAllocator>
const Arr_ConstReverseIterator<Type, TAllocator>
QArray<Type, TAllocator>::getCREnd() const
{
	return Arr_ConstReverseIterator(_array[-1]);
}

template<typename Type,
	typename TAllocator>
size_t QArray<Type, TAllocator>::getSize() const
{
	return _size;
}

template<typename Type,
	typename TAllocator>
size_t QArray<Type, TAllocator>::getMaxSize() const
{
	return _maxSize;
}

template<typename Type,
	typename TAllocator>
ALLOCATOR_ID QArray<Type, TAllocator>::getAllocator() const
{
	return _allocator.getID();
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::_setSize(size_t size)
{
	_size = size;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::_incrementSize()
{
	_size++;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::_decrementSize()
{
	_size--;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::_addSize(size_t amount)
{
	_size += amount;
}

template<typename Type,
	typename TAllocator>
void QArray<Type, TAllocator>::_subtractSize(size_t amount)
{
	_size -= amount;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_hasSpaceFor(size_t num) const
{
	return _size + num <= _maxSize;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkIndex(size_t index) const
{
	return index < _length && index >= 0;
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkIndices(size_t begin, size_t end) const
{
	return _checkIndex(begin) && end <= _length && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkIterator(const Iterator iterator) const
{
	return iterator >= getBegin() && iterator < getEnd();
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkIterators(const Iterator begin, const Iterator end) const
{
	return _checkIterator(begin) && end <= getEnd() && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkReverseIterator(const ReverseIterator iterator) const
{
	return iterator >= getRBegin() && iterator < getREnd();
}

template<typename Type,
	typename TAllocator>
QBool QArray<Type, TAllocator>::_checkReverseIterators(const ReverseIterator begin, const ReverseIterator end) const
{
	return _checkReverseIterator(begin) && end <= getREnd() && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
Comparison QArray<Type, TAllocator>::_compare(const Array A, const Array B, size_t size)
{
	const Array a1 = A;
	const Array a2 = B;
	size_t count = 0;
	while (size)
	{
		if (*a1 != *a2)
		{
			break;
		}

		a1++;
		c2++;
		size--;
	}
	return Comparison(count, size == 0);
}

template<typename Type,
	typename TAllocator>
	template<typename TIterator>
QBool QArray<Type, TAllocator>::_comesBefore(TIterator begin, TIterator end) const
{
	return begin <= end;
}

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream& os, const QArray<Type, TAllocator>& qarray)
{
	size_t count = 0;
	QArray<Type, TAllocator>::Iterator i = qarray.getBegin();
	for (; count < qarray._size; ++i, ++count)
	{
		os << "Index " << count << ": " << i.get() << std::endl;
	}
	return os;
}