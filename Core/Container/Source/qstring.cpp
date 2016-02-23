#include "..\Include\qstring.h"

QString::QString(void)
	: _string(nullptr), _length(0)
{
}

QString::QString(const QString& string)
	: _string(string._string), _length(string._length)
{
}

//QString::QString(const char* string)
//	: _string(string), _length(strlen(string))
//{
//}

QString::QString(char* string)
	: _string(string), _length(strlen(string))
{
}

QString::~QString(void)
{
	//clear();
}