#include "..\Include\qstring.h"

QBool startBeginning(Start start)
{
	return start == STRING_SEARCH_STARTING_POINT::BEGINNING;
}

QBool startEnding(Start start)
{
	return start == STRING_SEARCH_STARTING_POINT::ENDING;
}

QBool isSensitive(Sensitivity sensitivity)
{
	return sensitivity == STRING_SEARCH_CASE_SENSITIVITY::SENSITIVE;
}

QBool isUnsensitivity(Sensitivity sensitivity)
{
	return sensitivity == STRING_SEARCH_CASE_SENSITIVITY::UNSENSITIVE;
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
	size_t len = qStrLen(string);
	_maxLength = len;
	_length = len;
	_string = new char[len];
	qStrCpy(string, _string, len);
}

QString::QString(char* string)
	: _maxLength(), _length()
{
	size_t len = qStrLen(string);
	_maxLength = len;
	_length = len;
	_string = new char[len];
	qStrCpy(string, _string, len);
}

QString::QString(const QString& string)
	: _maxLength(string._maxLength), _length(string._length)
{
	_string = new char[_length];
	qStrCpy(string._string, _string, _length);
}

void QString::pushFront(Character ch)
{
	if (_length + 1 <= _maxLength)
	{
		Character last = _string[0];
		_string[0] = ch;
		for (size_t i = 1; i < _length; i++)
		{
			Character tmp = _string[i];
			_string[i] = last;
			last = tmp;
		}
		_incrementLength();
	}
}

void QString::setFront(Character ch)
{
	if (_length > 0)
	{
		_string[0] = ch;
	}
}

QString::ConstReference QString::getFront() const
{
	return _string[0];
}

void QString::pushBack(Character ch)
{
	if (_length + 1 <= _maxLength)
	{
		_string[_length] = ch;
		_incrementLength();
	}
}

void QString::setBack(Character ch)
{
	if (_length - 1 >= 0)
	{
		_string[_length - 1] = ch;
	}
}

QString::ConstReference QString::getBack() const
{
	return _string[_length - 1];
}


QString QString::substring(size_t begin)
{
	if (begin <= _length)
	{
		size_t len = _length - begin;
		QString string(len);
		string._length = len;
		Index start = _string + begin;
		qStrCpy(start, string._string);
		return string;
	}
	return EMPTY_STRING;
}

size_t QString::find(Character ch, Sensitivity sensitivity, Start start)
{
	return 0;
}

QBool QString::has(Character ch, Sensitivity sensitivity, Start start)
{
	size_t begin = (startBeginning(start)) ? 0 : _length - 1;
	size_t end = (startBeginning(start)) ? _length - 1 : 0;
	QBool sensitive = isSensitive(sensitivity);
	for (size_t i = begin; i != end; i++)
	{
		if (sensitive)
		{
			if (qChrCaseCmp(ch, _string[i]))
			{
				return true;
			}
		}
		else
		{

		}
	}
	return false;
}

QString QString::toUpper() const
{
	QString upper(_length);
	upper._length = _length;
	for (size_t i = 0; i < _length; i++)
	{
		upper[i] = toupper(_string[i]);
	}
	return upper;
}

void QString::setUpper()
{
	for (size_t i = 0; i < _length; i++)
	{
		Character upper = toupper(_string[i]);
		_string[i] = upper;
	}
}

void QString::setUpper(size_t index)
{
	Character ch = at(index);
	if (!isEmptyChar(ch))
	{
		_string[index] = toupper(ch);
	}
}

void QString::setUpper(size_t begin, size_t end)
{
	QBool begCheck = _checkIndex(begin);
	QBool endCheck = _checkIndex(end);
	if (begCheck && endCheck)
	{
		for (size_t i = begin; i < end + 1; i++)
		{
			Character upper = toupper(_string[i]);
			_string[i] = upper;
		}
	}
}

QString QString::toLower() const
{
	QString lower(_length);
	lower._length = _length;
	for (size_t i = 0; i < _length; i++)
	{
		lower[i] = tolower(_string[i]);
	}
	return lower;
}

void QString::setLower()
{
	for (size_t i = 0; i < _length; i++)
	{
		Character lower = tolower(_string[i]);
		_string[i] = lower;
	}
}

void QString::setLower(size_t index)
{
	Character ch = at(index);
	if (!isEmptyChar(ch))
	{
		_string[index] = tolower(ch);
	}
}

void QString::setLower(size_t begin, size_t end)
{
	QBool begCheck = _checkIndex(begin);
	QBool endCheck = _checkIndex(end);
	if (begCheck && endCheck)
	{
		for (size_t i = begin; i < end + 1; i++)
		{
			Character lower = tolower(_string[i]);
			_string[i] = lower;
		}
	}
}

char& QString::at(size_t index) const
{
	return _checkIndex(index) ? _string[index] : EMPTY_CHAR;
}

QString QString::at(size_t begin, size_t end) const
{
	QBool begCheck = _checkIndex(begin);
	QBool endCheck = _checkIndex(end);
	if (begCheck && endCheck)
	{
		size_t subLen = (end - begin != 0) ? end - begin : 1;
		QString string(subLen);
		for (size_t i = 0; i < subLen; i++)
		{
			string[i] = _string[i];
		}
		return string;
	}
	return EMPTY_STRING;
}

QString::Reference QString::operator[](size_t index) const
{
	return at(index);
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