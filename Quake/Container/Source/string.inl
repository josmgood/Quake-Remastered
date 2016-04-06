#include "..\Include\string.hpp"

//QBool isSensitive(Sensitivity sensitivity)
//{
//	return sensitivity == STR_SENSITIVE;
//}
//
//QBool isInsensitive(Sensitivity sensitivity)
//{
//	return sensitivity == STR_INSENSITIVE;
//}

template<typename T, typename A>
const Basic_String<T, A> Basic_String<T, A>::EMPTY_STRING(nullptr);

template<typename T, typename A>
Basic_String<T, A>::Basic_String(size_t length)
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

template<typename T, typename A>
Basic_String<T, A>::Basic_String(const String string)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	if (string)
	{
		size_t otherLen = strlen(string);
		QBool hasTZero = *(string + otherLen - 1) == '\0';
		size_t len = hasTZero ? otherLen : otherLen + 1;
		_maxLength = len;
		_length = len - 1;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		strncpy_s(_string, len, string, otherLen);
		if (!hasTZero)
		{
			_setTerminatingZero(len - 1);
		}
	}
}

template<typename T, typename A>
Basic_String<T, A>::Basic_String(const Index begin, const Index end)
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

template<typename T, typename A>
Basic_String<T, A>::Basic_String(const Iterator begin, const Iterator end)
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

template<typename T, typename A>
Basic_String<T, A>::Basic_String(const Basic_String& string)
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

template<typename T, typename A>
Basic_String<T, A>::Basic_String(std::ifstream& ifstream)
	: _string(nullptr), _allocator(), _maxLength(), _length()
{
	ifstream.seekg(0, std::ios::end);
	size_t length = ifstream.tellg();
	_maxLength = length + 1;
	_length == _maxLength - 1;
	ifstream.seekg(0, std::ios::beg);
	Block block = _allocator.allocate(sizeof(Value) * (_maxLength));
	_string = static_cast<String>(block.memory);
	ifstream.read(_string, _maxLength);
	ifstream.close();
	_setTerminatingZero(_maxLength - 1);
}

template<typename T, typename A>
Basic_String<T, A>::~Basic_String()
{
	if (_string)
	{
		clear();
	}
	_allocator.destroy();
}

template<typename T, typename A>
void Basic_String<T, A>::pushBack(Character ch)
{
	if (!_hasSpaceFor(1))
	{
		reserve(_maxSize + STRING_RESERVE_SIZE);
	}
	_string[_size] = ch;
	_incrementSize();
}

template<typename T, typename A>
Str_Reference<T, A>
Basic_String<T, A>::front() const
{
	return _string[0];
}

template<typename T, typename A>
Str_Reference<T, A>
Basic_String<T, A>::back() const
{
	return _string[_size - 2];
}

template<typename T, typename A>
void Basic_String<T, A>::concat(const Character* string)
{
	size_t len = strlen(string);
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	strncat_s(_string, _maxLength, string, len);
	_addLength(len);
}

template<typename T,
	typename A>
	void Basic_String<T, A>::concat(const Basic_String& string)
{
	size_t len = string._length - 1;
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	strncat_s(_string, _maxLength, string._string, len);
	_addLength(len);
}

template<typename T, typename A>
Basic_String<T, A>
Basic_String<T, A>::substring(size_t start) const
{
	if (_checkIndex(start))
	{
		size_t len = _length - start - 1;
		Character* start = _string + start;
		return Basic_String(start);
	}
	return EMPTY_STRING;
}

template<typename T, typename A>
Basic_String<T, A>
Basic_String<T, A>::substring(size_t begin, size_t end) const
{
	if (_checkIndicies(begin, end))
	{
		size_t distance = end - begin;
		Character* start = _string + begin;
		Character* stop = _string + begin + distance - 1;
		return Basic_String(start, stop);
	}
	return EMPTY_STRING;
}

template<typename T, typename A>
Basic_String<T, A>
Basic_String<T, A>::substring(const Iterator iterator) const
{
	if (_checkIterator(iterator))
	{
		return Basic_String(iterator.ptr());
	}
	return EMPTY_STRING;
}

template<typename T, typename A>
Basic_String<T, A>
Basic_String<T, A>::substring(const Iterator begin, const Iterator end) const
{
	if (_checkIterators(begin, end))
	{
		return Basic_String(begin, end);
	}
}

template<typename T, typename A>
Str_Iterator<T, A>
Basic_String<T, A>::find(Character ch, Sensitivity sensitivity) const
{
	size_t begin = 0;
	size_t end = _length - 1;
	for (size_t i = begin; i < end; i++)
	{
		if (_string[i] == ch)
		{
			return Iterator(&_string[i]);
		}
	}
	return this->end();
}

//template<typename T,
//	typename A>
//Str_Iterator<T, A>
//Basic_String<T, A>::find(const String string, Sensitivity sensitivity) const
//{
//	size_t len = strlen(string);
//	CharChecker charCheck = _getCharChecker(sensitivity);
//	size_t begin = 0;
//	size_t end = _length - 1;
//	size_t i = begin;
//	while (i < end)
//	{
//		if (charCheck(string[0], _string[i]))
//		{
//			String start = _string + i;
//			Comparison comparison = _compare(start, string, len, charCheck);
//			if (comparison.isEqual)
//			{
//				return Iterator(&_string[i]);
//			}
//			else
//			{
//				i += comparison.traversed;
//			}
//		}
//		else
//		{
//			i++;
//		}
//	}
//	return this->end();
//}
//
//template<typename T,
//	typename A>
//Str_Iterator<T, A>
//Basic_String<T, A>::find(const Basic_String& string, Sensitivity sensitivity) const
//{
//	size_t len = string._length - 1;
//	CharChecker charCheck = _getCharChecker(sensitivity);
//	size_t begin = 0;
//	size_t end = _length - 1;
//	size_t i = begin;
//	while (i < end)
//	{
//		if (charCheck(string[0], _string[i]))
//		{
//			String start = _string + i;
//			Comparison comparison = _compare(start, string._string, len, charCheck);
//			if (comparison.isEqual)
//			{
//				return Iterator(&_string[i]);
//			}
//			else
//			{
//				i += comparison.traversed;
//			}
//		}
//		else
//		{
//			i++;
//		}
//	}
//	return this->end();
//}

template<typename T, typename A>
QBool Basic_String<T, A>::has(Character ch, Sensitivity sensitivity) const
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

//template<typename T, typename A>
//QBool Basic_String<T, A>::has(const Character* string, Sensitivity sensitivity) const
//{
//	size_t len = strlen(string);
//	CharChecker charCheck = _getCharChecker(sensitivity);
//	Iterator begin = getBegin();
//	Iterator end = getEnd();
//	Iterator i = begin;
//	while (i < end)
//	{
//		if (charCheck(string[0], i.get()))
//		{
//			size_t distance = iterator_distance(i, begin);
//			Character* start = _string + distance;
//			Comparison comparison = _compare(start, string, len, charCheck);
//			if (comparison.isEqual)
//			{
//				return true;
//			}
//			else
//			{
//				i = iterator_traverse(i, comparison.traversed);
//			}
//		}
//		else
//		{
//			++i;
//		}
//	}
//	return false;
//}
//
//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::has(const Basic_String& string, Sensitivity sensitivity) const
//{
//	size_t len = string._length - 1;
//	CharChecker charCheck = _getCharChecker(sensitivity);
//	Iterator begin = getBegin();
//	Iterator end = getEnd();
//	Iterator i = begin;
//	while (i < end)
//	{
//		if (charCheck(string[0], i.get()))
//		{
//			size_t distance = iterator_distance(i, begin);
//			Character* start = _string + distance;
//			Character* other = string._string;
//			Comparison comparison = _compare(start, other, len, charCheck);
//			if (comparison.isEqual)
//			{
//				return true;
//			}
//			else
//			{
//				i = iterator_traverse(i, comparison.traversed);
//			}
//		}
//		else
//		{
//			++i;
//		}
//	}
//	return false;
//}

//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::is(CharacterFilter filter, CharacterFilter exception) const
//{
//	Iterator begin = getBegin();
//	Iterator end = getEnd();
//	for (Iterator i = begin; i < end; ++i)
//	{
//		Character ch = i.get();
//		QBool match = filter(ch);
//		QBool except = exception ? exception(ch) : false;
//		if (filterNotMatch(match) && exceptionNotApply(except))
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::is(size_t index, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkIndex(index) ? filter(_string[index]) || (exception && exception(_string[index])) : false;
//}
//
//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
//{
//	if (_checkIndicies(begin, end))
//	{
//		size_t trueEnd = end + 1;
//		for (size_t i = begin; i < trueEnd; ++i)
//		{
//			Character ch = _string[i];
//			QBool match = filter(ch);
//			QBool except = exception ? exception(ch) : false;
//			if (filterNotMatch(match) && exceptionNotApply(except))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//
//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::is(const Iterator iterator, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkIterator(iterator) ? filter(iterator.get()) || (exception && exception(iterator.get())) : false;
//}
//
//template<typename T,
//	typename A>
//QBool Basic_String<T, A>::is(Iterator begin, Iterator end, CharacterFilter filter, CharacterFilter exception) const
//{
//	if (_checkIterators(begin, end))
//	{
//		Iterator trueEnd = end + 1;
//		for (Iterator i = begin; i < trueEnd; ++i)
//		{
//			Character ch = i.get();
//			QBool match = filter(ch);
//			QBool except = exception ? exception(ch) : false;
//			if (filterNotMatch(match) && exceptionNotApply(except))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}

template<typename T,
	typename A>
	void Basic_String<T, A>::to(CharacterConverter converter)
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

template<typename T,
	typename A>
	void Basic_String<T, A>::to(size_t index, CharacterConverter converter)
{
	if (_checkIndex(index))
	{
		Character ch = _string[index];
		ch = converter(ch);
		_string[index] = ch;
	}
}

template<typename T,
	typename A>
	void Basic_String<T, A>::to(size_t begin, size_t end, CharacterConverter converter)
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

//void Basic_String::to(Iterator iterator, CharacterConverter converter, CharacterFilter filter)
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
//void Basic_String::to(Iterator begin, Iterator end, CharacterConverter converter, CharacterFilter filter)
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

//void Basic_String::rto(size_t index, CharacterConverter converter, CharacterFilter filter)
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

////void Basic_String::rto(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
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
//void Basic_String::rto(ReverseIterator iterator, CharacterConverter converter, CharacterFilter filter)
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
//void Basic_String::rto(ReverseIterator begin, ReverseIterator end, CharacterConverter converter, CharacterFilter filter)
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

template<typename T, typename A>
void Basic_String<T, A>::copy(const String string)
{
	size_t max = strlen(string) + 1;
	if (_maxLength < max)
	{
		reserve(max);
	}
	strncpy_s(_string, max, string, max);
	_setLength(max);
}

template<typename T, typename A>
void Basic_String<T, A>::copy(const Basic_String& string)
{
	size_t max = string._maxLength;
	if (_maxLength < max)
	{
		reserve(max);
	}
	strncpy_s(_string, max, string._string, max);
	_setLength(string._length);
}

template<typename T, typename A>
void Basic_String<T, A>::swap(String string)
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

template<typename T, typename A>
void Basic_String<T, A>::reserve(size_t maxSize)
{
	if (maxSize > _maxLength)
	{
		Block alloc = _allocator.allocate(maxSize);
		String string = static_cast<String>(alloc.memory);
		strncpy_s(string, maxSize, _string, _maxLength);

		Block dealloc(_string, _maxLength);
		_allocator.deallocate(dealloc);
		_string = string;
		_setMaxLength(maxSize);
	}
}

template<typename T, typename A>
void Basic_String<T, A>::clear()
{
	Block block(_string, _maxLength);
	_allocator.deallocate(block);
	_length = 0;
	_maxLength = 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::equals(const String other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return !strncmp(_string, other, len);
	}
	return false;
}

template<typename T, typename A>
QBool Basic_String<T, A>::equals(const Basic_String& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return !strncmp(_string, other._string, len);
	}
	return false;
}

template<typename T, typename A>
QBool Basic_String<T, A>::isEmpty() const
{
	return _length == 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::isFull() const
{
	return _length == _maxLength;
}

template<typename T, typename A>
int32 Basic_String<T, A>::toInt32() const
{
	return atoi(_string);
}

template<typename T, typename A>
float64 Basic_String<T, A>::toFloat64() const
{
	return atof(_string);
}

template<typename T, typename A>
const Str_String<T, A>
Basic_String<T, A>::toCString() const
{
	return _string;
}

template<typename T, typename A>
Str_Reference<T, A>
Basic_String<T, A>::at(size_t index) const
{
	return _checkIndex(index) ? _string[index] : EMPTY_CHAR;
}

template<typename T, typename A>
Str_Reference<T, A>
Basic_String<T, A>::operator[](size_t index) const
{
	return at(index);
}

template<typename T, typename A>
void Basic_String<T, A>::operator=(const String string)
{
	if (string)
	{
		size_t otherLen = strlen(string);
		QBool hasTZero = *(string + otherLen - 1) == '\0';
		size_t len = hasTZero ? otherLen : otherLen - 1;
		_maxLength = len;
		_length = len - 1;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		strncpy_s(_string, len, string, otherLen);
		if (!hasTZero)
		{
			_setTerminatingZero(len - 1);
		}
	}
}

template<typename T, typename A>
void Basic_String<T, A>::operator=(const Container& container)
{
	if (container)
	{
		_maxLength = container._maxLength;
		_length = container._length;
		size_t len = container._length;
		Block block = _allocator.allocate(sizeof(Character) * len);
		_string = static_cast<String>(block.memory);
		const String str = container._string;
		strncpy_s(_string, _length, str, len);
	}
}

template<typename T, typename A>
Basic_String<T, A>::operator bool() const
{
	return _string && _length && _maxLength;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator==(const Character* other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return QBool(!strncmp(_string, other, len));
	}
	return false;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator!=(const Character* other) const
{
	size_t len = strlen(other) + 1;
	if (_length == len)
	{
		return QBool(strncmp(_string, other, len));
	}
	return true;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator<(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	return strncmp(_string, other, len) == -1;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator<=(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	int32 result = strncmp(_string, other, len);
	return result == -1 || result == 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator>(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	return strncmp(_string, other, len) == 1;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator>=(const Character* other) const
{
	size_t otherLen = strlen(other) + 1;
	size_t len = _length > otherLen ? _length : otherLen;
	int32 result = strncmp(_string, other, len);
	return result == 1 || result == 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator==(const Basic_String& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return QBool(!strncmp(_string, other._string, len));
	}
	return false;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator!=(const Basic_String& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return QBool(strncmp(_string, other._string, len));
	}
	return true;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator<(const Basic_String& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	return strncmp(_string, other._string, len) == -1;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator<=(const Basic_String& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	int32 result = strncmp(_string, other._string, len);
	return result == -1 || result == 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator>(const Basic_String& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	return strncmp(_string, other._string, len) == 1;
}

template<typename T, typename A>
QBool Basic_String<T, A>::operator>=(const Basic_String& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	int32 result = strncmp(_string, other._string, len);
	return result == 1 || result == 0;
}

template<typename T, typename A>
void Basic_String<T, A>::operator<<(std::ifstream& input)
{
	input.seekg(0, std::ios::end);
	size_t length = input.tellg();
	if (_maxLength < length)
	{
		clear();
		_maxLength = length + 1;
		_length = _maxLength - 1;
	}
	else if (_length + length < _maxLength)
	{
		reserve(length);
	}
	input.seekg(0, std::ios::beg);
	input.read(_string, length);
	input.close();
	_setTerminatingZero(_maxLength - 1);
}

template<typename T, typename A>
const Str_Iterator<T, A>
Basic_String<T, A>::begin() const
{
	return Iterator(&_string[0]);
}

template<typename T, typename A>
const Str_Iterator<T, A>
Basic_String<T, A>::end() const
{
	return Iterator(&_string[_length - 1]);
}

template<typename T, typename A>
const Str_ConstIterator<T, A>
Basic_String<T, A>::cbegin() const
{
	return ConstIterator(&_string[0]);
}

template<typename T, typename A>
const Str_ConstIterator<T, A>
Basic_String<T, A>::cend() const
{
	return ConstIterator(&_string[_length - 1]);
}

template<typename T, typename A>
const Str_ReverseIterator<T, A>
Basic_String<T, A>::rbegin() const
{
	return ReverseIterator(&_string[_length - 2]);
}

template<typename T, typename A>
const Str_ReverseIterator<T, A>
Basic_String<T, A>::rend() const
{
	return ReverseIterator(&_string[-1]);
}

template<typename T, typename A>
const Str_ConstReverseIterator<T, A>
Basic_String<T, A>::crbegin() const
{
	return ConstReverseIterator(&_string[_length - 2]);
}

template<typename T, typename A>
const Str_ConstReverseIterator<T, A>
	Basic_String<T, A>::crend() const
{
	return ConstReverseIterator(&_string[-1]);
}

template<typename T, typename A>
size_t Basic_String<T, A>::length() const
{
	return _length - 1;
}

template<typename T, typename A>
size_t Basic_String<T, A>::maxLength() const
{
	return _maxLength - 1;
}

template<typename T, typename A>
size_t Basic_String<T, A>::size() const
{
	return _length - 1;
}

template<typename T, typename A>
size_t Basic_String<T, A>::maxSize() const
{
	return _maxLength - 1;
}

template<typename T, typename A>
ALLOCATOR_ID Basic_String<T, A>::allocatorID() const
{
	return _allocator.getID();
}

template<typename T, typename A>
void Basic_String<T, A>::_setLength(size_t len)
{
	_length = len;
}

template<typename T, typename A>
void Basic_String<T, A>::_setMaxLength(size_t max)
{
	_maxLength = max;
}

template<typename T, typename A>
void Basic_String<T, A>::_incrementLength()
{
	_length++;
}

template<typename T, typename A>
void Basic_String<T, A>::_decrementLength()
{
	_length--;
}

template<typename T, typename A>
void Basic_String<T, A>::_addLength(size_t amount)
{
	_length += amount;
}

template<typename T, typename A>
void Basic_String<T, A>::_subtractLength(size_t amount)
{
	_length -= amount;
}

template<typename T, typename A>
QBool Basic_String<T, A>::_hasSpaceFor(size_t num) const
{
	return _length + num <= _maxLength;
}

template<typename T, typename A>
void Basic_String<T, A>::_setTerminatingZero(size_t index)
{
	_string[index] = '\0';
}

template<typename T,
	typename A>
	QBool Basic_String<T, A>::_checkIndex(size_t index) const
{
	return index < _length - 1 && index > 0 || (index == 0 && _length - 1 > 0);
}

template<typename T, typename A>
QBool Basic_String<T, A>::_checkIndicies(size_t begin, size_t end) const
{
	return _checkIndex(begin) && end <= _length - 1 && _comesBefore(begin, end);
}

template<typename T, typename A>
QBool Basic_String<T, A>::_checkIterator(const Iterator iterator) const
{
	return iterator >= getBegin() && iterator < getEnd();
}

template<typename T, typename A>
QBool Basic_String<T, A>::_checkIterators(const Iterator begin, const Iterator end) const
{
	return _checkIterator(begin) && end <= getEnd() && _comesBefore(begin, end);
}

template<typename T, typename A>
QBool Basic_String<T, A>::_checkReverseIterator(const ReverseIterator iterator) const
{
	return iterator >= getRBegin() && iterator < getREnd();
}

template<typename T, typename A>
QBool Basic_String<T, A>::_checkReverseIterators(const ReverseIterator begin, const ReverseIterator end) const
{
	return _checkReverseIterator(begin) && end <= getREnd() && _comesBefore(begin, end);
}

template<typename T, typename A>
Comparison Basic_String<T, A>::_compare(const Character* A, const Character* B, size_t length, const CharChecker& checker) const
{
	const Character* c1 = A;
	const Character* c2 = B;

	size_t count = 0;
	while (length)
	{
		count++;
		if (!checker(*c1, *c2))
		{
			break;
		}

		c1++;
		c2++;
		length--;
	}
	return Comparison(count, length == 0);
}

template<typename T, typename A>
Str_CharChecker<T, A>
Basic_String<T, A>::_getCharChecker(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? CharChecker(chrcmp) : CharChecker(chricmp);
}

template<typename T, typename A>
Str_StrChecker<T, A>
Basic_String<T, A>::_getStrChecker(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? StrChecker(strncmp) : StrChecker(_strnicmp);
}

template<typename T, typename A>
size_t Basic_String<T, A>::_getSearchBegin(Direction direction) const
{
	return isForward(direction) ? 0 : _length - 2;
}

template<typename T, typename A>
size_t Basic_String<T, A>::_getSearchEnd(Direction direction) const
{
	return isForward(direction) ? _length - 1 : 0;
}

template<typename T, typename A>
QBool Basic_String<T, A>::_endNotReached(size_t index, size_t end, Direction direction) const
{
	return isForward(direction) ? index < end : index > end;
}

template<typename T, typename A>
size_t Basic_String<T, A>::_increment(size_t traversed, Direction direction) const
{
	return isForward(direction) ? traversed : -traversed;
}

template<typename T, typename A>
	template<typename TIterator>
QBool Basic_String<T, A>::_comesBefore(TIterator begin, TIterator end) const
{
	return begin <= end;
}

template<typename T, typename A>
	std::ostream& operator<<(std::ostream& os, const Basic_String<T, A>& string)
{
	return os << string._string;
}