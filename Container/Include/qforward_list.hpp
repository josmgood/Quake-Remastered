#pragma once

/*Standard Library*/
#include <iostream>

/*Custom Library*/
#include "..\Base\Include\base.hpp"

#include "..\..\Memory\Allocators\Include\pool_allocator.hpp"

//template<typename T>
//class QForwardList
//{
//public:
//	struct Node
//	{
//		Node(void);
//		Node(const T& data);
//
//		Node*	next;
//		T		data;
//	};
//	QForwardList				(size_t capacity);
//	QForwardList				(void);
//	~QForwardList				(void);
//
//	void pushFront				(const T& data);
//	void pushBack				(const T& data);
//	void popFront				(void);
//	void popBack				(void);
//
//	void insert					(const T& data, Node* next);
//	void append					(const T& data, Node* prev);
//	bool find					(const T& data);
//	void erase					(Node* node);
//	void reserve				(size_t amount);
//	void clear					(void);
//	bool isEmpty				(void) const;
//
//	const T& getFront			(void) const;
//	const T& getBack			(void) const;
//private:
//	Node* _create				(const T& data);
//	Block _getBlock				(Node* node);
//	Node* _getNext				(Node* node);
//	void _setNext				(Node* curr, Node* _next);
//	void _incrementSize			(void);
//	void _decrementSize			(void);
//
//	Node*								_front;
//	Node*								_back;
//	size_t								_size;
//	PoolAllocator<sizeof(Node)>		_pool;
//};

template<typename Type>
class QForwardList
	: public QLinearContainer<Type, ForwardIterator<Type>, PoolAllocator>
{
public:
	QForwardList(size_t capacity);
	QForwardList();
	virtual ~QForwardList() override;

	virtual void clear() override;
	virtual bool isEmpty() const override;

	virtual void insert(const Reference value, ForwardIterator& next) override;
	virtual void append(const Reference value, ForwardIterator& prev) override;
	virtual void swap(ForwardIterator& one, ForwardIterator& two) override;
	virtual void erase(ForwardIterator& itr) override;

	Iterator& beforeBegin() override;
	virtual const Iterator& begin() override;
	virtual const Iterator& end() override;
}

//#include "..\Source\qforward_list.inl"