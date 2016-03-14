#pragma once

#include <iostream>

#include "base.hpp"

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

#define DEFAULT_STRING_SIZE		32

template<typename TAllocator = PoolAllocator<char>>
class QString
	: public QAuxiliary<char, TAllocator>
{
public:
	typedef Value Character;

	QString(size_t length = DEFAULT_STRING_SIZE);
	QString(const char* string);
	QString(char* string);
	QString(const QString& string);

	~QString() {};

	void pushFront();
	void setFront();
	ConstReference getFront() const;

	void pushBack();
	void setBack();
	ConstReference getBack() const;

	void insert(size_t index, Character ch);
	void append(size_t index, Character ch);

	void reserve(size_t size);
	void clear(size_t index);
	void clear();
	bool isEmpty() const;
	bool isFull() const;
	void pack();
	void swap(QString& other);
	bool owns(Character ch);

	size_t getLength() const;
	size_t getMaxLength() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
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

	void _copy(const char* src, char* dest, size_t buffer);

	/*Raw string*/
	char* _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	Allocator _allocator;
};

#include "..\Source\qstring.inl"