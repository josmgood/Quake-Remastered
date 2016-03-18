#include "..\Include\qstring.h"

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

}

char& QString::at(size_t index) const
{
	return (index <= _length - 1) ? _string[index] : EMPTY_CHAR;
}

QString::Reference QString::operator[](size_t index) const
{
	return at(index);
}

void QString::_setLength(size_t len)
{
	_length = len;
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
	return os << string._string;
}