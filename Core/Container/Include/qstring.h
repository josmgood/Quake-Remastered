#pragma once

/*Standard Library*/
#include <iostream>
#include <string.h>

class QString
{
public:
	QString(void);
	QString(const QString& string);
	QString(const char* string);
	QString(char* string);
	~QString(void);

	bool toBool(void) const;
	int toInt(void) const;

	void concat(QString string, size_t index);
	void concat(const char* string, size_t index);
	void concat(char* string, size_t index);

	void append(size_t prev, const QString& string);
	void append(size_t prev, const char* string);
	void append(size_t prev, char* string);

	void insert(size_t next, const QString& string);
	void insert(size_t next, const char* string);
	void insert(size_t next, char* string);

	size_t find(const QString& string);
	size_t find(const char* string);
	size_t find(char* string);
	size_t find(char ch);

	void reserve(size_t amount);
	void resize(size_t newSize);
	void clear(void);
	bool isEmpty(void) const;

	size_t getLength(void) const;
	size_t getLastIndex(void) const;
	const char* getCString(void) const;

	char operator[](size_t index);
	QString& operator+(const QString& string);
	QString& operator+(const char* string);
	QString& operator+(char* string);

	std::ostream& operator<<(std::ostream& os);
	operator bool(void) const;

private:
	enum SEARCH_CASE_SENSITIVITY
	{
		//-- Characters must have exact casing --//
		SENSITIVE,
		//-- Character casing is irrelevant --//
		UNSENSITIVE
	};
	enum SEARCH_STARTING_POINT
	{
		//-- Start searching the string at the beginning (forward) --//
		BEGINNING,
		//-- Start Searching the string at the end (backward) --//
		END
	};

	//-- Raw String --//
	char*		_string;
	size_t		_length;
};