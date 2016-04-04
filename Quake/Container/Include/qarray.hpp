//#pragma once
//
//#include <iostream>
//
//#include "base.hpp"
//#include "iterator.hpp"
//#include "ccontainers.h"
//
//#include "..\..\Auxiliary\Include\algorithm.h"
//
//#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"
//#include "..\..\Memory\Include\Allocator\mallocator.h"
//
//template<typename Type,
//	typename TAllocator>
//class QArray;
//
//template<typename Type,
//	typename TAllocator>
//std::ostream& operator<<(std::ostream&, const QArray<Type, TAllocator>&);
//
//template<typename Type,
//	typename TAllocator = MAllocator>
//class QArray
//	: public QAuxiliary<Type, TAllocator>
//{
//public:
//	typedef Pointer Array;
//	typedef Pointer Index;
//
//	typedef CArray<Type> C_Array;
//	typedef BidirectionalArrayIterator<Type> Iterator;
//	typedef BidirectionalArrayIterator<const Type> ConstIterator;
//	typedef ReverseArrayIterator<Type> ReverseIterator;
//	typedef ReverseArrayIterator<const Type> ConstReverseIterator;
//
//	QArray(size_t maxSize = DEFAULT_CONTAINER_SIZE, ConstReference initial = Value());
//	QArray(const Iterator begin, const Iterator end);
//	QArray(const C_Array& carray);
//	QArray(const Container& container);
//	
//	void replaceFront(ConstReference reference);
//	void replaceFront(const C_Array& carray);
//	void replaceFront(const Container& container);
//	void pushFront(ConstReference reference);
//	void pushFront(const C_Array& carray);
//	void pushFront(const Container& container);
//	void pushFront(const Iterator begin, const Iterator end);
//	Reference getFront() const;
//
//	void replaceBack(ConstReference reference);
//	void replaceBack(const C_Array& carray);
//	void replaceBack(const Container& container);
//	void pushBack(ConstReference reference);
//	void pushBack(const C_Array& carray);
//	void pushBack(const Container& container);
//	void pushBack(const Iterator begin, const Iterator end);
//	Reference getBack() const;
//
//	void insert(size_t index, ConstReference reference);
//	void insert(const Iterator iterator, ConstReference reference);
//	void insert(size_t index, const C_Array& carray);
//	void insert(const Iterator iterator, const C_Array& carray);
//	void insert(size_t index, const Container& container);
//	void insert(const Iterator iterator, const Container& container);
//
//	void append(size_t index, ConstReference reference);
//	void append(const Iterator iterator, ConstReference reference);
//	void append(size_t index, const C_Array& carray);
//	void append(const Iterator iterator, const C_Array& carray);
//	void append(size_t index, const Container& container);
//	void append(const Iterator iterator, const Container& container);
//
//	void fill(ConstReference reference);
//
//	void replace(size_t index, ConstReference reference);
//	void replace(Iterator iterator, ConstReference reference);
//	void replace(size_t begin, size_t end, const C_Array& carray);
//	void replace(Iterator begin, Iterator end, const C_Array& carray);
//	void replace(size_t begin, size_t end, const Container& container);
//	void replace(Iterator begin, Iterator end, const Container& container);
//
//	QArray subarray(size_t begin) const;
//	QArray subarray(size_t begin, size_t end) const;
//	QArray subarray(const Iterator begin) const;
//	QArray subarray(const Iterator begin, const Iterator end) const;
//
//	Iterator find(ConstReference reference, size_t buffer = 1) const;
//	Iterator find(size_t begin, ConstReference reference, size_t buffer = 1) const;
//	Iterator find(size_t begin, size_t end, ConstReference reference, size_t buffer = 1) const;
//	Iterator find(const Iterator begin, ConstReference reference, size_t buffer = 1) const;
//	Iterator find(const Iterator begin, const Iterator end, ConstReference reference, size_t buffer = 1) const;
//
//	Iterator find(const C_Array& carray, size_t buffer = 1) const;
//	Iterator find(size_t begin, C_Array& carray, size_t buffer = 1) const;
//	Iterator find(size_t begin, size_t end, C_Array& carray, size_t buffer = 1) const;
//	Iterator find(const Iterator begin, const C_Array& carray, size_t buffer = 1) const;
//	Iterator find(Iterator begin, Iterator end, const C_Array& carray, size_t buffer = 1) const;
//
//	Iterator find(const Container& container, size_t buffer = 1) const;
//	Iterator find(size_t begin, const Container& container, size_t buffer = 1) const;
//	Iterator find(size_t begin, size_t end, const Container& container, size_t buffer = 1) const;
//	Iterator find(Iterator begin, const Container& container, size_t buffer = 1) const;
//	Iterator find(Iterator begin, Iterator end, const Container& container, size_t buffer = 1) const;
//
//	ReverseIterator rfind(ConstReference reference, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, ConstReference reference, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, const ReverseIterator end, ConstReference reference, size_t buffer = 1);
//
//	ReverseIterator rfind(const C_Array& carray, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, const C_Array& carray, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, const ReverseIterator end, const C_Array& carray, size_t buffer = 1) const;
//
//	ReverseIterator rfind(const Container& container, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, const Container& container, size_t buffer = 1) const;
//	ReverseIterator rfind(const ReverseIterator begin, const ReverseIterator end, const Container& container, size_t buffer = 1) const;
//
//	Iterator findLast(ConstReference reference) const;
//	Iterator findLast(size_t begin, ConstReference reference) const;
//	Iterator findLast(size_t begin, size_t end, ConstReference reference) const;
//	Iterator findLast(const Iterator begin, ConstReference reference) const;
//	Iterator findLast(const Iterator begin, const Iterator end, ConstReference reference) const;
//
//	Iterator findLast(const C_Array& carray) const;
//	Iterator findLast(size_t begin, const C_Array& carray) const;
//	Iterator findLast(size_t begin, size_t end, const C_Array carray) const;
//	Iterator findLast(const Iterator begin, const C_Array& carray) const;
//	Iterator findLast(const Iterator begin, const Iterator end, const C_Array& carray) const;
//
//	Iterator findLast(const Container& array) const;
//	Iterator findLast(size_t begin, const Container& container) const;
//	Iterator findLast(size_t begin, size_t end, const Container& container) const;
//	Iterator findLast(const Iterator begin, const Container& container) const;
//	Iterator findLast(const Iterator begin, const Iterator end, const Container& container) const;
//
//	QBool has(ConstReference reference) const;
//	QBool has(const C_Array& carray) const;
//	QBool has(const QArray& array) const;
//
//	QBool rhas(ConstReference reference) const;
//	QBool rhas(const C_Array& carray) const;
//	QBool rhas(const QArray& array) const;
//
//	size_t occurances(ConstReference reference) const;
//	size_t occurances(size_t begin, ConstReference reference) const;
//	size_t occurances(size_t begin, size_t end, ConstReference reference) const;
//	size_t occurances(const Iterator begin, ConstReference reference) const;
//	size_t occurances(const Iterator begin, const Iterator end, ConstReference reference) const;
//
//	size_t occurances(const C_Array& carray) const;
//	size_t occurances(size_t begin, const C_Array& carray) const;
//	size_t occurances(size_t begin, size_t end, const C_Array& carray) const;
//	size_t occurances(const Iterator begin, const C_Array& carray) const;
//	size_t occurances(const Iterator begin, const Iterator end, const C_Array& carray) const;
//
//	size_t occurances(const Container& array) const;
//	size_t occurances(size_t begin, const Container& array) const;
//	size_t occurances(size_t begin, size_t end, const Container& array) const;
//	size_t occurances(const Iterator begin, const QArray& array) const;
//	size_t occurances(const Iterator begin, const Iterator end, const Container& array) const;
//
//	void copy(const C_Array& carray);
//	void copy(const Container& container);
//	void copy(const Iterator begin, const Iterator end);
//	void swap(const C_Array& carray);
//	void swap(const Container& container);
//	void swap(const Iterator begin, const Iterator end);
//	void clear();
//	void pack();
//
//	QBool equals(const C_Array& carray) const;
//	QBool equals(const QArray& other) const;
//
//	QBool isEmpty() const;
//	QBool isFull() const;
//
//	C_Array toCArray() const;
//
//	Reference at(size_t index) const;
//	Reference operator[](size_t index) const;
//
//	QArray operator+(const QArray& other) const;
//	QArray operator+=(const QArray& other) const;
//	void operator=(const QArray& other) const;
//
//	operator bool() const;
//	QBool operator==(const QArray& other) const;
//	QBool operator!=(const QArray& other) const;
//	QBool operator<(const QArray& other) const;
//	QBool operator<=(const QArray& other) const;
//	QBool operator>(const QArray& other) const;
//	QBool operator>=(const QArray& other) const;
//
//	friend std::ostream& operator<< <>(std::ostream& os, const QArray& qarray);
//
//	const Iterator getBegin() const;
//	const Iterator getEnd() const;
//	const ConstIterator getCBegin() const;
//	const ConstIterator getCEnd() const;
//	const ReverseIterator getRBegin() const;
//	const ReverseIterator getREnd() const;
//	const ConstReverseIterator getCRBegin() const;
//	const ConstReverseIterator getCREnd() const;
//
//	size_t getSize() const;
//	size_t getMaxSize() const;
//	ALLOCATOR_ID getAllocator() const;
//
//	static const QArray<Type, TAllocator> EMPTY_ARRAY;
//	static const Value EMPTY_VALUE;
//private:
//	void _setSize(size_t size);
//	void _incrementSize();
//	void _decrementSize();
//	void _addSize(size_t amount);
//	void _subtractSize(size_t amount);
//
//	QBool _hasSpaceFor(size_t num) const;
//	
//	QBool _checkIndex(size_t index) const;
//	QBool _checkIndices(size_t begin, size_t end) const;
//
//	QBool _checkIterator(const Iterator iterator) const;
//	QBool _checkIterators(const Iterator begin, const Iterator end) const;
//
//	QBool _checkReverseIterator(const ReverseIterator iterator) const;
//	QBool _checkReverseIterators(const ReverseIterator begin, const ReverseIterator end) const;
//
//	//Comparison _compare(const Array A, const Array B, size_t size) const;
//
//	template<typename TIterator>
//	QBool _comesBefore(TIterator begin, TIterator end) const;
//
//	Array _array;
//	size_t _size;
//	size_t _maxSize;
//	Allocator _allocator;
//};
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Iterator = typename QArray<Type, TAllocator>::Iterator;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_ConstIterator = typename QArray<Type, TAllocator>::ConstIterator;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_ReverseIterator = typename QArray<Type, TAllocator>::ReverseIterator;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_ConstReverseIterator = typename QArray<Type, TAllocator>::ConstReverseIterator;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Reference = typename QArray<Type, TAllocator>::Reference;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_ConstReference = typename QArray<Type, TAllocator>::ConstReference;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Value = typename QArray<Type, TAllocator>::Value;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Pointer = typename QArray<Type, TAllocator>::Pointer;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Array = typename QArray<Type, TAllocator>::Array;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Index = typename QArray<Type, TAllocator>::Index;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_CArray = typename QArray<Type, TAllocator>::C_Array;
//
//template<typename Type,
//	typename TAllocator>
//using Arr_Container = typename QArray<Type, TAllocator>::Container;
//
//#include "..\Source\qarray.inl"