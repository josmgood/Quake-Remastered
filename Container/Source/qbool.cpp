#include "..\Include\qbool.h"

QBool::QBool(bool b)
	: _bool(b)
{
}

void QBool::setTrue()
{
	_bool = true;
}

void QBool::setFalse()
{
	_bool = false;
}

void QBool::set(bool b)
{
	_bool = b;
}

bool QBool::get() const
{
	return(_bool);
}

bool QBool::isTrue() const
{
	return(_bool == true);
}

bool QBool::isFalse() const
{
	return(_bool == false);
}

QBool::operator bool() const
{
	return(_bool);
}

void QBool::operator=(bool b)
{
	_bool = b;
}

//bool QBool::operator==(const QBool& qbool) const
//{
//	return(_bool == qbool._bool);
//}

bool QBool::operator!=(const QBool& qbool) const
{
	return(_bool != qbool._bool);
}

bool QBool::operator<(const QBool& qbool) const
{
	return(_bool < qbool._bool);
}

bool QBool::operator>(const QBool& qbool) const
{
	return(_bool > qbool._bool);
}

std::ostream& QBool::operator<<(std::ostream& os)
{
	return os << _bool;
}

std::string QBool::toString()
{
	switch (_bool)
	{
	case true:
		return("True");
	case false:
		return("False");
	}
}