#pragma once

#include <iostream>

#include "base.hpp"
#include "..\..\Auxiliary\Include\string_aux.h"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

#define DEFAULT_STRING_SIZE		32
#define EMPTY_STRING QString(0);

static char EMPTY_CHAR = ' ';

class QString
	: public QAuxiliary<char, int>
{
public:
	typedef Value Character;
	typedef Pointer Index;
	typedef Pointer String;

	QString(size_t length = DEFAULT_STRING_SIZE);
	QString(const char* string);
	QString(char* string);
	QString(const QString& string);

	~QString() {};

	void pushFront(Character ch);
	void setFront(Character ch);
	ConstReference getFront() const;

	void pushBack(Character ch);
	void setBack(Character ch);
	ConstReference getBack() const;

	void insert(size_t index, Character ch);
	void append(size_t index, Character ch);

	QString substring(size_t begin);
	QString substring(size_t begin, size_t end);
	//QString substring();

	size_t find(Character ch);
	size_t findLast(Character ch);

	QString toLower() const;
	QString toUpper() const;

	void copy(const QString& string);

	void reserve(size_t size);
	void clear(size_t index);
	void clear();
	bool isEmpty() const;
	bool isFull() const;
	void pack();
	void swap(QString& other);
	bool owns(Character ch);

	Reference at(size_t index) const;
	Reference operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const QString& string);

	size_t getLength() const;
	size_t getMaxLength() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
	void _setLength(size_t len);

	void _incrementLength();
	void _decrementLength();

	enum SEARCH_CASE_SENSITIVITY
	{
		/*Characters must have exact casing*/
		SENSITIVE,
		/*Character casing is irrelevant.*/
		UNSENSITIVE
	};
	enum SEARCH_STARTING_POINT
	{
		/*Start searching the string at the beginning (forward)*/
		BEGINNING,
		/*Start searching the string at the end (backward)*/
		END
	};

	/*Raw string*/
	String _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	//Allocator _allocator;
};