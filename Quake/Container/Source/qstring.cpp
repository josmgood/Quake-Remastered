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
	: _isInitialized(false), _maxLength(length), _length(), 
	_begin(), _end(), _rbegin(), _rend()
{
	//_string = _allocator.allocate(sizeof(Character) * length);
	_string = new char[length];

	if (_string)
	{
		_createIteratorFlags(0);
		_isInitialized = true;
	}
}

QString::QString(const char* string)
	: _isInitialized(false), _maxLength(), _length(),
	_begin(), _end(), _rbegin(), _rend()
{
	size_t len = Q_strLen(string);
	_maxLength = len;
	_length = len;
	_string = new char[len];
	Q_strCpy(string, _string, len);
	if (_string)
	{
		_createIteratorFlags(len);
		_isInitialized = true;
	}
}

QString::QString(const QString& string)
	: _isInitialized(false), _maxLength(string._maxLength), _length(string._length),
	_begin(), _end(), _rbegin(), _rend()
{
	_string = new char[_length];
	Q_strCpy(string._string, _string, _length);
	if (_string)
	{
		_createIteratorFlags(_length);
		_isInitialized = true;
	}
}

QString::~QString()
{
	delete[] _string;
}

void QString::pushFront(Character ch)
{
	/*if (_hasSpaceFor(1))
	{
		Character last = _string[0];
		_string[0] = ch;
		Iterator end = getEnd();
		for (Iterator i = getBegin(); i < end; ++i)
		{
			Character tmp = i.get();
			i.set(tmp);
			last = tmp;
		}
		_incrementLength();
		_adjustEnd(1);
	}*/

	if (!_hasSpaceFor(1))
	{
		reserve(_maxLength + 1);
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
	_adjustEnd(1);
}

void QString::setFront(Character ch)
{
	if (_length > 0)
	{
		_string[0] = ch;
	}
}

QString::Reference QString::getFront() const
{
	return _string[0];
}

void QString::pushBack(Character ch)
{
	if (_hasSpaceFor(1))
	{
		_string[_length] = ch;
		_incrementLength();
		_adjustEnd(1);
	}
}

void QString::pushBack(const Character* string, size_t length)
{
	size_t len = !length ? Q_strLen(string) : length;
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	for (size_t i = _length, j = 0; i < _maxLength; ++i, ++j)
	{
		_string[i] = string[j];
	}
}

void QString::pushBack(const QString& string)
{
	size_t len = string.getLength();
	if (!_hasSpaceFor(len))
	{
		reserve(_maxLength + len);
	}
	for (size_t i = _length, j = 0; i < _maxLength; ++i, ++j)
	{
		_string[i] = string[j];
	}
}

void QString::setBack(Character ch)
{
	if (_length - 1 >= 0)
	{
		_string[_length - 1] = ch;
	}
}

QString::Reference QString::getBack() const
{
	return _string[_length - 1];
}

void QString::concat(const Character* string, size_t length)
{
	size_t len = length != 0 ? length : Q_strLen(string);
	size_t spaceLeft = _maxLength - _length;
	if (spaceLeft < len)
	{
		size_t newLen = _maxLength + len;
		Character* str = new Character[newLen];
		Q_strCpy(_string, str, _length);
		delete[] _string;
		_string = str;
		_maxLength = newLen;
	}
	Q_strCpy(string, _string + _length, len);
	_length += len;
	_createIteratorFlags(_length);
}

void QString::concat(const QString& string)
{
	size_t len = string.getLength();
	const char* raw = string._string;
	size_t spaceLeft = _maxLength - _length;
	if (spaceLeft < len)
	{
		size_t newLen = _maxLength + len;
		Character* str = new Character[newLen];
		Q_strCpy(_string, str, _length);
		delete[] _string;
		_string = str;
		_maxLength = newLen;
	}
	Q_strCpy(raw, _string + _length, len);
	_length += len;
	_createIteratorFlags(_length);
}

void QString::insert(size_t index, Character ch)
{
	if (_checkIndex(index))
	{
		if (!_hasSpaceFor(1))
		{
			reserve(_maxLength + 5);
		}
		for (size_t i = index; i < _length; ++i)
		{
			Character hold = _string[i];
			Character next = _string[i + 1];
			_string[i + 1] = hold;
		}
		_string[index] = ch;
		_incrementLength();
		_adjustEnd(1);
	}
}

void QString::insert(size_t begin, size_t end, const Character* string)
{
	if (_checkIndicies(begin, end) || _checkIndex(begin) && _comesBefore(begin, end))
	{
		size_t spaceNeeded = end - begin;
		if (!_hasSpaceFor(spaceNeeded))
		{
			reserve(spaceNeeded);
		}
		size_t trueEnd = end + 1;
		Character hold = _string[0];
		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
		{
			Character hold = _string[i];
			Character next = _string[i + 1];
			_string[i + 1] = hold;
			hold = next;

			Character ch = string[j];
			_string[i] = ch;
		}
		size_t newLen = _length + spaceNeeded;
		_setLength(newLen);
		_adjustEnd(newLen);
	}
}

void QString::insert(size_t begin, size_t end, const QString& string)
{
	if (_checkNegativeIndicies(begin, end) || _checkIndex(begin) && _comesBefore(begin, end))
	{
		size_t spaceNeeded = end - begin;
		if (!_hasSpaceFor(spaceNeeded))
		{
			reserve(_maxLength + spaceNeeded);
		}
		size_t trueEnd = end + 1;
		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
		{
			Character hold = _string[i];
			Character next = _string[i + 1];
			_string[i + 1] = hold;

			Character ch = string[j];
			_string[i] = ch;
		}
		_setLength(_length + spaceNeeded);
		//_adjustEnd(spaceNeeded);
	}
}

void QString::insert(Iterator iterator, Character ch)
{
	if (_checkIterator(iterator))
	{
		if (!_hasSpaceFor(1))
		{
			reserve(_maxLength + 5);
		}
		for (Iterator i = _begin; i < _end; ++i)
		{
			Iterator hold = i;
			Iterator next = i.next();
			i.next() = hold;
		}
		iterator.set(ch);
		_incrementLength();
		_adjustEnd(1);
	}
}

void QString::set(size_t index, Character ch)
{
	if (_checkIndex(index))
	{
		_string[index] = ch;
	}
}

void QString::set(size_t begin, size_t end, const Character* string)
{
	size_t len = Q_strLen(string);
	if (_checkIndicies(begin, end) && begin + end == len)
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
		{
			_string[i] = string[j];
		}
	}
}

void QString::set(size_t begin, size_t end, const QString& string)
{
	size_t len = string.getLength();
	if (_checkIndicies(begin, end) && begin + end == len)
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin, j = 0; i < trueEnd; ++i, ++j)
		{
			_string[i] = string[j];
		}
	}
}

void QString::set(Iterator iterator, Character ch)
{
	if (_checkIterator(iterator))
	{
		iterator.set(ch);
	}
}

void QString::set(Iterator begin, Iterator end, const Character* string)
{
	size_t len = Q_strLen(string);
	if (_checkIterators(begin, end) && begin + len == end)
	{
		Iterator trueEnd = end + 1;
		size_t j = 0;
		for (Iterator i = begin; i < trueEnd; ++i, ++j)
		{
			Character ch = string[j];
			i.set(ch);
		}
	}
}

void QString::set(Iterator begin, Iterator end, const QString& string)
{
	size_t len = string.getLength();
	if (_checkIterators(begin, end) && begin + len == end)
	{
		Iterator trueEnd = end + 1;
		size_t j = 0;
		for (Iterator i = begin; i < trueEnd; ++i, ++j)
		{
			Character ch = string[j];
			i.set(ch);
		}
	}
}

QString QString::substring(size_t begin)
{
	if (begin <= _length)
	{
		size_t len = _length - begin - 1;
		QString string(len);
		string._length = len;
		Index start = _string + begin + 1;
		Q_strCpy(start, string._string);
		return string;
	}
	return EMPTY_STRING;
}

QString::Iterator QString::find(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			return i;
		}
	}
	return end;
}

QString::Iterator QString::find(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			found = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					return found;
				}
			}
		}
	}
	return end;
}

QString::Iterator QString::find(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			found = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					return found;
				}
			}
		}
	}
	return end;
}

QString::ReverseIterator QString::rfind(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			return i;
		}
	}
	return end;
}

QString::ReverseIterator QString::rfind(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	ReverseIterator found = end;
	QBool b = begin < end;
	std::cout << b << std::endl;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			found = i;
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (j == -1)
				{
					return found;
				}
			}
		}
	}
	return end;
}

QString::ReverseIterator QString::rfind(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	ReverseIterator found = end;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			found = i;
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (j == -1)
				{
					return found;
				}
			}
		}
	}
	return end;
}

QString::Iterator QString::findLast(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			found = i;
		}
	}
	return found;
}

QString::Iterator QString::findLast(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			Iterator possible = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					found = possible;
				}
			}
		}
	}
	return found;
}

QString::Iterator QString::findLast(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	Iterator found = end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			Iterator possible = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					found = possible;
				}
			}
		}
	}
	return found;
}

QString::Iterator QString::findnth(Character ch, size_t buffer, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	if (!buffer)
	{
		buffer = 1;
	}
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			if (!--buffer)
			{
				return i;
			}
		}
	}
	return end;
}

QString::Iterator QString::findnth(const Character* string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	if (!buffer)
	{
		buffer = 1;
	}
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			Iterator possible = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					if (!--buffer)
					{
						return possible;
					}
				}
			}
		}
	}
	return end;
}

QString::Iterator QString::findnth(const QString& string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	if (!buffer)
	{
		buffer = 1;
	}
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			Iterator possible = i;
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					if (!--buffer)
					{
						return possible;
					}
				}
			}
		}
	}
	return end;
}

QString::ReverseIterator QString::rfindnth(Character ch, size_t buffer, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	if (!buffer)
	{
		buffer = 1;
	}
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			if (!--buffer)
			{
				return i;
			}
		}
	}
	return end;
}

QString::ReverseIterator QString::rfindnth(const Character* string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	if (!buffer)
	{
		buffer = 1;
	}
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			ReverseIterator possible = i;
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (caseCheck(string[j], i.get()) && j == 0)
				{
					if (!--buffer)
					{
						return possible;
					}
				}
			}
		}
	}
	return end;
}

QString::ReverseIterator QString::rfindnth(const QString& string, size_t buffer, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	if (!buffer)
	{
		buffer = 1;
	}
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			ReverseIterator possible = i;
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (caseCheck(string[j], i.get()) && j == 0)
				{
					if (!--buffer)
					{
						return possible;
					}
				}
			}
		}
	}
	return end;
}

QBool QString::has(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			return true;
		}
	}
	return false;
}

QBool QString::has(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

QBool QString::has(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

QBool QString::rhas(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			return true;
		}
	}
	return false;
}

QBool QString::rhas(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (caseCheck(string[j], i.get()) && j == 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}

QBool QString::rhas(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	ReverseIterator begin = _rbegin;
	ReverseIterator end = _rend;
	for (ReverseIterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[len - 1], i.get()))
		{
			++i;
			for (size_t j = len - 2; caseCheck(string[j], i.get()); --j, ++i)
			{
				if (caseCheck(string[j], i.get()) && j == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

size_t QString::occurances(Character ch, Sensitivity sensitivity) const
{
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	size_t occurances = 0;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(ch, i.get()))
		{
			++occurances;
		}
	}
	return occurances;
}

size_t QString::occurances(const Character* string, Sensitivity sensitivity) const
{
	size_t len = Q_strLen(string);
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	size_t occurances = 0;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					++occurances;
				}
			}
		}
	}
	return occurances;
}

size_t QString::occurances(const QString& string, Sensitivity sensitivity) const
{
	size_t len = string.getLength();
	CaseChecker caseCheck = _getCase(sensitivity);
	Iterator begin = _begin;
	Iterator end = _end;
	size_t occurances = 0;
	for (Iterator i = begin; i < end; ++i)
	{
		if (caseCheck(string[0], i.get()))
		{
			++i;
			for (size_t j = 1; caseCheck(string[j], i.get()); ++j, ++i)
			{
				if (j == len - 1)
				{
					++occurances;
				}
			}
		}
	}
	return occurances;
}

QBool QString::is(CharacterFilter filter, CharacterFilter exception) const
{
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		if (!filter(i.get()) || !exception(i.get()))
		{
			return false;
		}
	}
	return true;
}

QBool QString::is(size_t index, CharacterFilter filter, CharacterFilter exception) const
{
	return _checkIndex(index) ? filter(_string[index]) || exception(_string[index]) : false;
}

QBool QString::is(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkIndicies(begin, end))
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin; i < trueEnd; ++i)
		{
			if (!filter(_string[i]) && !exception(_string[i]))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

QBool QString::is(Iterator iterator, CharacterFilter filter, CharacterFilter exception) const
{
	return _checkIterator(iterator) ? filter(iterator.get()) || exception(iterator.get()) : false;
}

QBool QString::is(Iterator begin, Iterator end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkIterators(begin, end))
	{
		Iterator trueEnd = end + 1;
		for (Iterator i = begin; i < trueEnd; ++i)
		{
			if (!filter(i.get()) && !exception(i.get()))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

QBool QString::ris(size_t index, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkNegativeIndex(index))
	{
		size_t pos = _negToPos(index);
		return filter(_string[pos]) || exception(_string[pos]);
	}
	return false;
}

QBool QString::ris(size_t begin, size_t end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkNegativeIndicies(begin, end))
	{
		size_t posBeg = _negToPos(begin);
		size_t posEnd = _negToPos(end);
		for (size_t i = posBeg; i < posEnd; ++i)
		{
			if (!filter(_string[i]) && !exception(_string[i]))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

QBool QString::ris(ReverseIterator iterator, CharacterFilter filter, CharacterFilter exception) const
{
	return _checkReverseIterator(iterator) ? filter(iterator.get()) || exception(iterator.get()) : false;
}

QBool QString::ris(ReverseIterator begin, ReverseIterator end, CharacterFilter filter, CharacterFilter exception) const
{
	if (_checkReverseIterators(begin, end))
	{
		ReverseIterator trueEnd = end + 1;
		for (ReverseIterator i = begin; i < trueEnd; ++i)
		{
			if (!filter(i.get()) || !exception(i.get()))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void QString::to(CharacterConverter converter, CharacterFilter filter)
{
	Iterator begin = _begin;
	Iterator end = _end;
	for (Iterator i = begin; i < end; ++i)
	{
		Character ch = i.get();
		if (!filter(ch))
		{
			ch = converter(ch);
			i.set(ch);
		}
	}
}

void QString::to(size_t index, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkIndex(index))
	{
		Character ch = _string[index];
		if (!filter(ch))
		{
			ch = converter(ch);
			_string[index] = ch;
		}
	}
}

void QString::to(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkIndicies(begin, end))
	{
		size_t trueEnd = end + 1;
		for (size_t i = begin; i < trueEnd; ++i)
		{
			Character ch = _string[i];
			if (!filter(ch))
			{
				ch = converter(ch);
				_string[i] = ch;
			}
		}
	}
}

void QString::to(Iterator iterator, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkIterator(iterator))
	{
		Character ch = iterator.get();
		if (!filter(ch))
		{
			ch = converter(ch);
			iterator.set(ch);
		}
	}
}

void QString::to(Iterator begin, Iterator end, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkIterators(begin, end))
	{
		Iterator trueEnd = end + 1;
		for (Iterator i = begin; i < trueEnd; ++i)
		{
			Character ch = i.get();
			if (!filter(ch))
			{
				ch = converter(ch);
				i.set(ch);
			}
		}
	}
}

void QString::rto(size_t index, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkNegativeIndex(index))
	{
		size_t i = _negToPos(index);
		Character ch = _string[i];
		if (!filter(ch))
		{
			_string[i] = converter(ch);
		}
	}
}

void QString::rto(size_t begin, size_t end, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkNegativeIndicies(begin, end))
	{
		size_t posBeg = _negToPos(begin);
		size_t trueEnd = _negToPos(end) + 1;
		for (size_t i = posBeg; i < trueEnd; ++i)
		{
			Character ch = _string[i];
			if (!filter(ch))
			{
				_string[i] = converter(ch);
			}
		}
	}
}

void QString::rto(ReverseIterator iterator, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkReverseIterator(iterator))
	{
		Character ch = iterator.get();
		if (!filter(ch))
		{
			ch = converter(ch);
			iterator.set(ch);
		}
	}
}

void QString::rto(ReverseIterator begin, ReverseIterator end, CharacterConverter converter, CharacterFilter filter)
{
	if (_checkReverseIterators(begin, end))
	{
		ReverseIterator trueEnd = end + 1;
		for (ReverseIterator i = begin; i < trueEnd; ++i)
		{
			Character ch = i.get();
			if (!filter(ch))
			{
				ch = converter(ch);
				i.set(ch);
			}
		}
	}
}

void QString::copy(const QString& string)
{

}

void QString::reserve(size_t size)
{
	if (size > _maxLength)
	{
		Character* string = new Character[size];
		Q_strCpy(_string, string, size);
		std::cout << string << std::endl;
		delete[] _string;
		_string = string;
		_maxLength = size;
	}
}

void QString::create(size_t length)
{
	if (!isInitialized())
	{
		_string = new Character[length];
		_length = length;
		_maxLength = length;

		if (_string)
		{
			_createIteratorFlags(0);
			_isInitialized = true;
		}
	}
}

void QString::create(const Character* string, size_t length)
{
	if (!isInitialized())
	{
		size_t len = length != 0 ? length : Q_strLen(string);
		_string = new Character[len];
		_length = len;
		_maxLength = len;
		Q_strCpy(string, _string, len);
		if (_string)
		{
			_createIteratorFlags(len);
			_isInitialized = true;
		}
	}
}

void QString::create(const QString& string)
{
	if (!isInitialized())
	{
		size_t len = string.getLength();
		size_t max = string.getMaxLength();
		_string = new Character[max];
		_length = len;
		_maxLength = max;
		Q_strCpy(string._string, _string, max);
		if (_string)
		{
			_createIteratorFlags(len);
			_isInitialized = true;
		}
	}
}

void QString::clear()
{
	if (isInitialized())
	{
		delete[] _string;
		_length = 0;
		_maxLength = 0;
		_begin = Iterator(nullptr);
		_end = Iterator(nullptr);
		_rbegin = ReverseIterator(nullptr);
		_rend = ReverseIterator(nullptr);
	}
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
	int32 value = 0;
	int32 sign = 1;
	Character ch = 0;
	Character* str = _string;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		str += 2;
		while (true)
		{
			ch = *str++;
			if (!Q_isNumeric(ch))
			{
				value = (value << 4) + ch - '0';
			}
			else if (Q_isHexU(ch))
			{
				value = (value << 4) + ch - 'A' + 10;
			}
			else if (Q_isHexL(ch))
			{
				value = (value << 4) + ch - 'a' + 10;
			}
			else
			{
				return sign * value;
			}
		}
	}

	if (str[0] == '\'')
	{
		return sign * str[1];
	}

	while (true)
	{
		ch = *str++;
		if (!Q_isNumeric(ch))
		{
			return sign * value;
		}
		value = value * 10 + ch - '0';
	}
	return 0;
}

float64 QString::toFloat64() const
{
	float64 value = 0;
	int sign = 1;
	char ch = 0;
	int decimal = -1;
	int total = 0;
	Character* str = _string;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		str += 2;
		while (true)
		{
			if (Q_isNumeric(ch))
			{
				value = (value * 16) + ch - '0';
			}
			else if (Q_isHexU(ch))
			{
				value = (value * 16) + ch - 'A' + 10;
			}
			else if (Q_isHexL(ch))
			{
				value = (value * 16) + ch - 'a' + 10;
			}
			else
			{
				return sign * value;
			}
		}
	}

	if (str[0] == '\'')
	{
		return sign * str[1];
	}

	while (true)
	{
		ch = *str++;
		if (ch == '.')
		{
			decimal = total;
			continue;
		}
		if (!Q_isNumeric(ch))
		{
			break;
		}
		value = (value * 10) + ch - '0';
		total++;
	}

	if (decimal == -1)
	{
		return sign * value;
	}

	while (total > decimal)
	{
		value /= 10;
		total--;
	}
	return sign * value;
}

cString QString::toCString() const
{
	return cString(_string, _length);
}

QString::Reference QString::at(size_t index) const
{
	if (_checkIndex(index))
	{
		return _string[index];
	}
	else if (_checkNegativeIndex(index))
	{
		size_t i = _negToPos(index);
		return _string[i];
	}
	else
	{
		return EMPTY_CHAR;
	}
}

QString::Reference QString::operator[](size_t index) const
{
	return at(index);
}

//QString QString::operator+(const char* string)
//{
//	/*size_t len = Q_strLen(string);
//	if (_length + len >= _maxLength)
//	{
//		size_t oldLen = _length;
//		Q_strDelete(_string, _maxLength);
//		_string = new char[oldLen + len];
//	}
//	for (size_t i = 0, j = _l; i < len; i++)
//	{
//
//	}*/
//	return EMPTY_STRING;
//}

const QString::Iterator QString::getBegin() const
{
	return *_begin;
}

const QString::Iterator QString::getEnd() const
{
	return *_end;
}

const QString::ReverseIterator QString::getRBegin() const
{
	return *_rbegin;
}

const QString::ReverseIterator QString::getREnd() const
{
	return *_rend;
}

QBool QString::isInitialized() const
{
	return _isInitialized;
}

size_t QString::getLength() const
{
	return _length;
}

size_t QString::getMaxLength() const
{
	return _maxLength;
}

size_t QString::getSize() const
{
	return _length;
}

size_t QString::getMaxSize() const
{
	return _maxLength;
}

void QString::_setLength(size_t len)
{
	_length = len;
}

QBool QString::_hasSpaceFor(size_t num) const
{
	return _length + num <= _maxLength;
}

QBool QString::_checkIndex(size_t index) const
{
	return (index < _length && index >= 0) || (_length == 0 && index == 0);
}

QBool QString::_checkIndicies(size_t begin, size_t end) const
{
	return _checkIndex(begin) && _checkIndex(end) && _comesBefore(begin, end);
}

QBool QString::_checkNegativeIndex(size_t index) const
{
	return index < 0 && index <= -_length && _length != 0;
}

QBool QString::_checkNegativeIndicies(size_t begin, size_t end) const
{
	return _checkNegativeIndex(begin) && _checkNegativeIndex(end) && _negComesBefore(begin, end);
}

size_t QString::_negToPos(size_t negative) const
{
	if (negative == -1)
	{
		return 0;
	}
	else if (negative == -_length)
	{
		return _length - 1;
	}
	else
	{
		return -negative;
	}
}

QBool QString::_negComesBefore(size_t begin, size_t end) const
{
	return begin > end;
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

void QString::_createIteratorFlags(size_t length)
{
	if (!isInitialized())
	{
		QBool isZero = length == 0;
		if (!isZero)
		{
			_begin = Iterator(_string[0]);
			_end = Iterator(_string[length]);
			_rbegin = ReverseIterator(_string[length - 1]);
			_rend = ReverseIterator(_string[-1]);
		}
		else
		{
			_begin = Iterator(_string[0]);
			_end = Iterator(_string[0]);
			_rbegin = ReverseIterator(_string[0]);
			_rend = ReverseIterator(_string[-1]);
		}
	}
}

void QString::_adjustEnd(size_t num)
{
	_end += num;
	_rbegin += num;
}

QString::CaseChecker QString::_getCase(Sensitivity sensitivity) const
{
	return isSensitive(sensitivity) ? CaseChecker(Q_chrCmp) : CaseChecker(Q_chrCaseCmp);
}

void QString::_incrementLength()
{
	_length++;
}

void QString::_decrementLength()
{
	_length--;
}

std::ostream& operator<<(std::ostream& os, const QString& string)
{
	for (size_t i = 0; i < string.getLength(); i++)
	{
		os << string[i];
	}
	return os;
}