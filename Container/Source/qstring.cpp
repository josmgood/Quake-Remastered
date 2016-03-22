#include "..\Include\qstring.h"

QBool isForward(Direction dir)
{
	return dir == STR_FORWARD;
}

QBool isBackward(Direction dir)
{
	return dir == STR_BACKWARD;
}

QBool isSensitive(Sensitivity sensitivity)
{
	return sensitivity == STR_SENSITIVE;
}

QBool isUnsensitivity(Sensitivity sensitivity)
{
	return sensitivity == STR_UNSENSITIVE;
}

QString::QString(size_t length)
	: _maxLength(length), _length()
{
	//_string = _allocator.allocate(sizeof(Character) * length);
	_string = new char[length];
}

QString::QString(const char* string)
	: _maxLength(), _length()
{
	size_t len = Q_strLen(string);
	_maxLength = len;
	_length = len;
	_string = new char[len];
	Q_strCpy(string, _string, len);
}

QString::QString(const QString& string)
	: _maxLength(string._maxLength), _length(string._length)
{
	_string = new char[_length];
	Q_strCpy(string._string, _string, _length);
}

QString::~QString()
{
	delete[] _string;
}

void QString::pushFront(Character ch)
{
	if (_length + 1 <= _maxLength)
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
	}
}

//void QString::setFront(Character ch)
//{
//	if (_length > 0)
//	{
//		_string[0] = ch;
//	}
//}
//
//QString::ConstReference QString::getFront() const
//{
//	return _string[0];
//}
//
//void QString::pushBack(Character ch)
//{
//	if (_length + 1 <= _maxLength)
//	{
//		_string[_length] = ch;
//		_incrementLength();
//	}
//}
//
//void QString::setBack(Character ch)
//{
//	if (_length - 1 >= 0)
//	{
//		_string[_length - 1] = ch;
//	}
//}
//
//QString::ConstReference QString::getBack() const
//{
//	return _string[_length - 1];
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
//void QString::set(size_t begin, size_t end, const char* string)
//{
//	if (_checkIndicies(begin, end))
//	{
//		//for (size_t i = begin; _interationCheck(begin, end); i)
//	}
//}
//
//QString QString::substring(size_t begin)
//{
//	if (begin <= _length)
//	{
//		size_t len = _length - begin - 1;
//		QString string(len);
//		string._length = len;
//		Index start = _string + begin + 1;
//		Q_strCpy(start, string._string);
//		return string;
//	}
//	return EMPTY_STRING;
//}
//
////size_t QString::find(Character ch, Sensitivity sensitivty, Direction dir) const
////{
////	_IterationAttribs attribs(dir, _length);
////	QBool sensitive = isSensitive(sensitivty);
////	size_t begin = attribs.begin;
////	size_t end = attribs.end;
////	size_t increment = attribs.increment;
////	for (size_t i = begin; _interationCheck(i, end, dir); i += increment)
////	{
////		if (!sensitive)
////		{
////			if (Q_chrCaseCmp(ch, _string[i]))
////			{
////				return i;
////			}
////		}
////		else
////		{
////			if (Q_chrCmp(ch, _string[i]))
////			{
////				return i;
////			}
////		}
////	}
////	return BAD_INDEX;
////}
//
//QString::Iterator QString::find(Character ch, Sensitivity sensitivity, Direction dir) const
//{
//	return Iterator();
//}
//
//size_t QString::findLast(Character ch, Sensitivity sensitivity, Direction dir) const
//{
//	_IterationAttribs attribs(dir, _length);
//	QBool sensitive = isSensitive(sensitivity);
//	size_t begin = attribs.begin;
//	size_t end = attribs.end;
//	size_t increment = attribs.increment;
//	size_t last = BAD_INDEX;
//	for (size_t i = begin; _interationCheck(i, end, dir); i += increment)
//	{
//		if (!sensitive)
//		{
//			if (Q_chrCaseCmp(ch, _string[i]))
//			{
//				last = i;
//			}
//		}
//		else
//		{
//			if (Q_chrCmp(ch, _string[i]))
//			{
//				last = i;
//			}
//		}
//	}
//	return last;
//}
//
//QBool QString::has(Character ch, Sensitivity sensitivity, Direction dir) const
//{
//	_IterationAttribs attribs(dir, _length);
//	QBool sensitive = isSensitive(sensitivity);
//	size_t begin = attribs.begin;
//	size_t end = attribs.end;
//	size_t increment = attribs.increment;
//	for (size_t i = begin; _interationCheck(i, end, dir); i += increment)
//	{
//		if (!sensitive)
//		{
//			if (Q_chrCaseCmp(ch, _string[i]))
//			{
//				return true;
//			}
//		}
//		else
//		{
//			if (Q_chrCmp(ch, _string[i]))
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}
//
//QBool QString::isAlpha() const
//{
//	size_t length = _length - 1;
//	for (size_t i = 0; i < length; i++)
//	{
//		if (!Q_isAlpha(_string[i]))
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//QBool QString::isAlpha(size_t index) const
//{
//	return _checkIndex(index) ? Q_isAlpha(_string[index]) : false;
//}
//
//QBool QString::isAlpha(size_t begin, size_t end) const
//{
//	if (_checkIndicies(begin, end))
//	{
//		for (size_t i = 0; i <= end; i++)
//		{
//			std::cout << i << std::endl;
//			if (!Q_isAlpha(_string[i]))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//
//QBool QString::isNumeric() const
//{
//	size_t length = _length - 1;
//	for (size_t i = 0; i < length; i++)
//	{
//		if (!Q_isNumeric(_string[i]))
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//QBool QString::isNumeric(size_t index) const
//{
//	return _checkIndex(index) ? Q_isNumeric(_string[index]) : false;
//}
//
//QBool QString::isNumeric(size_t begin, size_t end) const 
//{
//	if (_checkIndicies(begin, end))
//	{
//		for (size_t i = 0; i <= end; i++)
//		{
//			if (!Q_isNumeric(_string[i]))
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
//
//QString QString::toUpper() const
//{
//	QString upper(_length);
//	upper._length = _length;
//	for (size_t i = 0; i < _length; i++)
//	{
//		std::cout << i << std::endl;
//		upper[i] = toupper(_string[i]);
//	}
//	return upper;
//}
//
//void QString::setUpper()
//{
//	for (size_t i = 0; i < _length; i++)
//	{
//		Character upper = toupper(_string[i]);
//		_string[i] = upper;
//	}
//}
//
//void QString::setUpper(size_t index)
//{
//	Character ch = at(index);
//	if (!isEmptyChar(ch))
//	{
//		_string[index] = toupper(ch);
//	}
//}
//
//void QString::setUpper(size_t begin, size_t end)
//{
//	if (_checkIndicies(begin, end))
//	{
//		for (size_t i = begin; i < end + 1; i++)
//		{
//			Character upper = toupper(_string[i]);
//			_string[i] = upper;
//		}
//	}
//}
//
//QString QString::toLower() const
//{
//	QString lower(_length);
//	lower._length = _length;
//	for (size_t i = 0; i < _length; i++)
//	{
//		lower[i] = tolower(_string[i]);
//	}
//	return lower;
//}
//
//void QString::setLower()
//{
//	for (size_t i = 0; i < _length; i++)
//	{
//		Character lower = tolower(_string[i]);
//		_string[i] = lower;
//	}
//}
//
//void QString::setLower(size_t index)
//{
//	Character ch = at(index);
//	if (!isEmptyChar(ch))
//	{
//		_string[index] = tolower(ch);
//	}
//}
//
//void QString::setLower(size_t begin, size_t end)
//{
//	if (_checkIndicies(begin, end))
//	{
//		for (size_t i = begin; i < end + 1; i++)
//		{
//			Character lower = tolower(_string[i]);
//			_string[i] = lower;
//		}
//	}
//}
//
//void QString::copy(const QString& string)
//{
//	/*size_t maxLength = (_maxLength < string._maxLength) ? string._maxLength : _maxLength;
//	if (_length < maxLength)
//	{
//		delete[] _string;
//		_string = new char[maxLength];
//	}
//	Q_strCpy(string._string, _string, maxLength);*/
//}
//
//void QString::clear(size_t index)
//{
//	if (_checkIndex(index))
//	{
//		_string[index] = EMPTY_CHAR;
//	}
//}
//
//void QString::clear(size_t begin, size_t end)
//{
//	if (_checkIndicies(begin, end))
//	{
//		for (size_t i = begin; i != end; i++)
//		{
//			_string[i] = EMPTY_CHAR;
//		}
//	}
//}
//
//void QString::clear()
//{
//	for (size_t i = 0; i < _length; i++)
//	{
//		_string[i] = EMPTY_CHAR;
//	}
//	_length = 0;
//}
//
//QBool QString::isEmpty() const
//{
//	return !_length;
//}
//
//QBool QString::isFull() const
//{
//	return _length;
//}
//
//void QString::pack()
//{
//	/*size_t length = _length;
//	for (size_t i = 0; i < length; i++)
//	{
//		Character current = _string[i];
//		Character next = (_checkIndex(i + 1)) ? _string[i + 1] : EMPTY_CHAR;
//		if (isEmptyChar(current) && !isEmptyChar(next))
//		{
//			current = next;
//		}
//	}*/
//}

QString::Reference QString::at(size_t index) const
{
	return _checkIndex(index) ? _string[index] : EMPTY_CHAR;
}

//QString QString::at(size_t begin, size_t end) const
//{
//	if (_checkIndicies(begin, end))
//	{
//		size_t subLen = (end - begin != 0) ? end - begin : 1;
//		QString string(subLen);
//		for (size_t i = 0; i < subLen; i++)
//		{
//			string[i] = _string[i];
//		}
//		return string;
//	}
//	return EMPTY_STRING;
//}

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
	return Iterator(_string[0]);
}

const QString::Iterator QString::getEnd() const
{
	return Iterator(_string[_length]);
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

QBool QString::_checkIndex(size_t index) const
{
	return index <= _length - 1 && index >= 0;
}

//QBool QString::_checkIndicies(size_t begin, size_t end) const
//{
//	return _checkIndex(begin) && _checkIndex(end) && _comesBefore(begin, end);
//}
//
//QBool QString::_comesBefore(size_t begin, size_t end) const
//{
//	return begin <= end;
//}
//
//QBool QString::_interationCheck(size_t index, size_t end, Direction dir) const
//{
//	if (isForward(dir))
//	{
//		return index < end;
//	}
//	else if (isBackward(dir))
//	{
//		return index >= end;
//	}
//}

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