#pragma once

#include <iostream>

#include "iterator.hpp"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

template<typename Type,
	typename TAllocator = PoolAllocator<Type>>
class QArray
	: public QAuxiliary<Type, TAllocator>
{
public:
	typedef Pointer Array;
	typedef Value Index;
	//typedef QArray<Type, TAllocator> QArray;
	typedef BidirectionalArrayIterator<Type> Iterator;
	typedef BidirectionalArrayIterator<const Type> ConstIterator;
	typedef ReverseArrayIterator<Type> ReverseIterator;
	typedef ReverseArrayIterator<const Type> ConstReverseIterator;

	/*inline QArray(size_t maxSize = DEFAULT_CONTAINER_SIZE, ConstReference initial = Value());
	inline ~QArray();

	inline void pushFront(ConstReference value);
	inline void setFront(ConstReference value);
	inline void popFront();

	inline void pushBack(ConstReference value);
	inline void setBack(ConstReference value);
	inline void popBack();

	inline void set(size_t index, ConstReference value);
	inline void set(size_t begin, size_t end, const QArray& value);
	inline void set(Iterator iterator, ConstReference value) const;
	inline void set(Iterator begin, Iterator end, const QArray& value) const;

	inline QArray subarray(size_t index) const;
	inline QArray subarray(size_t begin, size_t end) const;
	inline QArray subarray(Iterator iterator) const;
	inline QArray subarray(Iterator begin, Iterator end) const;

	inline Iterator find(ConstReference value) const;
	inline Iterator find(const Array& subarray) const;
	inline Iterator find(const QArray& subarray) const;

	inline Iterator findnth(ConstReference value, size_t buffer) const;
	inline Iterator findnth(const Array subarray, size_t buffer) const;
	inline Iterator findnth(const QArray& subarray, size_t buffer) const;

	inline Iterator findLast(ConstRefernce value) const;
	inline Iterator findLast(const Array& subarray) const;
	inline Iterator findLast(const QArray& subarray) const;

	inline ReverseIterator rfind(ConstReference value) const;
	inline ReverseIterator rfind(const Array subarray) const;
	inline ReverseIterator rfind(const QArray& subarray) const;

	inline QBool has(ConstReference value) const;
	inline QBool has(const Array& subarray) const;
	inline QBool has(const QArray& subarray) const;

	inline size_t occurances(ConstReference value) const;
	inline size_t occurances(const Array& subarray) const;
	inline size_t occurances(const QArray& subarray) const;

	void create(size_t maxSize);
	void create(const Array subarray);
	void create(const QArray& subarray);
	void clear();

	QBool isEmpty() const;
	QBool isFull() const;
	void pack();
	void swap(QArray& other);

	Reference at(size_t index) const;
	Reference operator[](size_t index) const;

	void operator=(const Array& other);
	void operator=(const QArray& other);
	
	QBool operator==(const Array& other) const;
	QBool operator!=(const Array& other) const;
	QBool operator<(const Array& other) const;
	QBool operator<=(const Array& other) const;
	QBool operator>(const Array& other) const;
	QBool operator>=(const Array& other) const;

	QBool operator==(const QArray& other) const;
	QBool operator!=(const QArray& other) const;
	QBool operator<(const QArray& other) const;
	QBool operator<=(const QArray& other) const;
	QBool operator>(const QArray& other) const;
	QBool operator>=(const QArray& other) const;

	friend std::operator<<(std::ostream& os, const QArray& qarray);

	const Iterator getBegin() const;
	const Iterator getEnd() const;
	const Iterator getRBegin() const;
	const Iterator getREnd() const;

	QBool isInitialized() const;
	size_t getSize() const;
	size_t getMaxSize() const;
private:
	void _setSize(size_t size);
	void _addSize(size_t amount);
	void _subtractSize(size_t amount);

	QBool _hasSpaceFor(size_t num) const;
	
	QBool _checkIndex(size_t index) const;
	Qbool _checkIndicies(size_t begin, size_t end) const;

	size_t _negToPos(size_t )

	Array _array;
	size_t _size;
	size_t _maxSize;
	size_t _back;*/
};

#include "..\Source\qarray.inl"