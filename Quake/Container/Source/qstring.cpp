#include "..\Include\qstring.h"

QBool isSensitive(Sensitivity sensitivity)
{
	return sensitivity == STR_SENSITIVE;
}

QBool isUnsensitivity(Sensitivity sensitivity)
{
	return sensitivity == STR_UNSENSITIVE;
}

QString::QString(size_t length)
	:  _maxLength(), _length()
{
	//_string = _allocator.allocate(sizeof(Character) * length);
	size_t zeroLen = length + 1;
	_maxLength = zeroLen;
	_length = 1;
	_string = new char[zeroLen];
	_string[0] = '\0';
}

QString::QString(const Character* string)
	:  _maxLength(), _length()
{
	if (string)
	{
		size_t len = 1;
		const Character* ch = string;
		while (*ch++)
		{
			len++;
		}
		_maxLength = len;
		_length = len;
		_string = new char[len];
		Character* tc = _string;
		const Character* oc = string;
		while (*oc)
		{
			*tc = *oc;
			tc++;
			oc++;
		}
		*tc++ = '\0';
	}
}

QString::QString(const QString& string)
	: _maxLength(string._maxLength), _length(string._length)
{
	if (string != EMPTY_STRING)
	{
		_string = new char[_length];
		Character* tc = _string;
		Character* oc = string._string;
		while(*oc)
		{
			*tc = *oc;

			tc++;
			oc++;
		}
		*tc++ = '\0';
	}
}

QString::~QString()
{
	delete[] _string;
}

//void QString::pushFront(Character ch)
//{
//	if (!_hasSpaceFor(1))
//	{
//		reserve(_maxLength + 3);
//	}
//	Character last = _string[0];
//	_string[0] = ch;
//	size_t end = _length + 1;
//	for (size_t i = 1; i < end; ++i)
//	{
//		Character hold = _string[i];
//		_string[i] = last;
//		last = hold;
//	}
//	_incrementLength();
//	_adjustEnd(1);
//}
//
//void QString::pushFront(const Character* string)
//{
//	/*size_t len = 0;
//	const Character* ch = string;
//	while (*ch++)
//	{
//		len++;
//	}
//
//	if (!_hasSpaceFor(len))
//	{
//		reserve(_maxLength + len);
//	}
//	Character last = _string[0];
//	_string[0] = string[0];
//	size_t end = _length + len;
//	for (size_t i = 1; i < end; ++i)
//	{
//		Character hold = _string[i];
//		_string[i] = last;
//		last = hold;
//
//		if (i < len)
//		{
//			_string[i - 1]
//		}
//	}*/
//}
//
//void QString::setFront(Character ch)
//{
//	if (_length > 1)
//	{
//		_string[0] = ch;
//	}
//}
//
//QString::Reference QString::getFront() const
//{
//	return _string[0];
//}
//
//void QString::pushBack(Character ch)
//{
//	if (_hasSpaceFor(1))
//	{
//		_string[_length - 1] = ch;
//		_string[_length] = '\0';
//		_incrementLength();
//		_adjustEnd(1);
//	}
//}
//
//void QString::pushBack(const Character* string)
//{
//	size_t len = 0;
//	const Character* ch = string;
//	while (*ch++)
//	{
//		len++;
//	}
//	if (!_hasSpaceFor(len))
//	{
//		reserve(_maxLength + len);
//	}
//	for (size_t i = _length - 1, j = 0; i < _maxLength; ++i, ++j)
//	{
//		Character ch = string[j];
//		_string[i] = ch;
//	}
//	_addLength(len);
//	_adjustEnd(len);
//	_setTerminatingZero(_length - 1);
//}
//
//void QString::pushBack(const QString& string)
//{
//	size_t len = string.getLength() - 1;
//	if (!_hasSpaceFor(len))
//	{
//		reserve(_maxLength + len);
//	}
//	for (size_t i = _length, j = 0; i < _maxLength; ++i, ++j)
//	{
//		Character ch = string[j];
//		_string[i] = ch;
//	}
//	_addLength(len);
//	_adjustEnd(len);
//	_setTerminatingZero(_length - 1);
//}
//
//void QString::setBack(Character ch)
//{
//	if (_length - 2 >= 0)
//	{
//		_string[_length - 2] = ch;
//	}
//}
//
//QString::Reference QString::getBack() const
//{
//	return _string[_length - 2];
//}
//
//void QString::concat(const Character* string)
//{
//	size_t len = 0;
//	const Character* ch = string;
//	while (*ch++)
//	{
//		len++;
//	}
//	if (!_hasSpaceFor(len))
//	{
//		reserve(_maxLength + len);
//	}
//	for (size_t i = _length - 1, j = 0; i < _maxLength; ++i, ++j)
//	{
//		Character ch = string[j];
//		_string[i] = ch;
//	}
//	_addLength(len);
//	_adjustEnd(len);
//	_setTerminatingZero(_length - 1);
//}
//
//void QString::concat(const QString& string)
//{
//	size_t len = string.getLength() - 1;
//	if (!_hasSpaceFor(len))
//	{
//		reserve(_maxLength + len);
//	}
//	for (size_t i = _length - 1, j = 0; i < _maxLength; ++i, ++j)
//	{
//		Character ch = string[j];
//		_string[i] = ch;
//	}
//	_addLength(len);
//	_adjustEnd(len);
//	_setTerminatingZero(_length - 1);
//}
//
//void QString::insert(size_t index, Character ch)
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
//void QString::insert(size_t begin, size_t end, const Character* string)
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
//void QString::insert(size_t begin, size_t end, const QString& string)
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
//void QString::insert(Iterator iterator, Character ch)
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
//
//void QString::set(size_t index, Character ch)
//{
//	if (_checkIndex(index))
//	{
//		_string[index] = ch;
//	}
//}
//
//void QString::set(size_t begin, size_t end, const Character* string)
//{
//	size_t len = Q_strLen(string);
//	if (_checkIndicies(begin, end) && begin + end == len)
//	{
//		size_t trueEnd = end + 1;
//		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
//		{
//			_string[i] = string[j];
//		}
//	}
//}
//
//void QString::set(size_t begin, size_t end, const QString& string)
//{
//	size_t len = string.getLength();
//	if (_checkIndicies(begin, end) && begin + end == len)
//	{
//		size_t trueEnd = end + 1;
//		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
//		{
//			_string[i] = string[j];
//		}
//	}
//}
//
//void QString::set(Iterator iterator, Character ch)
//{
//	if (_checkIterator(iterator))
//	{
//		iterator.set(ch);
//	}
//}
//
//void QString::set(Iterator begin, Iterator end, const Character* string)
//{
//	size_t len = Q_strLen(string);
//	if (_checkIterators(begin, end) && begin + len == end)
//	{
//		Iterator trueEnd = end + 1;
//		size_t j = 0;
//		for (Iterator i = begin; i < trueEnd; ++i, ++j)
//		{
//			Character ch = string[j];
//			i.set(ch);
//		}
//	}
//}
//
//void QString::set(Iterator begin, Iterator end, const QString& string)
//{
//	size_t len = string.getLength();
//	if (_checkIterators(begin, end) && begin + len == end)
//	{
//		Iterator trueEnd = end + 1;
//		size_t j = 0;
//		for (Iterator i = begin; i < trueEnd; ++i, ++j)
//		{
//			Character ch = string[j];
//			i.set(ch);
//		}
//	}
//}
//
//QString QString::substring(size_t index) const
//{
//	if (_checkIndex(index))
//	{
//		size_t len = _length - index;
//		if (len > 0)
//		{
//			Character* substring = new Character[len];
//			for (size_t i = 0; i < len - 1; ++i)
//			{
//				Character ch = _string[index + i];
//				substring[i] = ch;
//			}
//			substring[len - 1] = '\0';
//			return QString(substring);
//		}
//	}
//	return EMPTY_STRING;
//}
//
//QString QString::substring(size_t begin, size_t end) const
//{
//	if (_checkIndicies(begin, end))
//	{
//		size_t len = end - begin + 1;
//		if (len > 0)
//		{
//			Character* substring = new Character[len];
//			for (size_t i = 0; i < len - 1; ++i)
//			{
//				Character ch = _string[begin + i];
//				substring[i] = ch;
//			}
//			substring[len - 1] = '\0';
//			return QString(substring);
//		}
//	}
//	return EMPTY_STRING;
//}
//
////QString QString::substring(Iterator iterator) const
////{
////	if (_checkIterator(iterator))
////	{
////		Iterator end = _end;
////		size_t len = end.ptr() - iterator.ptr();
////		Character* substring = new Character[len];
////		for (size_t i = 0; i < len; ++i)
////		{
////			Character ch = (iterator + i).get();
////			substring[i] = ch;
////		}
////		substring[len - 1] = '\0';
////		return QString(substring);
////	}
////	return EMPTY_STRING;
////}
////
////QString::Iterator QString::find(Character ch, Sensitivity sensitivity) const
////{
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			return i;
////		}
////	}
////	return end;
////}
////
////QString::Iterator QString::find(const Character* string, Sensitivity sensitivity) const
////{
////	/*size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	Iterator found = end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			found = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					return found;
////				}
////			}
////		}
////	}
////	return end;*/
////	return Iterator();
////}
////
////QString::Iterator QString::find(const QString& string, Sensitivity sensitivity) const
////{
////	/*size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	Iterator found = end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			found = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					return found;
////				}
////			}
////		}
////	}
////	return end;*/
////	return Iterator();
////}
////
////QString::ReverseIterator QString::rfind(Character ch, Sensitivity sensitivity) const
////{
////	/*CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			return i;
////		}
////	}
////	return end;*/
////	return ReverseIterator();
////}
////
////QString::ReverseIterator QString::rfind(const Character* string, Sensitivity sensitivity) const
////{
////	/*size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	ReverseIterator found = end;
////	QBool b = begin < end;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			found = i;
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (j == -1)
////				{
////					return found;
////				}
////			}
////		}
////	}
////	return end;*/
////	return ReverseIterator();
////}
////
////QString::ReverseIterator QString::rfind(const QString& string, Sensitivity sensitivity) const
////{
////	/*size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	ReverseIterator found = end;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			found = i;
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (j == -1)
////				{
////					return found;
////				}
////			}
////		}
////	}
////	return end;*/
////	return ReverseIterator();
////}
////
////QString::Iterator QString::findLast(Character ch, Sensitivity sensitivity) const
////{
////	/*CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	Iterator found = end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			found = i;
////		}
////	}
////	return found;*/
////	return Iterator();
////}
////
////QString::Iterator QString::findLast(const Character* string, Sensitivity sensitivity) const
////{
////	/*size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	Iterator found = end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			Iterator possible = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					found = possible;
////				}
////			}
////		}
////	}
////	return found;*/
////	return Iterator();
////}
////
////QString::Iterator QString::findLast(const QString& string, Sensitivity sensitivity) const
////{
////	/*size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	Iterator found = end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			Iterator possible = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					found = possible;
////				}
////			}
////		}
////	}
////	return found;*/
////	return Iterator();
////}
////
////QString::Iterator QString::findnth(Character ch, size_t buffer, Sensitivity sensitivity) const
////{
////	/*CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			if (!--buffer)
////			{
////				return i;
////			}
////		}
////	}
////	return end;*/
////	return Iterator();
////}
////
////QString::Iterator QString::findnth(const Character* string, size_t buffer, Sensitivity sensitivity) const
////{
////	/*size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			Iterator possible = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					if (!--buffer)
////					{
////						return possible;
////					}
////				}
////			}
////		}
////	}
////	return end;*/
////	return Iterator();
////}
////
////QString::Iterator QString::findnth(const QString& string, size_t buffer, Sensitivity sensitivity) const
////{
////	/*size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			Iterator possible = i;
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					if (!--buffer)
////					{
////						return possible;
////					}
////				}
////			}
////		}
////	}
////	return end;*/
////	return Iterator();
////}
////
////QString::ReverseIterator QString::rfindnth(Character ch, size_t buffer, Sensitivity sensitivity) const
////{
////	/*CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			if (!--buffer)
////			{
////				return i;
////			}
////		}
////	}
////	return end;*/
////	return ReverseIterator();
////}
////
////QString::ReverseIterator QString::rfindnth(const Character* string, size_t buffer, Sensitivity sensitivity) const
////{
////	/*size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			ReverseIterator possible = i;
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (caseCheck(string[j], i.get()) && j == 0)
////				{
////					if (!--buffer)
////					{
////						return possible;
////					}
////				}
////			}
////		}
////	}
////	return end;*/
////	return ReverseIterator();
////}
////
////QString::ReverseIterator QString::rfindnth(const QString& string, size_t buffer, Sensitivity sensitivity) const
////{
////	size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	if (!buffer)
////	{
////		buffer = 1;
////	}
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			ReverseIterator possible = i;
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (caseCheck(string[j], i.get()) && j == 0)
////				{
////					if (!--buffer)
////					{
////						return possible;
////					}
////				}
////			}
////		}
////	}
////	return end;
////}
////
////QBool QString::has(Character ch, Sensitivity sensitivity) const
////{
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			return true;
////		}
////	}
////	return false;
////}
////
////QBool QString::has(const Character* string, Sensitivity sensitivity) const
////{
////	size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					return true;
////				}
////			}
////		}
////	}
////	return false;
////}
////
////QBool QString::has(const QString& string, Sensitivity sensitivity) const
////{
////	size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					return true;
////				}
////			}
////		}
////	}
////	return false;
////}
////
////QBool QString::rhas(Character ch, Sensitivity sensitivity) const
////{
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			return true;
////		}
////	}
////	return false;
////}
////
////QBool QString::rhas(const Character* string, Sensitivity sensitivity) const
////{
////	size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (caseCheck(string[j], i.get()) && j == 0)
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
////QBool QString::rhas(const QString& string, Sensitivity sensitivity) const
////{
////	size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	ReverseIterator begin = _rbegin;
////	ReverseIterator end = _rend;
////	for (ReverseIterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[len - 1], i.get()))
////		{
////			++i;
////			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
////			{
////				if (caseCheck(string[j], i.get()) && j == 0)
////				{
////					return true;
////				}
////			}
////		}
////	}
////	return false;
////}
////
////size_t QString::occurances(Character ch, Sensitivity sensitivity) const
////{
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	size_t occurances = 0;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(ch, i.get()))
////		{
////			++occurances;
////		}
////	}
////	return occurances;
////}
////
////size_t QString::occurances(const Character* string, Sensitivity sensitivity) const
////{
////	size_t len = Q_strLen(string);
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	size_t occurances = 0;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					++occurances;
////				}
////			}
////		}
////	}
////	return occurances;
////}
////
////size_t QString::occurances(const QString& string, Sensitivity sensitivity) const
////{
////	size_t len = string.getLength();
////	CaseChecker caseCheck = _getCase(sensitivity);
////	Iterator begin = _begin;
////	Iterator end = _end;
////	size_t occurances = 0;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (caseCheck(string[0], i.get()))
////		{
////			++i;
////			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
////			{
////				if (j == len - 1)
////				{
////					++occurances;
////				}
////			}
////		}
////	}
////	return occurances;
////}
////
////QBool QString::is(CharacterFilter filter, CharacterFilter exception) const
////{
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		if (!filter(i.get()) || !exception(i.get()))
////		{
////			return false;
////		}
////	}
////	return true;
////}
//
//QBool QString::is(size_t index, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkIndex(index) ? filter(_string[index]) || exception(_string[index]) : false;
//}
//
//QBool QString::is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
//{
//	if (_checkIndicies(begin, end))
//	{
//		size_t trueEnd = end + 1;
//		for (size_t i = begin; i < trueEnd; ++i)
//		{
//			if (!filter(_string[i]) && !exception(_string[i]))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//
//QBool QString::is(Iterator iterator, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkIterator(iterator) ? filter(iterator.get()) || exception(iterator.get()) : false;
//}
//
//QBool QString::is(Iterator begin, Iterator end, CharacterFilter filter, CharacterFilter exception) const
//{
//	if (_checkIterators(begin, end))
//	{
//		Iterator trueEnd = end + 1;
//		for (Iterator i = begin; i < trueEnd; ++i)
//		{
//			if (!filter(i.get()) && !exception(i.get()))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//
////QBool QString::ris(size_t index, CharacterFilter filter, CharacterFilter exception) const
////{
////	if (_checkNegativeIndex(index))
////	{
////		size_t pos = _negToPos(index);
////		return filter(_string[pos]) || exception(_string[pos]);
////	}
////	return false;
////}
////
////QBool QString::ris(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
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
//QBool QString::ris(ReverseIterator iterator, CharacterFilter filter, CharacterFilter exception) const
//{
//	return _checkReverseIterator(iterator) ? filter(iterator.get()) || exception(iterator.get()) : false;
//}
//
//QBool QString::ris(ReverseIterator begin, ReverseIterator end, CharacterFilter filter, CharacterFilter exception) const
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
//
////void QString::to(CharacterConverter converter, CharacterFilter filter)
////{
////	Iterator begin = _begin;
////	Iterator end = _end;
////	for (Iterator i = begin; i < end; ++i)
////	{
////		Character ch = i.get();
////		if (!filter(ch))
////		{
////			ch = converter(ch);
////			i.set(ch);
////		}
////	}
////}
//
//void QString::to(size_t index, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkIndex(index))
//	{
//		Character ch = _string[index];
//		if (!filter(ch))
//		{
//			ch = converter(ch);
//			_string[index] = ch;
//		}
//	}
//}
//
//void QString::to(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
//{
//	if (_checkIndicies(begin, end))
//	{
//		size_t trueEnd = end + 1;
//		for (size_t i = begin; i < trueEnd; ++i)
//		{
//			Character ch = _string[i];
//			if (!filter(ch))
//			{
//				ch = converter(ch);
//				_string[i] = ch;
//			}
//		}
//	}
//}
//
//void QString::to(Iterator iterator, CharacterConverter converter, CharacterFilter filter)
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
//void QString::to(Iterator begin, Iterator end, CharacterConverter converter, CharacterFilter filter)
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
//
////void QString::rto(size_t index, CharacterConverter converter, CharacterFilter filter)
////{
////	if (_checkNegativeIndex(index))
////	{
////		size_t i = _negToPos(index);
////		Character ch = _string[i];
////		if (!filter(ch))
////		{
////			_string[i] = converter(ch);
////		}
////	}
////}
////
////void QString::rto(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
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
//void QString::rto(ReverseIterator iterator, CharacterConverter converter, CharacterFilter filter)
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
//void QString::rto(ReverseIterator begin, ReverseIterator end, CharacterConverter converter, CharacterFilter filter)
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

void QString::copy(const QString& string)
{
	size_t max = string._maxLength;
	if (_maxLength < max)
	{
		reserve(max);
	}
	strncpy_s(_string, max, string._string, max);
	_setLength(string._length);
}

void QString::reserve(size_t size)
{
	if (size > _maxLength)
	{
		Character* string = new Character[size];
		//std::strncpy_s(string, _string, _length);
		//delete[] _string;
		_string = string;
		_setMaxLength(size);
	}
}

void QString::clear()
{
	delete[] _string;
	_length = 0;
	_maxLength = 0;
}

QBool QString::isEmpty() const
{
	return _length == 0;
}

QBool QString::isFull() const
{
	return _length == _maxLength;
}

int32 QString::toInt32() const
{
	return atoi(_string);
}

float64 QString::toFloat64() const
{
	return atof(_string);
}

const QString::Character* QString::toCString() const
{
	return _string;
}

QString::Reference QString::at(size_t index) const
{
	return _checkIndex(index) ? _string[index] : EMPTY_CHAR;
}

QString::Reference QString::operator[](size_t index) const
{
	return at(index);
}

////QString QString::operator+(const char* string)
////{
////	/*size_t len = Q_strLen(string);
////	if (_length + len >= _maxLength)
////	{
////		size_t oldLen = _length;
////		Q_strDelete(_string, _maxLength);
////		_string = new char[oldLen + len];
////	}
////	for (size_t i = 0, j = _l; i < len; i++)
////	{
////
////	}*/
////	return EMPTY_STRING;
////}
//
//QBool QString::operator==(const Character* other) const
//{
//	const Character* A = _string;
//	const Character* B = other;
//	while (*A || *B)
//	{
//		if (!Q_chrCmp(*A, *B) || !*A || !*B)
//		{
//			return false;
//		}
//		A++;
//		B++;
//	}
//	return true;
//}
//
//QBool QString::operator!=(const Character* other) const
//{
//	/*for (size_t i = 0; i < _length; i++)
//	{
//
//	}*/
//	return false;
//}
//
QBool QString::operator<(const Character* other) const
{
	/*const Character* A = _string;
	const Character* B = other;
	size_t Alen = 0;
	size_t Blen = 0;
	while (*A || *B)
	{

	}*/
	return false;
}

QBool QString::operator==(const QString& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return !strncmp(_string, other._string, len);
	}
	return false;
}

QBool QString::operator!=(const QString& other) const
{
	size_t len = other._length;
	if (_length == len)
	{
		return strncmp(_string, other._string, len);
	}
	return true;
}

QBool QString::operator<(const QString& other) const
{
	size_t len = _length > other._length ? _length : other._length;
	return strncmp(_string, other._string, len) == -1;
}

const QString::Iterator QString::getBegin() const
{
	return Iterator(&_string[0]);
}

const QString::Iterator QString::getEnd() const
{
	return Iterator(&_string[_length - 1]);
}

const QString::ConstIterator QString::getCBegin() const
{
	return ConstIterator(&_string[0]);
}

const QString::ConstIterator QString::getCEnd() const
{
	return ConstIterator(&_string[_length - 1]);
}

const QString::ReverseIterator QString::getRBegin() const
{
	return ReverseIterator(&_string[_length - 2]);
}

const QString::ReverseIterator QString::getREnd() const
{
	return ReverseIterator(&_string[-1]);
}

const QString::ConstReverseIterator QString::getCRBegin() const
{
	return ConstReverseIterator(&_string[_length - 2]);
}

const QString::ConstReverseIterator QString::getCREnd() const
{
	return ConstReverseIterator(&_string[-1]);
}

size_t QString::getLength() const
{
	return _length - 1;
}

size_t QString::getMaxLength() const
{
	return _maxLength - 1;
}

size_t QString::getSize() const
{
	return _length - 1;
}

size_t QString::getMaxSize() const
{
	return _maxLength - 1;
}

void QString::_setLength(size_t len)
{
	_length = len;
}

void QString::_setMaxLength(size_t max)
{
	_maxLength = max;
}

void QString::_incrementLength()
{
	_length++;
}

void QString::_decrementLength()
{
	_length--;
}

void QString::_addLength(size_t amount)
{
	_length += amount;
}

void QString::_subtractLength(size_t amount)
{
	_length -= amount;
}

QBool QString::_hasSpaceFor(size_t num) const
{
	return _length + num <= _maxLength;
}

void QString::_setTerminatingZero(size_t index)
{
	_string[index] = '\0';
}

QBool QString::_checkIndex(size_t index) const
{
	return index < _length - 1 && index > 0;
}

QBool QString::_checkIndicies(size_t begin, size_t end) const
{
	return _checkIndex(begin) && _checkIndex(end) && _comesBefore(begin, end);
}

QBool QString::_checkIterator(Iterator iterator) const
{
	return iterator >= getBegin() && iterator < getEnd();
}

QBool QString::_checkIterators(Iterator begin, Iterator end) const
{
	return _checkIterator(begin) && _checkIterator(end) && _comesBefore(begin, end);
}

QBool QString::_checkReverseIterator(ReverseIterator iterator) const
{
	return iterator >= getRBegin() && iterator < getREnd();
}

QBool QString::_checkReverseIterators(ReverseIterator begin, ReverseIterator end) const
{
	return _checkReverseIterator(begin) && _checkReverseIterator(end) && _comesBefore(begin, end);
}

QString::CaseChecker QString::_getCase(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? CaseChecker(strncmp) : CaseChecker(_strnicmp);
}

std::ostream& operator<<(std::ostream& os, const QString& string)
{
	return os << string._string;
}