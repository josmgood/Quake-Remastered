#pragma once

#include <iostream>

#include "base.hpp"
#include "..\..\Memory\Include\Allocator\pool_allocator.hpp"

//template<typename Type,
//	typename TAllocator = PoolAllocator<Type>,
//	typename TIterator = ArrayIterator<Type>>
//class QArray
//	:	public QBaseContainer<Type, TAllocator, TIterator, QArray<Type>>,
//		public Arrayable<Type>,
//		public Searchable<Type>,
//		public FrontAccessible<Type>,
//		public BackAccessible<Type>
//{
//public:
//	QArray(size_t size = DEFAULT_CONTAINER_SIZE);
//	virtual ~QArray() override;
//
//	virtual void clear() override;
//	virtual void swap(QArray& other) override;
//	virtual bool has(ConstReference value) override;
//	
//	virtual Reference operator[](size_t index) override;
//	virtual Reference at(size_t index) override;
//	virtual TIterator& find(ConstReference value) override;
//
//	virtual void pushFront(ConstReference value) override;
//	virtual void popFront() override;
//	virtual ConstReference getFront() const override;
//
//	virtual void pushBack(ConstReference value) override;
//	virtual void popBack() override;
//	virtual ConstReference getBack() const override;
//};

template<typename Type,
	typename TAllocator = PoolAllocator<Type>>
class QArray
	: public QAuxiliary<Type, TAllocator>
{
public:
	typedef Pointer Array;
	typedef Value Node;

	QArray(size_t maxSize = DEFAULT_CONTAINER_SIZE, ConstReference initial = Value());
	~QArray();

	void pushFront(ConstReference value);
	void pushBack(ConstReference value);

	void setFront(ConstReference value);
	void setBack(ConstReference value);

	void popFront();
	void popBack();

	ConstReference getFront() const;
	ConstReference getBack() const;

	size_t find(ConstReference value);
	bool owns(ConstReference value);
	void clear(size_t index);
	void clear();
	void swap(QArray& other);
	void pack();

	Reference operator[](size_t index) const;
	Reference at(size_t index) const;
	void set(size_t index, ConstReference value);

	std::ostream& operator<<(std::ostream& os);
private:
	Array _array;
	size_t _back;
};

#include "..\Source\qarray.inl"