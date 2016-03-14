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

	inline QArray(size_t maxSize = DEFAULT_CONTAINER_SIZE, ConstReference initial = Value());
	inline ~QArray();

	inline void pushFront(ConstReference value);
	inline void pushBack(ConstReference value);

	inline void setFront(ConstReference value);
	inline void setBack(ConstReference value);

	inline void popFront();
	inline void popBack();

	inline ConstReference getFront() const;
	inline ConstReference getBack() const;

	inline size_t find(ConstReference value);
	inline bool owns(ConstReference value);
	inline void clear(size_t index);
	void clear();
	void swap(QArray& other);
	void pack();

	Reference operator[](size_t index) const;
	Reference at(size_t index) const;
	void set(size_t index, ConstReference value);

	std::ostream& operator<<(std::ostream& os);

	size_t getSize() const;
	size_t getMaxSize() const;
private:
	Array _array;
	size_t _size;
	size_t _maxSize;
	size_t _back;
};

#include "..\Source\qarray.inl"