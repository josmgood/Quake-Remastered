#pragma once

#include <iostream>
#include <string>

class QBool
{
public:
	QBool(bool b = false);

	void setTrue();
	void setFalse();
	void set(bool bl);
	bool get() const;

	bool isTrue() const;
	bool isFalse() const;

	operator bool() const;
	void operator=(bool b);
	//bool operator==(const QBool& qbool) const;
	bool operator!=(const QBool& qbool) const;
	bool operator<(const QBool& qbool) const;
	bool operator>(const QBool& qbool) const;
	std::ostream& operator<<(std::ostream& os);

	std::string toString();
private:
	bool _bool;
};