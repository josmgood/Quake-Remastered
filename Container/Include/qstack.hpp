#pragma once

/*Custom Library*/
#include "base.hpp"
#include "..\..\Memory\Allocators\Include\pool_allocator.hpp"

template<typename Type,
		typename TAllocator = PoolAllocator<Type>,
		typename TIterator = ArrayIterator<Type>>
class QStack
	:	public QBaseContainer<Type, TAllocator, TIterator, QStack<Type>>,
		public Stackable<Type>,
		public Resizable<Type>
{
public:
	QStack(size_t size = DEFAULT_CONTAINER_SIZE, Value initial = Value());
	virtual ~QStack() override;

	virtual ConstReference getTop() const override;
	virtual void push(ConstReference value) override;
	virtual void pop() override;

	virtual void resize(size_t amount) override;
	virtual void reserve(size_t amount) override;

	virtual void clear() override;
	virtual void swap(QStack& other) override;
	virtual bool has(ConstReference value) override;
};

#include "..\Source\qstack.inl"