#pragma once

#include <iostream>

#include "base.hpp"
#include "iterator.hpp"

#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"
#include "..\..\Memory\Include\Allocator\mallocator.h"

#define NULL_NODE nullptr

template<typename T, typename A>
class ForwardList;

template<typename T, typename A>
std::ostream& operator<<(std::ostream&, const ForwardList<T, A>&);

template<typename T, typename A = MAllocator>
class ForwardList
	: public QAuxiliary<T, A>
{
	struct Node
	{
		Node(ConstReference dat);
		void set(ConstReference dat);

		Node* getNext() const;
		void setNext(Node* nxt);

		Value data;
		Node* next;
	};

	typedef ForwardList<T, A> Container;
	typedef ForwardNodeIterator<T> Iterator;
	typedef ForwardNodeIterator<const T> ConstIterator;

	static const ForwardList EMPTY_FLIST;

	ForwardList(size_t maxSize);
	ForwardList(Iterator begin, Iterator end);
	ForwardList(const Container& container);
	~ForwardList();

	void pushFront(ConstReference reference);
	void pushFront(const Container& container);
	void popFront();
	ConstReference front() const;

	void pushBack(ConstReference reference);
	void pushBack(const Container& container);
	void popBack();
	ConstReference back() const;

	void insert(Node* after, ConstReference reference);
	void append(Node* before, ConstReference reference);

	ForwardList sublist(Iterator iterator) const;

	Iterator find(ConstReference reference) const;
	QBool has(ConstReference reference) const;

	//ForwardList reversed() const;
	//void reverse() const;
	void clear();
	void copy(const Container& other);
	void swap(ForwardList& other);
	void reserve(size_t maxSize);
	void shrink(size_t maxSize);

	QBool equals(const Container& other) const;

	QBool isEmpty() const;
	QBool isFull() const;

	Container operator+(const ForwardList& other);
	Container operator+=(const ForwardList& other);
	void operator=(const Container& other);

	operator bool() const;
	QBool operator==(const Container& other) const;
	QBool operator!=(const Container& other) const;
	QBool operator<(const Container& other) const;
	QBool operator<=(const Container& other) const;
	QBool operator>(const Container& other) const;
	QBool operator>=(const Container& other) const;

	friend std::ostream& operator<< <>(std::ostream& os, const Container& list);

	const Iterator begin() const;
	const Iterator bbegin() const;
	const Iterator end() const;
	const ConstIterator cbegin() const;
	const ConstIterator cbbegin() const;
	const ConstIterator cend() const;

	size_t size() const;
	size_t maxSize() const;
private:
	void _incrementSize();
	void _decrementSize();
	Node* _allocateNode();
	void _deallocateNode(Node* node);

	QBool _hasSpaceFor(size_t amount) const;
	void _initBounds(ConstReference reference);

	Node* _front;
	Node* _back;
	Node* _bbegin;
	Node* _end;

	size_t _size;
	size_t _maxSize;
	Allocator _allocator;
};

template<typename T,
	typename A>
using FL_Iterator = typename ForwardList<T, A>::Iterator;

template<typename T,
	typename A>
using FL_ConstIterator = typename ForwardList<T, A>::ConstIterator;

template<typename T,
	typename A>
using FL_Reference = typename ForwardList<T, A>::Reference;

template<typename T,
	typename A>
using FL_ConstReference = typename ForwardList<T, A>::ConstReference;

template<typename T,
	typename A>
using FL_Pointer = typename ForwardList<T, A>::Pointer;

template<typename T,
	typename A>
using FL_Value = typename ForwardList<T, A>::Value;

template<typename T,
	typename A>
using FL_Node = typename ForwardList<T, A>::Node*;


#include "..\Source\forward_list.inl"