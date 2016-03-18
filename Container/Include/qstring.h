#pragma once

#include <iostream>

#include "base.hpp"
#include "..\..\Auxiliary\Include\string_aux.h"
#include "..\..\Math\Include\math.h"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

#define DEFAULT_STRING_SIZE		32
#define EMPTY_STRING QString((size_t)0);

enum STRING_SEARCH_CASE_SENSITIVITY
{
	SENSITIVE = 0,
	UNSENSITIVE = 1
};

enum STRING_SEARCH_STARTING_POINT
{
	BEGINNING = 0,
	ENDING = 1
};

typedef STRING_SEARCH_CASE_SENSITIVITY Sensitivity;
typedef STRING_SEARCH_STARTING_POINT Start;

QBool startBeginning(Start start);
QBool startEnding(Start start);

QBool isSensitive(Sensitivity sensitivity);
QBool isUnsensitivity(Sensitivity sensitivity);

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

	size_t find(Character ch, Sensitivity sensitivty = UNSENSITIVE, Start start = BEGINNING);
	size_t findLast(Character ch, Sensitivity sensitivity = UNSENSITIVE, Start start = BEGINNING);
	QBool has(Character ch, Sensitivity sensitivity = UNSENSITIVE, Start start = BEGINNING);

	QString toUpper() const;
	void setUpper();
	void setUpper(size_t index);
	void setUpper(size_t begin, size_t end);

	QString toLower() const;
	void setLower();
	void setLower(size_t index);
	void setLower(size_t begin, size_t end);

	void copy(const QString& string);

	void reserve(size_t size);
	void clear(size_t index);
	void clear();
	bool isEmpty() const;
	bool isFull() const;
	void pack();
	void swap(QString& other);

	Reference at(size_t index) const;
	QString at(size_t begin, size_t end) const;
	Reference operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const QString& string);

	size_t getLength() const;
	size_t getMaxLength() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
	void _setLength(size_t len);

	QBool _checkIndex(size_t index) const;

	void _incrementLength();
	void _decrementLength();

	/*Raw string*/
	String _string;
	/*String length*/
	size_t _length;
	/*Maximum length*/
	size_t _maxLength;
	/*Memory Allocator*/
	//Allocator _allocator;
};