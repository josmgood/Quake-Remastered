#include "..\Include\qstring.hpp"

//QBool isSensitive(Sensitivity sensitivity)
//{
//	return sensitivity == STR_SENSITIVE;
//}
//
//QBool isInsensitive(Sensitivity sensitivity)
//{
//	return sensitivity == STR_INSENSITIVE;
//}

template<typename Type,
	typename TAllocator>
const Basic_QString<Type, TAllocator> Basic_QString<Type, TAllocator>::EMPTY_STRING(nullptr);

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Comparison::Comparison(size_t trav, QBool equal)
	: traversed(trav), isEqual(equal)
{
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Basic_QString(size_t length)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	//_string = _allocator.allocate(sizeof(Character) * length);
	if (length != 0)
	{
		size_t zeroLen = length + 1;
		_maxLength = zeroLen;
		_length = 1;
		Block block = _allocator.allocate(sizeof(Character) * zeroLen);
		_string = static_cast<String>(block.memory);
		_string[0] = '\0';
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Basic_QString(const String string)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	if (string)
	{
		size_t otherLen = strlen(string);
		QBool hasTZero = *(string + otherLen - 1) == '\0';
		size_t len = hasTZero ? otherLen : otherLen + 1;
		_maxLength = len;
		_length = len;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		strncpy_s(_string, len, string, otherLen);
		if (!hasTZero)
		{
			_string[len - 1] = '\0';
		}
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Basic_QString(const Index begin, const Index end)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	if (_comesBefore(begin, end))
	{
		QBool hasTZero = *end == '\0';
		size_t len = hasTZero ? end - begin : end - begin + 1;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		_length = len;
		_maxLength = len;
		strncpy_s(_string, len, begin, len - 1);
		if (!hasTZero)
		{
			_string[len - 1] = '\0';
		}
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Basic_QString(const Iterator begin, const Iterator end)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	if (_comesBefore(begin, end))
	{
		const Character* string = begin.ptr();
		size_t otherLen = strlen(string);
		QBool hasTZero = *end == '\0';
		size_t len = hasTZero ? otherLen : otherLen + 1;
		_maxLength = len;
		_length = len;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		strncpy_s(_string, len, string, otherLen);
		if (!hasTZero)
		{
			_string[len - 1] = '\0';
		}
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::Basic_QString(const Basic_QString& string)
	: _string(nullptr), _allocator(), _maxLength(string._maxLength), _length(string._length)
{
	if (string)
	{
		size_t len = string._length;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		const String str = string._string;
		strncpy_s(_string, _length, str, len);
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::~Basic_QString()
{
	if (_string)
	{
		Block block(_string, _maxLength);
		_allocator.deallocate(block);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushFront(Character ch)
{
	if (!_hasSpaceFor(1))
	{
		reserve(_maxLength + 3);
	}
	Character last = _string[0];
	_string[0] = ch;
	size_t end = _length + 1;
	for (size_t i = 1; i < end; ++i)
	{
		Character hold = _string[i];
		_string[i] = last;
		last = hold;
	}
	_incrementLength();
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushFront(const Character* string)
{
	size_t len = strlen(string);
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	Character last = _string[0];
	_string[0] = string[0];
	size_t end = _length + len;
	for (size_t i = 1; i < end; ++i)
	{
		//Character hold = _string[i];
		//Character hold2 = _string[i + 1];
		//_string[i] = last;
		//last = hold;
		///*if (i < len)
		//{
		//	_string[i] = string[i];
		//}*/
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushFront(const Basic_QString& string)
{
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::setFront(Character ch)
{
	if (_length > 1)
	{
		_string[0] = ch;
	}
}

template<typename Type,
	typename TAllocator>
Str_Reference<Type, TAllocator>
Basic_QString<Type, TAllocator>::getFront() const
{
	return _string[0];
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushBack(Character ch)
{
	if (!_hasSpaceFor(1))
	{
		reserve(_maxLength + 2);
	}
	_string[_length - 1] = ch;
	_setTerminatingZero(_length);
	_incrementLength();
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushBack(const Character* string)
{
	size_t len = strlen(string);
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	for (size_t i = _length - 1, j = 0; i < _maxLength && j < len; ++i, ++j)
	{
		Character ch = string[j];
		_string[i] = ch;
	}
	_addLength(len);
	if (string[len] == '\0')
	{
		_setTerminatingZero(_length - 1);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::pushBack(const Basic_QString& string)
{
	size_t len = string._length - 1;
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	for (size_t i = _length - 1, j = 0; i < _maxLength && j < len; ++i, ++j)
	{
		Character ch = string[j];
		_string[i] = ch;
	}
	_addLength(len);
	if (string[len] == '\0')
	{
		_setTerminatingZero(_length - 1);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::setBack(Character ch)
{
	if (_length - 2 >= 0)
	{
		_string[_length - 2] = ch;
	}
}

template<typename Type,
	typename TAllocator>
Str_Reference<Type, TAllocator>
Basic_QString<Type, TAllocator>::getBack() const
{
	return _string[_length - 2];
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::concat(const Character* string)
{
	size_t len = strlen(string);
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	strncat_s(_string, _maxLength, string, len);
	_addLength(len);
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::concat(const Basic_QString& string)
{
	size_t len = string._length - 1;
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	strncat_s(_string, _maxLength, string._string, len);
	_addLength(len);
}

//void Basic_QString::insert(size_t index, Character ch)
//{
//	if (_checkIndex(index))
//	{
//		if (!_hasSpaceFor(1))
//		{
//			reserve(_maxLength + 5);
//		}
//		for (size_t i = index; i < _length; ++i)
//		{
//			Character hold = _string[i];
//			Character next = _string[i + 1];
//			_string[i + 1] = hold;
//		}
//		_string[index] = ch;
//		_incrementLength();
//		_adjustEnd(1);
//	}
//}
//
//void Basic_QString::insert(size_t begin, size_t end, const Character* string)
//{
//	if (_checkIndicies(begin, end) || _checkIndex(begin) && _comesBefore(begin, end))
//	{
//		size_t spaceNeeded = end - begin;
//		if (!_hasSpaceFor(spaceNeeded))
//		{
//			reserve(spaceNeeded);
//		}
//		size_t trueEnd = end + 1;
//		Character hold = _string[0];
//		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
//		{
//			Character hold = _string[i];
//			Character next = _string[i + 1];
//			_string[i + 1] = hold;
//			hold = next;
//
//			Character ch = string[j];
//			_string[i] = ch;
//		}
//		size_t newLen = _length + spaceNeeded;
//		_setLength(newLen);
//		_adjustEnd(newLen);
//	}
//}
//
//void Basic_QString::insert(size_t begin, size_t end, const Basic_QString& string)
//{
//	//if (_checkNegativeIndicies(begin, end) || _checkIndex(begin) && _comesBefore(begin, end))
//	//{
//	//	size_t spaceNeeded = end - begin;
//	//	if (!_hasSpaceFor(spaceNeeded))
//	//	{
//	//		reserve(_maxLength + spaceNeeded);
//	//	}
//	//	size_t trueEnd = end + 1;
//	//	for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
//	//	{
//	//		Character hold = _string[i];
//	//		Character next = _string[i + 1];
//	//		_string[i + 1] = hold;
//
//	//		Character ch = string[j];
//	//		_string[i] = ch;
//	//	}
//	//	_setLength(_length + spaceNeeded);
//	//	//_adjustEnd(spaceNeeded);
//	//}
//}
//
//void Basic_QString::insert(Iterator iterator, Character ch)
//{
//	/*if (_checkIterator(iterator))
//	{
//		if (!_hasSpaceFor(1))
//		{
//			reserve(_maxLength + 5);
//		}
//		for (Iterator i = _begin; i < _end; ++i)
//		{
//			Iterator hold = i;
//			Iterator next = i.next();
//			i.next() = hold;
//		}
//		iterator.set(ch);
//		_incrementLength();
//		_adjustEnd(1);
//	}*/
//}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(size_t index, Character ch)
{
	if (_checkIndex(index))
	{
		_string[index] = ch;
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(size_t begin, size_t end, const Character* string)
{
	if (_checkIndicies(begin, end))
	{
		size_t distance = end - begin;
		size_t len = strlen(string);
		size_t buffer = distance > len ? len : distance;
		for (size_t i = begin, j = 0; i < end && j < buffer; ++i, ++j)
		{
			Character ch = string[j];
			_string[i] = ch;
		}
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(size_t begin, size_t end, const Basic_QString& string)
{
	if (_checkIndicies(begin, end))
	{
		size_t distance = end - begin;
		size_t len = string._length - 1;
		size_t buffer = distance > len ? len : distance;
		for (size_t i = begin, j = 0; i < end && j < buffer; ++i, ++j)
		{
			Character ch = string[j];
			_string[i] = ch;
		}
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(Iterator iterator, Character ch)
{
	if (_checkIterator(iterator))
	{
		iterator.set(ch);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(Iterator begin, Iterator end, const Character* string)
{
	if (_checkIterators(begin, end))
	{
		size_t distance = iterator_distance(end, begin);
		size_t len = strlen(string);
		size_t buffer = distance > len ? len : distance;
		size_t j = 0;
		for (Iterator i = begin; i < end; ++i, ++j)
		{
			Character ch = string[j];
			i.set(ch);
		}
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::set(Iterator begin, Iterator end, const Basic_QString& string)
{
	if (_checkIterators(begin, end))
	{
		size_t distance = iterator_distance(end, begin);
		size_t len = string._length - 1;
		size_t buffer = distance > len ? len : distance;
		size_t j = 0;
		for (Iterator i = begin; i < end; ++i, ++j)
		{
			Character ch = string[j];
			i.set(ch);
		}
	}
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>
Basic_QString<Type, TAllocator>::substring(size_t index) const
{
	if (_checkIndex(index))
	{
		size_t len = _length - index - 1;
		Character* start = _string + index;
		return Basic_QString(start);
	}
	return EMPTY_STRING;
}

template<typename Type, 
	typename TAllocator>
Basic_QString<Type, TAllocator>
Basic_QString<Type, TAllocator>::substring(size_t begin, size_t end) const
{
	if (_checkIndicies(begin, end))
	{
		size_t distance = end - begin;
		Character* start = _string + begin;
		Character* stop = _string + begin + distance - 1;
		return Basic_QString(start, stop);
	}
	return EMPTY_STRING;
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>
Basic_QString<Type, TAllocator>::substring(const Iterator iterator) const
{
	if (_checkIterator(iterator))
	{
		return Basic_QString(iterator.ptr());
	}
	return EMPTY_STRING;
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>
Basic_QString<Type, TAllocator>::substring(const Iterator begin, const Iterator end) const
{
	if (_checkIterators(begin, end))
	{
		return Basic_QString(begin, end);
	}
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::find(Character ch, size_t buffer, Sensitivity sensitivity) const
{
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(ch, i.get()) && !--buffer)
		{
			return i;
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::find(const Character* string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = strlen(string);
	CharChecker charCheck = _getCharChecker(sensitivity);
	StrChecker strCheck = _getStrChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			if (!strCheck(start, string, len) && !--buffer)
			{
				return i;
			}
			else
			{
				i += len;
			}
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::find(const Basic_QString& string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = string._length - 1;
	CharChecker charCheck = _getCharChecker(sensitivity);
	StrChecker strCheck = _getStrChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			if (!strCheck(start, string._string, len) && !--buffer)
			{
				return i;
			}
			else
			{
				i += len;
			}
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Str_ReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::rfind(Character ch, Sensitivity sensitivity) const
{
	CharChecker charCheck = _getCharChecker(sensitivity);
	ReverseIterator begin = getRBegin();
	ReverseIterator end = getREnd();
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (charCheck(ch, i.get()))
		{
			return i;
		}
	}
	return end;
}

template<typename Type,
	typename TAllocator>
Str_ReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::rfind(const String string, Sensitivity sensitivity) const
{
	/*size_t len = strlen(string);
	std::cout << "LENGTH: " << len << std::endl;
	CharChecker charCheck = _getCharChecker(sensitivity);
	StrChecker strCheck = _getStrChecker(sensitivity);
	ReverseIterator begin = getRBegin();
	ReverseIterator end = getREnd();
	ReverseIterator i = begin;
	while (i < end)
	{
		if (charCheck(string[len - 1], i.get()))
		{
			size_t distance = iterator_distance(i, end - 2);
			const String start = _string + distance;
			const String other = string;
			std::cout << start << std::endl;
			Comparison comparison = _compare(start, other, len + 1, charCheck);
			if (comparison.isEqual)
			{
				return i;
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
	}*/
	//return end;
	return getREnd();
}

template<typename Type,
	typename TAllocator>
Str_ReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::rfind(const Basic_QString& string, Sensitivity sensitivity) const
{
	/*size_t len = string._length - 1;
	CharChecker charCheck = _getCharChecker(sensitivity);
	StrChecker strCheck = _getStrChecker(sensitivity);
	ReverseIterator begin = getRBegin();
	ReverseIterator end = getREnd();
	ReverseIterator i = begin;
	while (i < end)
	{
		if (charCheck(string[len - 1], i.get()))
		{
			size_t distance = iterator_distance(i, end);
			String start = _string + distance;
			Comparison comparison = _compare(start, string._string, len, charCheck);
			if (comparison.isEqual)
			{
				return i;
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
	}*/
	/*for (ReverseIterator i = 0; i < end; ++i)
	{
		if (charCheck(string[len - 1], i.get()))
		{
			size_t distance = iterator_distance(i, end) - len;
			String start = _string + distance;
			if (!strCheck(start, string, len))
			{
				return i;
			}
			else
			{
				i += len;
			}
		}
	}
	return end;*/
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::findLast(Character ch, Sensitivity sensitivity) const
{
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(ch, i.get()))
		{
			found = i;
		}
	}
	return found;
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::findLast(const Character* string, Sensitivity sensitivity) const
{
	size_t len = strlen(string);
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator found = end;
	Iterator i = begin;
	size_t count = 0;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Iterator possible = i;
			Comparison comparison = _compare(start, string, len, charCheck);
			size_t traversed = comparison.traversed;
			i = iterator_traverse(i, traversed);
			count += traversed;
			if (comparison.isEqual)
			{
				found = possible;
				int32 indicesLeft = _length - count - 1;
				if (indicesLeft < len)
				{
					return found;
				}
			}
		}
		else
		{
			++i;
			++count;
		}
	}
	return found;
}

template<typename Type,
	typename TAllocator>
Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::findLast(const Basic_QString& string, Sensitivity sensitivity) const
{
	size_t len = string._length - 1;
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator found = end;
	Iterator i = begin;
	size_t count = 0;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Character* other = string._string;
			Iterator possible = i;
			Comparison comparison = _compare(start, other, len, charCheck);
			size_t traversed = comparison.traversed;
			i = iterator_traverse(i, traversed);
			count += traversed;
			if (comparison.isEqual)
			{
				found = possible;
				int32 indicesLeft = _length - count - 1;
				if (indicesLeft < len)
				{
					return found;
				}
			}
		}
		else
		{
			++i;
			++count;
		}
	}
	return found;
}

template<typename Type, 
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::has(Character ch, Sensitivity sensitivity) const
{
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(ch, i.get()))
		{
			return true;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::has(const Character* string, Sensitivity sensitivity) const
{
	size_t len = strlen(string);
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Comparison comparison = _compare(start, string, len, charCheck);
			if (comparison.isEqual)
			{
				return true;
			}
			else
			{
				i = iterator_traverse(i, comparison.traversed);
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
QBool Basic_QString<Type, TAllocator>::has(const Basic_QString& string, Sensitivity sensitivity) const
{
	size_t len = string._length - 1;
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Character* other = string._string;
			Comparison comparison = _compare(start, other, len, charCheck);
			if (comparison.isEqual)
			{
				return true;
			}
			else
			{
				i = iterator_traverse(i, comparison.traversed);
			}
		}
		else
		{
			++i;
		}
	}
	return false;
}

////QBool Basic_QString::rhas(Character ch, Sensitivity sensitivity) const
////{
////	CharChecker charCheck = _getCharChecker(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (charCheck(ch, i.get()))
////		{
////			return true;
////		}
////	}
////	return false;
////}
////
////QBool Basic_QString::rhas(const Character* string, Sensitivity sensitivity) const
////{
////	size_t len = Q_strLen(string);
////	CharChecker charCheck = _getCharChecker(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (charCheck(string[len - 1], i.get()))
////		{
////			++i;
////			for (size_t j = len - 2; charCheck(string[j], i.get()); --j, ++i)
////			{
////				if (charCheck(string[j], i.get()) && j == 0)
////				{
////					return true;
////				}
////			}
////		}
////	}
////
////	return false;
////}
////
////QBool Basic_QString::rhas(const Basic_QString& string, Sensitivity sensitivity) const
////{
////	size_t len = string.getLength();
////	CharChecker charCheck = _getCharChecker(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (charCheck(string[len - 1], i.get()))
////		{
////			++i;
////			for (size_t j = len - 2; charCheck(string[j], i.get()); --j, ++i)
////			{
////				if (charCheck(string[j], i.get()) && j == 0)
////				{
////					return true;
////				}
////			}
////		}
////	}
////	return false;
////}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::occurances(Character ch, Sensitivity sensitivity) const
{
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	size_t occurances = 0;
	for (Iterator i = begin; i < end; ++i)
	{
		if (charCheck(ch, i.get()))
		{
			++occurances;
		}
	}
	return occurances;
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::occurances(const Character* string, Sensitivity sensitivity) const
{
	size_t len = strlen(string);
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	size_t occurances = 0;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Comparison comparison = _compare(start, string, len, charCheck);
			i = iterator_traverse(i, comparison.traversed);
			if (comparison.isEqual)
			{
				occurances++;
			}
		}
		else
		{
			++i;
		}
	}
	return occurances;
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::occurances(const Basic_QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CharChecker charCheck = _getCharChecker(sensitivity);
	Iterator begin = getBegin();
	Iterator end = getEnd();
	Iterator i = begin;
	size_t occurances = 0;
	while (i < end)
	{
		if (charCheck(string[0], i.get()))
		{
			size_t distance = iterator_distance(i, begin);
			Character* start = _string + distance;
			Character* other = string._string;
			Comparison comparison = _compare(start, other, len, charCheck);
			i = iterator_traverse(i, comparison.traversed);
			if (comparison.isEqual)
			{
				occurances++;
			}
		}
		else
		{
			++i;
		}
	}
	return occurances;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::is(CharacterFilter filter, CharacterFilter exception) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		Character ch = i.get();
		QBool match = filter(ch);
		QBool except = exception ? exception(ch) : false;
		if (filterNotMatch(match) && exceptionNotApply(except))
		{
			return false;
		}
	}
	return true;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::is(size_t index, CharacterFilter filter, CharacterFilter exception) const
{
	return _checkIndex(index) ? filter(_string[index]) || (exception && exception(_string[index])) : false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkIndicies(begin, end))
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin; i < trueEnd; ++i)
		{
			Character ch = _string[i];
			QBool match = filter(ch);
			QBool except = exception ? exception(ch) : false;
			if (filterNotMatch(match) && exceptionNotApply(except))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::is(const Iterator iterator, CharacterFilter filter, CharacterFilter exception) const
{
	return _checkIterator(iterator) ? filter(iterator.get()) || (exception && exception(iterator.get())) : false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::is(Iterator begin, Iterator end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkIterators(begin, end))
	{
		Iterator trueEnd = end + 1;
		for (Iterator i = begin; i < trueEnd; ++i)
		{
			Character ch = i.get();
			QBool match = filter(ch);
			QBool except = exception ? exception(ch) : false;
			if (filterNotMatch(match) && exceptionNotApply(except))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

////QBool Basic_QString::ris(size_t index, CharacterFilter filter, CharacterFilter exception) const
////{
////	if (_checkNegativeIndex(index))
////	{
////		size_t pos = _negToPos(index);
////		return filter(_string[pos]) || exception(_string[pos]);
////	}
////	return false;
////}
////
////QBool Basic_QString::ris(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
////{
////	if (_checkNegativeIndicies(begin, end))
////	{
////		size_t posBeg = _negToPos(begin);
////		size_t posEnd = _negToPos(end);
////		for (size_t i = posBeg; i < posEnd; ++i)
////		{
////			if (!filter(_string[i]) && !exception(_string[i]))
////			{
////				return false;
////			}
////		}
////		return true;
////	}
////	return false;
////}
//
//QBool Basic_QString::ris(ReverseIterator iterator, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkReverseIterator(iterator) ? filter(iterator.get()) || exception(iterator.get()) : false;
//}
//
//QBool Basic_QString::ris(ReverseIterator begin, ReverseIterator end, CharacterFilter filter, CharacterFilter exception) const
//{
//	if (_checkReverseIterators(begin, end))
//	{
//		ReverseIterator trueEnd = end + 1;
//		for (ReverseIterator i = begin; i < trueEnd; ++i)
//		{
//			if (!filter(i.get()) || !exception(i.get()))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::to(CharacterConverter converter)
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		Character ch = i.get();
		ch = converter(ch);
		i.set(ch);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::to(size_t index, CharacterConverter converter)
{
	if (_checkIndex(index))
	{
		Character ch = _string[index];
		ch = converter(ch);
		_string[index] = ch;
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::to(size_t begin, size_t end, CharacterConverter converter)
{
	if (_checkIndicies(begin, end))
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin; i < trueEnd; ++i)
		{
			Character ch = _string[i];
			ch = converter(ch);
			_string[i] = ch;
		}
	}
}

//void Basic_QString::to(Iterator iterator, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkIterator(iterator))
//	{
//		Character ch = iterator.get();
//		if (!filter(ch))
//		{
//			ch = converter(ch);
//			iterator.set(ch);
//		}
//	}
//}
//
//void Basic_QString::to(Iterator begin, Iterator end, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkIterators(begin, end))
//	{
//		Iterator trueEnd = end + 1;
//		for (Iterator i = begin; i < trueEnd; ++i)
//		{
//			Character ch = i.get();
//			if (!filter(ch))
//			{
//				ch = converter(ch);
//				i.set(ch);
//			}
//		}
//	}
//}

//void Basic_QString::rto(size_t index, CharacterConverter converter, CharacterFilter filter)
//{
//	/*if (_checkNegativeIndex(index))
//	{
//		size_t i = _negToPos(index);
//		Character ch = _string[i];
//		if (!filter(ch))
//		{
//			_string[i] = converter(ch);
//		}
//	}*/
//}

////void Basic_QString::rto(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
////{
////	if (_checkNegativeIndicies(begin, end))
////	{
////		size_t posBeg = _negToPos(begin);
////		size_t trueEnd = _negToPos(end) + 1;
////		for (size_t i = posBeg; i < trueEnd; ++i)
////		{
////			Character ch = _string[i];
////			if (!filter(ch))
////			{
////				_string[i] = converter(ch);
////			}
////		}
////	}
////}
//
//void Basic_QString::rto(ReverseIterator iterator, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkReverseIterator(iterator))
//	{
//		Character ch = iterator.get();
//		if (!filter(ch))
//		{
//			ch = converter(ch);
//			iterator.set(ch);
//		}
//	}
//}
//
//void Basic_QString::rto(ReverseIterator begin, ReverseIterator end, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkReverseIterators(begin, end))
//	{
//		ReverseIterator trueEnd = end + 1;
//		for (ReverseIterator i = begin; i < trueEnd; ++i)
//		{
//			Character ch = i.get();
//			if (!filter(ch))
//			{
//				ch = converter(ch);
//				i.set(ch);
//			}
//		}
//	}
//}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::copy(const String string)
{
	size_t max = strlen(string) + 1;
	if (_maxLength < max)
	{
		reserve(max);
	}
	strncpy_s(_string, max, string, max);
	_setLength(max);
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::copy(const Basic_QString& string)
{
	size_t max = string._maxLength;
	if (_maxLength < max)
	{
		reserve(max);
	}
	strncpy_s(_string, max, string._string, max);
	_setLength(string._length);
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::swap(String string)
{
	/*size_t otherLen = strlen(string);
	QBool hasTZero = string[otherLen] == '\0';
	size_t len = _length - 1;
	size_t buffer = len > otherLen ? otherLen : len;

	Index c1 = _string;
	Index c2 = string;
	while (buffer--)
	{
	Character ch = *c1;
	*c1 = *c2;
	*c2 = ch;

	++c1;
	++c2;
	}*/
	/*if (len > buffer)
	{
	if (!hasTZero)
	{
	_setTerminatingZero(buffer);
	}
	for (size_t i = buffer + 1; i < len; ++i)
	{
	_string[i] = ' ';
	}
	}
	else if (otherLen > buffer)
	{
	string[buffer] = '\0';
	for (size_t i = buffer + 1; i < otherLen; ++i)
	{
	string[i] = ' ';
	}
	}*/
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::reserve(size_t size)
{
	if (size > _maxLength)
	{
		Block alloc = _allocator.allocate(size);
		String string = static_cast<String>(alloc.memory);
		strncpy_s(string, size, _string, _maxLength);
		
		Block dealloc(_string, _maxLength);
		_allocator.deallocate(dealloc);
		_string = string;
		_setMaxLength(size);
	}
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::clear()
{
	Block block(_string, _maxLength);
	_allocator.deallocate(block);
	_length = 0;
	_maxLength = 0;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::equals(const String other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return !strncmp(_string, other, len);
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::equals(const Basic_QString& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return !strncmp(_string, other._string, len);
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::isEmpty() const
{
	return _length == 0;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::isFull() const
{
	return _length == _maxLength;
}

template<typename Type,
	typename TAllocator>
int32 Basic_QString<Type, TAllocator>::toInt32() const
{
	return atoi(_string);
}

template<typename Type,
	typename TAllocator>
float64 Basic_QString<Type, TAllocator>::toFloat64() const
{
	return atof(_string);
}

template<typename Type,
	typename TAllocator>
const Str_String<Type, TAllocator>
Basic_QString<Type, TAllocator>::toCString() const
{
	return _string;
}

template<typename Type,
	typename TAllocator>
Str_Reference<Type, TAllocator> 
Basic_QString<Type, TAllocator>::at(size_t index) const
{
	return _checkIndex(index) ? _string[index] : EMPTY_CHAR;
}

template<typename Type,
	typename TAllocator>
Str_Reference<Type, TAllocator>
Basic_QString<Type, TAllocator>::operator[](size_t index) const
{
	return at(index);
}

template<typename Type,
	typename TAllocator>
Basic_QString<Type, TAllocator>::operator bool() const
{
	return _string && _length && _maxLength;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator==(const Character* other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return QBool(!strncmp(_string, other, len));
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator!=(const Character* other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return QBool(strncmp(_string, other, len));
	}
	return true;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator<(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	return strncmp(_string, other, len) == -1;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator<=(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	int32 result = strncmp(_string, other, len);
	return result == -1 || result == 0;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator>(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	return strncmp(_string, other, len) == 1;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator>=(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	int32 result = strncmp(_string, other, len);
	return result == 1 || result == 0;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator==(const Basic_QString& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return QBool(!strncmp(_string, other._string, len));
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator!=(const Basic_QString& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return QBool(strncmp(_string, other._string, len));
	}
	return true;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator<(const Basic_QString& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	return strncmp(_string, other._string, len) == -1;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator<=(const Basic_QString& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	int32 result = strncmp(_string, other._string, len);
	return result == -1 || result == 0;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator>(const Basic_QString& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	return strncmp(_string, other._string, len) == 1;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::operator>=(const Basic_QString& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	int32 result = strncmp(_string, other._string, len);
	return result == 1 || result == 0;
}

template<typename Type,
	typename TAllocator>
const Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getBegin() const
{
	return Iterator(&_string[0]);
}

template<typename Type,
	typename TAllocator>
const Str_Iterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getEnd() const
{
	return Iterator(&_string[_length - 1]);
}

template<typename Type,
	typename TAllocator>
const Str_ConstIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getCBegin() const
{
	return ConstIterator(&_string[0]);
}

template<typename Type,
	typename TAllocator>
const Str_ConstIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getCEnd() const
{
	return ConstIterator(&_string[_length - 1]);
}

template<typename Type,
	typename TAllocator>
const Str_ReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getRBegin() const
{
	return ReverseIterator(&_string[_length - 2]);
}

template<typename Type,
	typename TAllocator>
const Str_ReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getREnd() const
{
	return ReverseIterator(&_string[-1]);
}

template<typename Type,
	typename TAllocator>
const Str_ConstReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getCRBegin() const
{
	return ConstReverseIterator(&_string[_length - 2]);
}

template<typename Type,
	typename TAllocator>
const Str_ConstReverseIterator<Type, TAllocator>
Basic_QString<Type, TAllocator>::getCREnd() const
{
	return ConstReverseIterator(&_string[-1]);
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::getLength() const
{
	return _length - 1;
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::getMaxLength() const
{
	return _maxLength - 1;
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::getSize() const
{
	return _length - 1;
}

template<typename Type,
	typename TAllocator>
size_t Basic_QString<Type, TAllocator>::getMaxSize() const
{
	return _maxLength - 1;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_setLength(size_t len)
{
	_length = len;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_setMaxLength(size_t max)
{
	_maxLength = max;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_incrementLength()
{
	_length++;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_decrementLength()
{
	_length--;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_addLength(size_t amount)
{
	_length += amount;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_subtractLength(size_t amount)
{
	_length -= amount;
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_hasSpaceFor(size_t num) const
{
	return _length + num <= _maxLength;
}

template<typename Type,
	typename TAllocator>
void Basic_QString<Type, TAllocator>::_setTerminatingZero(size_t index)
{
	_string[index] = '\0';
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkIndex(size_t index) const
{
	return index < _length - 1 && index > 0 || (index == 0 && _length - 1 > 0);
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkIndicies(size_t begin, size_t end) const
{
	return _checkIndex(begin) && end <= _length - 1 && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkIterator(const Iterator iterator) const
{
	return iterator >= getBegin() && iterator < getEnd();
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkIterators(const Iterator begin, const Iterator end) const
{
	return _checkIterator(begin) && end <= getEnd() && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkReverseIterator(const ReverseIterator iterator) const
{
	return iterator >= getRBegin() && iterator < getREnd();
}

template<typename Type,
	typename TAllocator>
QBool Basic_QString<Type, TAllocator>::_checkReverseIterators(const ReverseIterator begin, const ReverseIterator end) const
{
	return _checkReverseIterator(begin) && _checkReverseIterator(end) && _comesBefore(begin, end);
}

template<typename Type,
	typename TAllocator>
Str_Comparison<Type, TAllocator>
Basic_QString<Type, TAllocator>::_compare(const Character* A, const Character* B, size_t length, const CharChecker& checker) const
{
	const Character* c1 = A;
	const Character* c2 = B;
	std::cout << "A: " << A - 1 << std::endl;
	std::cout << "B: " << B << std::endl;
	size_t count = 0;
	while (length)
	{
		count++;
		if (!checker(*c1, *c2))
		{
			std::cout << "TERMINATED AT: " << count << std::endl;
			break;
		}

		c1++;
		c2++;
		length--;
	}
	std::cout << "LENGTH: " << length << std::endl;
	return Comparison(count, length == 0);
}

template<typename Type,
	typename TAllocator>
Str_CharChecker<Type, TAllocator>
Basic_QString<Type, TAllocator>::_getCharChecker(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? CharChecker(chrcmp) : CharChecker(chricmp);
}

template<typename Type,
	typename TAllocator>
Str_StrChecker<Type, TAllocator>
Basic_QString<Type, TAllocator>::_getStrChecker(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? StrChecker(strncmp) : StrChecker(_strnicmp);
}

template<typename Type,
	typename TAllocator>
template<typename TIterator>
QBool Basic_QString<Type, TAllocator>::_comesBefore(TIterator begin, TIterator end) const
{
	return begin <= end;
}

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream& os, const Basic_QString<Type, TAllocator>& string)
{
	return os << string._string;
}