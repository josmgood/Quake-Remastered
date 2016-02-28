#pragma once

#include "base.hpp"

template<typename Type,
	typename TAllocator = PoolAllocator<Type>,
	typename TIterator = ArrayIterator<Type>>
class QArray
	:	public QBaseContainer<Type, TAllocator, TIterator, QArray<Type>>,
		public Arrayable<Type>,
		public Searchable<Type>,
		public FrontAccessible<Type>,
		public BackAccessible<Type>
{
public:
	QArray(size_t size = DEFAULT_CONTAINER_SIZE);
	virtual ~QArray() override;

	virtual void clear() override;
	virtual void swap(QArray& other) override;
	virtual bool has(ConstReference value) override;
	
	virtual Reference operator[](size_t index) override;
	virtual Reference at(size_t index) override;
	virtual TIterator& find(ConstReference value) override;

	virtual void pushFront(ConstReference value) override;
	virtual void popFront() override;
	virtual ConstReference getFront() const override;

	virtual void pushBack(ConstReference value) override;
	virtual void popBack() override;
	virtual ConstReference getBack() const override;
};