#include "..\Include\qforward_list.hpp"

template<typename Type,
	typename TAllocator>
QForwardList<Type, TAllocator>::Node::Node(ConstReference dat)
	: data(data), next(nullptr)
{
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::Node::set(ConstReference dat)
{
	data = dat;
}

template<typename Type,
	typename TAllocator>
FL_Node<Type, TAllocator>
QForwardList<Type, TAllocator>::Node::getNext() const
{
	return next;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::Node::setNext(Node* nxt)
{
	next = nxt;
}

template<typename Type,
	typename TAllocator>
QForwardList<Type, TAllocator>::QForwardList(size_t maxSize)
	: _front(nullptr), _back(nullptr), _size(), _maxSize(maxSize), _allocator()
{
}

template<typename Type,
	typename TAllocator>
QForwardList<Type, TAllocator>::QForwardList(const QForwardList& list)
	: _front(nullptr), _back(nullptr), _size(), _maxSize(list._maxSize), _allocator()
{
	Node* i = list._front;
	size_t size = list._size;
	while (size--)
	{
		pushBack(i->data);
		i = i->getNext();
	}
}

template<typename Type,
	typename TAllocator>
QForwardList<Type, TAllocator>::~QForwardList()
{
	empty();
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::pushFront(ConstReference reference)
{
	if (!isEmpty() && !isFull())
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		node->setNext(_front);
		_front = node;
		_incrementSize();
	}
	else
	{
		_initBounds(reference);
	}
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::pushFront(const QForwardList& list)
{
	size_t size = list.getSize();
	if (_hasSpaceFor(size))
	{
		for (Node* i = list._front; size--; i = i->getNext())
		{
			pushFront(i->data);
		}
	}
}

template<typename Type,
	typename TAllocator>
FL_ConstReference<Type, TAllocator>
QForwardList<Type, TAllocator>::getFront() const
{
	return _front->data;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::popFront()
{
	if (_front)
	{
		void* mem = static_cast<void*>(_front);
		size_t size = sizeof(Node);
		Block block(mem, size);
		_front = front->getNext();
		_allocator.deallocate(block);
		_decrementSize();
	}
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::pushBack(ConstReference reference)
{
	if (!isEmpty() && !isFull())
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		_back->setNext(node);
		_back = node;
		_incrementSize();
	}
	else
	{
		_initBounds(reference);
	}
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::pushBack(const QForwardList& list)
{
	size_t size = list.getSize();
	if (_hasSpaceFor(size))
	{
		for (Node* i = list._front; size--; i = i->getNext())
		{
			pushBack(i->data);
		}
	}
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::popBack()
{
	if (_back)
	{
		Node* i = _front;
		while (i = i->getNext() != _back);
		if (i)
		{
			void* mem = static_cast<void*>(_back);
			size_t size = sizeof(Node);
			Block block(mem, size);
			_back = i;
			_allocator.deallocate(block);
			_decrementSize();
		}
	}
}

template<typename Type,
	typename TAllocator>
FL_ConstReference<Type, TAllocator>
QForwardList<Type, TAllocator>::getBack() const
{
	return _back->data;
}

template<typename Type,
	typename TAllocator>
FL_Iterator<Type, TAllocator>
QForwardList<Type, TAllocator>::find(ConstReference reference) const
{
	Iterator begin = getBegin();
	Iterator end = getEnd();
	for (Iterator i = begin; i < end; ++i)
	{
		if (i.get()->data = reference)
		{
			return true;
		}
	}
	return false;
}

template<typename Type,
	typename TAllocator>
	void QForwardList<Type, TAllocator>::clear()
{
	while (!isEmpty())
	{
		if (_front)
		{
			popFront();
		}
		if (_back)
		{
			popBack();
		}
	}
}

template<typename Type,
	typename TAllocator>
QBool QForwardList<Type, TAllocator>::isEmpty() const
{
	return _size == 0;
}

template<typename Type,
	typename TAllocator>
QBool QForwardList<Type, TAllocator>::isFull() const
{
	return _size == _maxSize;
}

template<typename Type,
	typename TAllocator>
const FL_Iterator<Type, TAllocator>
QForwardList<Type, TAllocator>::getBegin() const
{
	return Iterator(_front);
}

template<typename Type,
	typename TAllocator>
const FL_Iterator<Type, TAllocator>
QForwardList<Type, TAllocator>::getBeforeBegin() const
{
	
}

template<typename Type,
	typename TAllocator>
const FL_Iterator<Type, TAllocator>
QForwardList<Type, TAllocator>::getEnd() const
{
	//return Iterator(_back + 1);
}

template<typename Type,
	typename TAllocator>
size_t QForwardList<Type, TAllocator>::getSize() const
{
	return _size;
}

template<typename Type,
	typename TAllocator>
size_t QForwardList<Type, TAllocator>::getMaxSize() const
{
	return _maxSize;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::_incrementSize()
{
	_size++;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::_decrementSize()
{
	_size--;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::_addSize(size_t size)
{
	_size += size;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::_subtractSize(size_t size)
{
	_size -= size;
}

template<typename Type,
	typename TAllocator>
QBool QForwardList<Type, TAllocator>::_hasSpaceFor(size_t amount)
{
	return _size + amount <= _maxSize;
}

template<typename Type,
	typename TAllocator>
void QForwardList<Type, TAllocator>::_initBounds(ConstReference reference)
{
	if (!_front && !_back && _maxSize)
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		_front = _back = node;
		_incrementSize();
	}
}