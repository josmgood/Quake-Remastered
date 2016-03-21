#include "..\Include\iterator.hpp"

template<typename Type,
	template<typename T> typename TIterator>
IteratorBase<Type, TIterator>::IteratorBase()
	: _ptr(nullptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
IteratorBase<Type, TIterator>::IteratorBase(const Pointer ptr)
	: _ptr(ptr)
{
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator==(Iterator other) const
{
	return _ptr == other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator!=(Iterator other) const
{
	return _ptr != other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator<(Iterator other) const
{
	return _ptr < other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator<=(Iterator other) const
{
	return _ptr <= other._ptr;
}

template< typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator>(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
QBool IteratorBase<Type, TIterator>::operator>=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename Type,
	template<typename T> typename TIterator>
void IteratorBase<Type, TIterator>::set(const Pointer ptr)
{
	_ptr = ptr;
}

//=======================================================================================

template<typename Type, 
	template <typename T> typename TIterator>
ForwardIterator<Type, TIterator>::ForwardIterator()
	: IteratorBase()
{
}

template<typename Type, 
	template<typename T> typename TIterator>
ForwardIterator<Type, TIterator>::ForwardIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename Type>
ForwardNodeIterator<Type>::ForwardNodeIterator()
	: _ptr(nullptr)
{
}

template<typename Type>
ForwardNodeIterator<Type>::ForwardNodeIterator(const Pointer ptr)
	: _ptr(ptr)
{
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::next() const
{
	return Iterator(_ptr->next);
}

template<typename Type>
typename ForwardNodeIterator<Type>::Reference
ForwardNodeIterator<Type>::operator*() const
{
	return _ptr->data;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Pointer
ForwardNodeIterator<Type>::ptr() const
{
	return &_ptr->data;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Reference
ForwardNodeIterator<Type>::get() const
{
	return _ptr->data;
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::operator+(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename Type>
void ForwardNodeIterator<Type>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = ptr->next;
	}
}

template<typename Type>
typename ForwardNodeIterator<Type>::Iterator
ForwardNodeIterator<Type>::operator++()
{
	return Iterator(_ptr = _ptr->next);
}

template<typename Type>
ForwardArrayIterator<Type>::ForwardArrayIterator()
{
	_ptr = nullptr;
}

template<typename Type>
ForwardArrayIterator<Type>::ForwardArrayIterator(const Pointer ptr)
{
	_ptr = ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator 
ForwardArrayIterator<Type>::next()
{
	return Iterator(_ptr + 1);
}

template<typename Type>
typename ForwardArrayIterator<Type>::Reference
ForwardArrayIterator<Type>::operator*() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Pointer
ForwardArrayIterator<Type>::ptr() const
{
	return _ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Reference 
ForwardArrayIterator<Type>::get() const
{
	return *_ptr;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator
ForwardArrayIterator<Type>::operator+(int itrs)
{
	return Iterator(_ptr + sizeof(Type) * itrs);
}

template<typename Type>
void ForwardArrayIterator<Type>::operator+=(int itrs)
{
	_ptr += itrs;
}

template<typename Type>
typename ForwardArrayIterator<Type>::Iterator
ForwardArrayIterator<Type>::operator++()
{
	return Iterator(++_ptr);
}

//=======================================================================================

template<typename Type,
	template<typename T> typename TIterator>
BidirectionalIterator<Type, TIterator>::BidirectionalIterator()
	: IteratorBase()
{
}

template<typename Type,
	template<typename T> typename TIterator>
BidirectionalIterator<Type, TIterator>::BidirectionalIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

//template< 
//	typename Type>
//BidirectionalNodeIterator< Type>::BidirectionalNodeIterator()
//	: IteratorBase()
//{
//}
//
//template< 
//	typename Type>
//BidirectionalNodeIterator< Type>::BidirectionalNodeIterator(const Pointer ptr)
//	: IteratorBase(ptr)
//{
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::next() const
//{
//	return Iterator(_ptr->next);
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::prev() const
//{
//	return Iterator(_ptr->prev);
//}
//
//template< 
//	typename Type>
//BReference< Type> BidirectionalNodeIterator< Type>::operator*() const
//{
//	return _ptr->data;
//}
//
//template< 
//	typename Type>
//BPointer< Type> BidirectionalNodeIterator< Type>::ptr() const
//{
//	return &_ptr->data;
//}
//
//template< 
//	typename Type>
//BReference< Type> BidirectionalNodeIterator< Type>::get() const
//{
//	return _ptr->data;
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::operator+(int itrs)
//{
//	Iterator itr(_ptr);
//	while (!itrs--)
//	{
//		itr._ptr = itr._ptr->next;
//	}
//	return itr;
//}
//
//template< 
//	typename Type>
//void BidirectionalNodeIterator< Type>::operator+=(int itrs)
//{
//	while (!itrs--)
//	{
//		_ptr = _ptr->next;
//	}
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::operator++()
//{
//	return Iterator(_ptr = _ptr->next);
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::operator-(int itrs)
//{
//	Iterator itr(_ptr);
//	while (!itrs--)
//	{
//		itr._ptr = itr._ptr->next;
//	}
//	return itr;
//}
//
//template< 
//	typename Type>
//void BidirectionalNodeIterator< Type>::operator-=(int itrs)
//{
//	while (!itrs--)
//	{
//		_ptr = _ptr->prev;
//	}
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalNodeIterator< Type>::operator--()
//{
//	return Iterator(_ptr = _ptr->prev);
//}
//
//template< 
//	typename Type>
//BidirectionalArrayIterator< Type>::BidirectionalArrayIterator()
//	: BidirectionalIterator()
//{
//}
//
//template< 
//	typename Type>
//BidirectionalArrayIterator< Type>::BidirectionalArrayIterator(const Pointer ptr)
//	: BidirectionalArrayIterator(ptr)
//{
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::next() const
//{
//	return Iterator(_ptr + sizeof(Value));
//}
//
//template< 
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::prev() const
//{
//	return Iterator(_ptr - sizeof(Value));
//}
//
//template<
//	typename Type>
//BReference< Type> BidirectionalArrayIterator< Type>::operator*() const
//{
//	return *_ptr;
//}
//
//template<
//	typename Type>
//BPointer< Type> BidirectionalArrayIterator< Type>::ptr() const
//{
//	return _ptr;
//}
//
//template<
//	typename Type>
//BReference< Type> BidirectionalArrayIterator< Type>::get() const
//{
//	return *_ptr;
//}
//
//template<
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::operator+(int itrs)
//{
//	return Iterator(_ptr + sizeof(Value) * itrs);
//}
//
//template<
//	typename Type>
//void BidirectionalArrayIterator< Type>::operator+=(int itrs)
//{
//	_ptr += sizeof(Value) * itrs;
//}
//
//template<
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::operator++()
//{
//	return Iterator(++_ptr);
//}
//
//template<
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::operator-(int itrs)
//{
//	return Iterator(_ptr - sizeof(Value) * itrs);
//}
//
//template<
//	typename Type>
//void BidirectionalArrayIterator< Type>::operator-=(int itrs)
//{
//	_ptr -= sizeof(Value) * itrs;
//}
//
//template<
//	typename Type>
//BIterator< Type> BidirectionalArrayIterator< Type>::operator--()
//{
//	return Iterator(--_ptr);
//}
//
////=======================================================================================