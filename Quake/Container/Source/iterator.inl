#include "..\Include\iterator.hpp"

template<typename T,
	template<typename> typename I>
IteratorBase<T, I>::IteratorBase()
	: _ptr(nullptr)
{
}

template<typename T,
	template<typename> typename I>
IteratorBase<T, I>::IteratorBase(const Pointer ptr)
	: _ptr(ptr)
{
}

template<typename T,
	template<typename> typename I>
IteratorBase<T, I>::IteratorBase(const Reference ref)
	: _ptr(&ref)
{
}

template<typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator==(Iterator other) const
{
	return _ptr == other._ptr;
}

template< typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator!=(Iterator other) const
{
	return _ptr != other._ptr;
}

template<typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator<(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator<=(Iterator other) const
{
	return _ptr <= other._ptr;
}

template< typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator>(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename T,
	template<typename> typename I>
QBool IteratorBase<T, I>::operator>=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename T,
	template<typename> typename I>
void IteratorBase<T, I>::set(const Pointer ptr)
{
	_ptr = ptr;
}

template<typename T,
	template<typename> typename I>
void IteratorBase<T, I>::set(const Reference ref)
{
	*_ptr = ref;
}

//=======================================================================================

template<typename T, 
	template <typename> typename I>
ForwardIterator<T, I>::ForwardIterator()
	: IteratorBase()
{
}

template<typename T, 
	template<typename> typename I>
ForwardIterator<T, I>::ForwardIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename T,
	template<typename> typename I>
ForwardIterator<T, I>::ForwardIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename T>
ForwardNodeIterator<T>::ForwardNodeIterator()
	: ForwardIterator()
{
}

template<typename T>
ForwardNodeIterator<T>::ForwardNodeIterator(const Pointer ptr)
	: ForwardIterator(ptr)
{
}

template<typename T>
ForwardNodeIterator<T>::ForwardNodeIterator(const Reference ref)
	: ForwardIterator(ref)
{
}

template<typename T>
typename ForwardNodeIterator<T>::Iterator
ForwardNodeIterator<T>::next() const
{
	return Iterator(_ptr->next);
}

template<typename T>
typename ForwardNodeIterator<T>::Reference
ForwardNodeIterator<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
typename ForwardNodeIterator<T>::Pointer
ForwardNodeIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename ForwardNodeIterator<T>::Reference
ForwardNodeIterator<T>::get() const
{
	return *_ptr;
}

template<typename T>
typename ForwardNodeIterator<T>::Iterator
ForwardNodeIterator<T>::operator+(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename T>
void ForwardNodeIterator<T>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->next;
	}
}

template<typename T>
typename ForwardNodeIterator<T>::Iterator
ForwardNodeIterator<T>::operator++()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename T>
ForwardArrayIterator<T>::ForwardArrayIterator()
	: ForwardIterator()
{
}

template<typename T>
ForwardArrayIterator<T>::ForwardArrayIterator(const Pointer ptr)
	: ForwardIterator(ptr)
{
}

template<typename T>
ForwardArrayIterator<T>::ForwardArrayIterator(const Reference ref)
	: ForwardIterator(ref)
{
}

template<typename T>
typename ForwardArrayIterator<T>::Iterator 
ForwardArrayIterator<T>::next() const
{
	return Iterator(_ptr + 1);
}

template<typename T>
typename ForwardArrayIterator<T>::Reference
ForwardArrayIterator<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
typename ForwardArrayIterator<T>::Pointer
ForwardArrayIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename ForwardArrayIterator<T>::Reference 
ForwardArrayIterator<T>::get() const
{
	return *_ptr;
}

template<typename T>
typename ForwardArrayIterator<T>::Iterator
ForwardArrayIterator<T>::operator+(int itrs)
{
	return Iterator(_ptr + sizeof(T) * itrs);
}

template<typename T>
void ForwardArrayIterator<T>::operator+=(int itrs)
{
	_ptr += itrs;
}

template<typename T>
typename ForwardArrayIterator<T>::Iterator
ForwardArrayIterator<T>::operator++()
{
	++_ptr;
	return *this;
}

//=======================================================================================

template<typename T,
	template<typename T> typename I>
BidirectionalIterator<T, I>::BidirectionalIterator()
	: IteratorBase()
{
}

template<typename T,
	template<typename T> typename I>
BidirectionalIterator<T, I>::BidirectionalIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename T,
	template<typename T> typename I>
BidirectionalIterator<T, I>::BidirectionalIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename T>
BidirectionalNodeIterator<T>::BidirectionalNodeIterator()
	: BidirectionalIterator()
{
}

template<typename T>
BidirectionalNodeIterator<T>::BidirectionalNodeIterator(const Pointer ptr)
	: BidirectionalIterator(ptr)
{
}

template<typename T>
BidirectionalNodeIterator<T>::BidirectionalNodeIterator(const Reference ref)
	: BidirectionalIterator(ref)
{
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::next() const
{
	return Iterator(_ptr->next);
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::prev() const
{
	return Iterator(_ptr->prev);
}

template<typename T>
typename BidirectionalNodeIterator<T>::Reference 
BidirectionalNodeIterator<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
typename BidirectionalNodeIterator<T>::Pointer
BidirectionalNodeIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename BidirectionalNodeIterator<T>::Reference
BidirectionalNodeIterator<T>::get() const
{
	return *_ptr;
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::operator+(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename T>
void BidirectionalNodeIterator< T>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->next;
	}
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::operator++()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::operator-(int itrs)
{
	Iterator itr(_ptr);
	while (!itrs--)
	{
		itr._ptr = itr._ptr->next;
	}
	return itr;
}

template<typename T>
void BidirectionalNodeIterator<T>::operator-=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->prev;
	}
}

template<typename T>
typename BidirectionalNodeIterator<T>::Iterator
BidirectionalNodeIterator<T>::operator--()
{
	_ptr = _ptr->prev;
	return *this;
}

template< typename T>
BidirectionalArrayIterator<T>::BidirectionalArrayIterator()
	: BidirectionalIterator()
{
}

template<typename T>
BidirectionalArrayIterator<T>::BidirectionalArrayIterator(const Pointer ptr)
	: BidirectionalIterator(ptr)
{
}

template<typename T>
BidirectionalArrayIterator<T>::BidirectionalArrayIterator(const Reference ref)
	: BidirectionalIterator(ref)
{
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator<T>::next() const
{
	return Iterator(_ptr + 1);
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator< T>::prev() const
{
	return Iterator(_ptr - 1);
}

template<typename T>
typename BidirectionalArrayIterator<T>::Reference
BidirectionalArrayIterator<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Pointer
BidirectionalArrayIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Reference
BidirectionalArrayIterator<T>::get() const
{
	return *_ptr;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator<T>::operator+(int itrs)
{
	return Iterator(_ptr + 1 * itrs);
}

template<typename T>
void BidirectionalArrayIterator<T>::operator+=(int itrs)
{
	_ptr += 1 * itrs;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator<T>::operator++()
{
	++_ptr;
	return *this;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator<T>::operator-(int itrs)
{
	return Iterator(_ptr - 1 * itrs);
}

template<typename T>
void BidirectionalArrayIterator<T>::operator-=(int itrs)
{
	_ptr -= 1 * itrs;
}

template<typename T>
typename BidirectionalArrayIterator<T>::Iterator
BidirectionalArrayIterator<T>::operator--()
{
	--_ptr;
	return *this;
}

//=======================================================================================

template<typename T,
	template<typename T> typename I>
ReverseIterator<T, I>::ReverseIterator()
	: IteratorBase()
{
}

template<typename T,
	template<typename T> typename I>
ReverseIterator<T, I>::ReverseIterator(const Pointer ptr)
	: IteratorBase(ptr)
{
}

template<typename T,
	template<typename T> typename I>
ReverseIterator<T, I>::ReverseIterator(const Reference ref)
	: IteratorBase(ref)
{
}

template<typename T,
	template<typename T> typename I>
QBool ReverseIterator<T, I>::operator<(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename T,
	template<typename T> typename I>
QBool ReverseIterator<T, I>::operator<=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename T,
	template<typename T> typename I>
QBool ReverseIterator<T, I>::operator>(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename T,
	template<typename T> typename I>
QBool ReverseIterator<T, I>::operator>=(Iterator other) const
{
	return _ptr <= other._ptr;
}

template<typename T>
ReverseNodeIterator<T>::ReverseNodeIterator()
	: ReverseIterator()
{
}

template<typename T>
ReverseNodeIterator<T>::ReverseNodeIterator(const Pointer ptr)
	: ReverseIterator(ptr)
{
}

template<typename T>
ReverseNodeIterator<T>::ReverseNodeIterator(const Reference ref)
	: ReverseIterator(ref)
{
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::next() const
{
	return Iterator(_ptr->prev);
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::prev() const
{
	return Iterator(_ptr->next);
}

template<typename T>
typename ReverseNodeIterator<T>::Reference
ReverseNodeIterator<T>::operator*() const
{
	return _ptr;
}

template<typename T>
typename ReverseNodeIterator<T>::Pointer
ReverseNodeIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename ReverseNodeIterator<T>::Reference 
ReverseNodeIterator<T>::get() const
{
	return _ptr;
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::operator+(int itrs)
{
	Pointer node = _ptr;
	while (!itrs--)
	{
		node = node->prev;
	}
	return Iterator(node);
}

template<typename T>
void ReverseNodeIterator<T>::operator+=(int itrs)
{
	while (!itrs--)
	{
		_ptr = _ptr->prev;
	}
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::operator++()
{
	_ptr = _ptr->prev;
	return *this;
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::operator-(int itrs)
{
	Pointer node = _ptr;
	while (!itrs--)
	{
		node = node->next;
	}
	return Iterator(node);
}

template<typename T>
void ReverseNodeIterator<T>::operator-=(int itrs)
{
	while (!itrs--)
	{
		_ptr = ptr->next;
	}
}

template<typename T>
typename ReverseNodeIterator<T>::Iterator
ReverseNodeIterator<T>::operator--()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename T>
ReverseArrayIterator<T>::ReverseArrayIterator()
	: ReverseIterator()
{
}

template<typename T>
ReverseArrayIterator<T>::ReverseArrayIterator(const Pointer ptr)
	: ReverseIterator(ptr)
{
}

template<typename T>
ReverseArrayIterator<T>::ReverseArrayIterator(const Reference ref)
	: ReverseIterator(ref)
{
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::next() const
{
	return _ptr - 1;
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::prev() const
{
	return _ptr + 1;
}

template<typename T>
typename ReverseArrayIterator<T>::Reference
ReverseArrayIterator<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
typename ReverseArrayIterator<T>::Pointer
ReverseArrayIterator<T>::ptr() const
{
	return _ptr;
}

template<typename T>
typename ReverseArrayIterator<T>::Reference
ReverseArrayIterator<T>::get() const
{
	return *_ptr;
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::operator+(int itrs)
{
	return Iterator(_ptr - 1 * itrs);
}

template<typename T>
void ReverseArrayIterator<T>::operator+=(int itrs)
{
	_ptr -= 1 * itrs;
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::operator++()
{	
	--_ptr;
	return *this;
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::operator-(int itrs)
{
	return Iterator(_ptr + 1 * itrs);
}

template<typename T>
void ReverseArrayIterator<T>::operator-=(int itrs)
{
	_ptr += 1 * itrs;
}

template<typename T>
typename ReverseArrayIterator<T>::Iterator
ReverseArrayIterator<T>::operator--()
{
	++_ptr;
	return *this;
}

template<typename T>
QBool ReverseArrayIterator<T>::operator<(Iterator other) const
{
	return _ptr > other._ptr;
}

template<typename T>
QBool ReverseArrayIterator<T>::operator<=(Iterator other) const
{
	return _ptr >= other._ptr;
}

template<typename T>
QBool ReverseArrayIterator<T>::operator>(Iterator other) const
{
	return _ptr < other._ptr;
}

template<typename T>
QBool ReverseArrayIterator<T>::operator>=(Iterator other) const
{
	return _ptr <= other._ptr;
}