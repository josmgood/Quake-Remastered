#pragma once

#include <iostream>

#include "base.hpp"
#include "iterator.hpp"

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"
#include "..\..\Memory\Include\Allocator\mallocator.h"

template<typename Type,
	typename TAllocator>
class QForwardList;

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream&, const QForwardList<Type, TAllocator>&);

template<typename Type,
	typename TAllocator = MAllocator>
class QForwardList
	: public QAuxiliary<Type, TAllocator>
{
	typedef ForwardNodeIterator<Type> Iterator;
	typedef ForwardNodeIterator<const Type> ConstIterator;

	struct Node
	{
		Node(ConstReference dat);
		void set(ConstReference dat);

		Node* getNext() const;
		void setNext(Node* nxt);

		Value data;
		Node* next;
	};
	QForwardList(size_t maxSize);
	QForwardList(Iterator begin, Iterator end);
	QForwardList(const QForwardList& list);
	~QForwardList();

	void pushFront(ConstReference reference);
	void pushFront(const QForwardList& list);
	void popFront();
	ConstReference getFront() const;

	void pushBack(ConstReference reference);
	void pushBack(const QForwardList& list);
	void popBack();
	ConstReference getBack() const;

	void insert(ConstReference reference);
	void insert(Iterator start, ConstReference reference);
	void insert(const QForwardList& list);
	void insert(Iterator start, const QForwardList& list);
	void append(ConstReference reference);
	void append(Iterator start, ConstReference reference);
	void append(const QForwardList& list);
	void append(Iterator start, const QForwardList& list);
	void pop(Iterator iterator);
	void pop(Iterator begin, Iterator end);

	QForwardList sublist(Iterator index) const;
	QForwardList sublist(Iterator begin, Iterator end) const;

	Iterator find(ConstReference reference) const;
	Iterator find(Iterator start, ConstReference reference) const;
	Iterator find(Iterator begin, Iterator end, ConstReference reference) const;

	Iterator find(const QForwardList& sublist) const;
	Iterator find(Iterator start, const QForwardList& sublist) const;
	Iterator find(Iterator begin, Iterator end, const QForwardList& sublist) const;

	QBool has(ConstReference reference) const;
	QBool has(Iterator start, ConstReference reference) const;
	QBool has(Iterator begin, Iterator end, ConstReference reference) const;

	QBool has(const QForwardList& sublist) const;
	QBool has(Iterator start, const QForwardList& sublist) const;
	QBool has(Iterator begin, Iterator end, const QForwardList& sublist) const;

	size_t occurances(ConstReference reference) const;
	size_t occurances(const QForwardList& sublist) const;
	size_t occurances(Iterator start, ConstReference reference) const;
	size_t occurances(Iterator start, const QForwardList& sublist) const;
	size_t occurances(Iterator begin, Iterator end, ConstReference reference) const;
	size_t occurances(Iterator begin, Iterator end, const QForwardList& sublist) const;

	QForwardList reversed() const;
	void reverse() const;
	void clear();
	void copy(const QForwardList& other);
	void swap(QForwardList& other);
	void resize(size_t maxSize);

	QBool equals(const QForwardList& other) const;

	QBool isEmpty() const;
	QBool isFull() const;

	QForwardList operator+(ConstReference reference);
	QForwardList operator+(const QForwardList& other);
	QForwardList operator+=(ConstReference reference);
	QForwardList operator+=(const QForwardList& other);
	void operator=(const QForwardList& other);

	operator bool() const;
	QBool operator==(const QForwardList& other) const;
	QBool operator!=(const QForwardList& other) const;
	QBool operator<(const QForwardList& other) const;
	QBool operator<=(const QForwardList& other) const;
	QBool operator>(const QForwardList& other) const;
	QBool operator>=(const QForwardList& other) const;

	friend std::ostream& operator<< <>(std::ostream&, const QForwardList& list);

	const Iterator getBegin() const;
	const Iterator getBeforeBegin() const;
	const Iterator getEnd() const;
	const ConstIterator getCBegin() const;
	const ConstIterator getCBeforeBegin() const;
	const ConstIterator getCEnd() const;

	size_t getSize() const;
	size_t getMaxSize() const;

	static const QForwardList EMPTY_FLIST;
	static const Node* NULL_NODE;
private:
	void _incrementSize();
	void _decrementSize();
	void _addSize(size_t size);
	void _subtractSize(size_t size);

	QBool _hasSpaceFor(size_t amount);
	void _initBounds(ConstReference reference);

	Node* _front;
	Node* _back;

	size_t _size;
	size_t _maxSize;
	Allocator _allocator;
};

template<typename Type,
	typename TAllocator>
using FL_Iterator = typename QForwardList<Type, TAllocator>::Iterator;

template<typename Type,
	typename TAllocator>
using FL_ConstIterator = typename QForwardList<Type, TAllocator>::ConstIterator;

template<typename Type,
	typename TAllocator>
using FL_Reference = typename QForwardList<Type, TAllocator>::Reference;

template<typename Type,
	typename TAllocator>
using FL_ConstReference = typename QForwardList<Type, TAllocator>::ConstReference;

template<typename Type,
	typename TAllocator>
using FL_Pointer = typename QForwardList<Type, TAllocator>::Pointer;

template<typename Type,
	typename TAllocator>
using FL_Value = typename QForwardList<Type, TAllocator>::Value;

template<typename Type,
	typename TAllocator>
using FL_Node = typename QForwardList<Type, TAllocator>::Node*;


#include "..\Source\qforward_list.inl"