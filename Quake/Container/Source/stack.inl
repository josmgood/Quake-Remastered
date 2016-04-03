#include "..\Include\stack.hpp"

template<typename Type,
	typename TAllocator>
const Stack<Type, TAllocator> Stack<Type, TAllocator>::EMPTY_STACK(0);

//template<typename Type,
//	typename TAllocator>
//const Stack<Type, TAllocator>::Node* Stack<Type, TAllocator>::NULL_NODE = nullptr;

template<typename Type,
	typename TAllocator>
const Stk_Value<Type, TAllocator> Stack<Type, TAllocator>::EMPTY_VALUE = Value();

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::Node::Node(ConstReference dat)
	: data(dat), next(nullptr), prev(nullptr)
{
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::Node::set(ConstReference dat)
{
	data = dat;
}

template<typename Type,
	typename TAllocator>
Stk_Node<Type, TAllocator>
Stack<Type, TAllocator>::Node::getNext() const
{
	return next;
}

template<typename Type,
	typename TAllocator>
Stk_Node<Type, TAllocator>
Stack<Type, TAllocator>::Node::getPrev() const
{
	return prev;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::Node::setNext(Node* nxt)
{
	next = nxt;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::Node::setPrev(Node* prv)
{
	prev = prv;
}


template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::Stack(size_t maxSize)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(maxSize), _allocator()
{
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::Stack(const Pointer array_ptr, size_t size)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(size), _allocator()
{
	for (size_t i = 0; i < size; ++i)
	{
		Value value = array_ptr[i];
		push(value);
	}
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::Stack(const Stack& other)
	: _bottom(nullptr), _top(nullptr), _size(), _maxSize(), _allocator()
{
	if (other)
	{
		size_t size = other._size;
		_maxSize = other._maxSize;
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::~Stack()
{
	clear();
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::set(ConstReference reference)
{
	if (!isEmpty())
	{
		_top->set(reference);
	}
	else
	{
		_initBounds(reference);
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::push(const Stack& other)
{
	size_t size = other._size;
	if (_hasSpaceFor(size))
	{
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::push(ConstReference reference)
{
	if (isEmpty())
	{
		_initBounds(reference);
	}
	else if (!isFull())
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		node->setPrev(_top);
		node->getPrev()->setNext(node);
		_top = node;
		_incrementSize();
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::pop(size_t amount)
{
	while (!isEmpty() && amount--)
	{
		pop();
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::pop()
{
	if (!isEmpty())
	{
		void* mem = static_cast<void*>(_top);
		size_t size = sizeof(Node);
		Block block(mem, size);
		_top = _top->getPrev();
		_allocator.deallocate(block);
		_decrementSize();
	}
}

template<typename Type,
	typename TAllocator>
Stk_Value<Type, TAllocator>
Stack<Type, TAllocator>::take()
{
	if (!isEmpty())
	{
		Value value = _top->data;
		pop();
		return value;
	}
	return EMPTY_VALUE;
}

template<typename Type,
	typename TAllocator>
Stk_ConstReference<Type, TAllocator>
Stack<Type, TAllocator>::peek() const
{
	return _top->data;
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>
Stack<Type, TAllocator>::getReversed() const
{
	size_t size = _size;
	Stack stack(size);
	for (Node* i = _top; size--; i = i->getPrev())
	{
		stack.push(i->data);
	}
	return stack;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::reverse()
{
	size_t size = _size / 2;
	for (Node* i = _bottom, *j = _top;
		 size--;
		 i = i->getNext(),
		 j = j->getPrev())
	{
		if (i != j)
		{
			Value value = j->data;
			j->set(i->data);
			i->set(value);
		}
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::clear()
{
	while (!isEmpty())
	{
		pop();
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::copy(const Stack& other)
{
	size_t size = other._size;
	_maxSize = _maxSize > other._maxSize ? _maxSize : other._maxSize;
	while (_size > size)
	{
		pop();
	}
	Node* i = _bottom;
	Node* j = other._bottom;
	while (size--)
	{
		if (i)
		{
			Value value = j->data;
			j->set(i->data);
			i->set(value);
			i = i->getNext();
		}
		else
		{
			push(j->data);
		}
		j = j->getNext();
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::swap(Stack& other)
{
	size_t tSize = _size;
	size_t oSize = other._size;

	size_t lesser = tSize > oSize ? oSize : tSize;
	_size = lesser;
	other._size = lesser;

	Node* i = _bottom;
	Node* j = other._bottom;
	while (lesser--)
	{
		Value value = j->data;
		j->set(i->data);
		i->set(value);

		i = i->getNext();
		j = j->getNext();
	}

	if (tSize > oSize)
	{
		size_t remain = tSize - oSize;
		while (remain--)
		{
			other.push(i->data);
			i = i->getNext();
		}
	}
	else if (oSize > tSize)
	{
		size_t remain = oSize - tSize;
		while (remain--)
		{
			push(j->data);
			j = j->getNext();
		}
	}
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::shrink(size_t maxSize)
{
	while (_size > maxSize)
	{
		pop();
	}
	_setMaxSize(maxSize);
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::resize(size_t maxSize)
{
	if (_size > maxSize)
	{
		shrink(maxSize);
	}
	else
	{
		_setMaxSize(maxSize);
	}
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::equals(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
			 tSize--;
			 i = i->getNext(),
			 j = j->getNext())
		{
			if (i->data != j->data)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::isEmpty() const
{
	return _size == 0;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::isFull() const
{
	return _size == _maxSize;
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>
Stack<Type, TAllocator>::operator+(const Stack& other)
{
	size_t tSize = _size;
	size_t oSize = other._size;
	size_t size = tSize + oSize;
	Stack stack(size);
	for (Node* i = _bottom; tSize--; i = i->getNext())
	{
		stack.push(i->data);
	}
	for (Node* i = other._bottom; oSize--; i = i->getNext())
	{
		stack.push(i->data);
	}
	return stack;
}

template<typename Type, 
	typename TAllocator>
Stack<Type, TAllocator>
Stack<Type, TAllocator>::operator+=(const Stack& other)
{
	size_t size = other._size;
	if (_hasSpaceFor(size))
	{
		Node* i = other._bottom;
		while (size--)
		{
			push(i->data);
			i = i->getNext();
		}
	}
	return *this;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::operator=(const Stack& other)
{
	size_t size = other._size;
	_maxSize = _maxSize > other._maxSize ? _maxSize : other._maxSize;
	while (_size > size)
	{
		pop();
	}
	Node* i = _bottom;
	Node* j = other._bottom;
	while (size--)
	{
		if (i)
		{
			Value value = j->data;
			i->set(value);
			i = i->getNext();
		}
		else
		{
			push(j->data);
		}
		j = j->getNext();
	}
}

template<typename Type,
	typename TAllocator>
Stack<Type, TAllocator>::operator bool() const
{
	return _bottom && _size && _maxSize;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator==(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
			 tSize--;
			 i = i->getNext(),
			 j = j->getNext())
		{
			if (i->data != j->data)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator!=(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize)
	{
		for (Node* i = _bottom, *j = other._bottom;
			 tSize--;
			 i = i->getNext(),
			 j = j->getNext())
		{
			if (i->data != j->data)
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator<(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _bottom;
		Node* j = other._bottom;
		while (tSize--)
		{
			if (i->data >= j->data)
			{
				return false;
			}
			i = i->getNext();
			j = j->getNext();
		}
		return true;
	}
	return tSize < oSize;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator<=(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _bottom;
		Node* j = other._bottom;
		while (tSize--)
		{
			if (i->data > j->data)
			{
				return false;
			}
			i = i->getNext();
			j = j->getNext();
		}
		return true;
	}
	return tSize <= oSize;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator>(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _bottom;
		Node* j = other._bottom;
		while (tSize--)
		{
			if (i->data <= j->data)
			{
				return false;
			}
			i = i->getNext();
			j = j->getNext();
		}
		return true;
	}
	return tSize > oSize;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::operator>=(const Stack& other) const
{
	size_t tSize = _size;
	size_t oSize = other._size;
	if (tSize == oSize && tSize)
	{
		Node* i = _bottom;
		Node* j = other._bottom;
		while (tSize--)
		{
			if (i->data < j->data)
			{
				return false;
			}
			i = i->getNext();
			j = j->getNext();
		}
		return true;
	}
	return tSize >= oSize;
}

template<typename Type,
	typename TAllocator>
size_t Stack<Type, TAllocator>::getSize() const
{
	return _size;
}

template<typename Type,
	typename TAllocator>
size_t Stack<Type, TAllocator>::getMaxSize() const
{
	return _maxSize;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_setSize(size_t size)
{
	_size = size;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_setMaxSize(size_t max)
{
	_maxSize = max;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_incrementSize()
{
	_size++;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_decrementSize()
{
	_size--;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_addSize(size_t amount)
{
	_size += amount;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_subtractSize(size_t amount)
{
	_size -= amount;
}

template<typename Type,
	typename TAllocator>
QBool Stack<Type, TAllocator>::_hasSpaceFor(size_t num) const
{
	return _size + num <= _maxSize;
}

template<typename Type,
	typename TAllocator>
void Stack<Type, TAllocator>::_initBounds(ConstReference reference)
{
	if (!_bottom && !_top && _maxSize)
	{
		Block block = _allocator.allocate(sizeof(Node));
		Node* node = static_cast<Node*>(block.memory);
		node->set(reference);
		_bottom = _top = node;
		_incrementSize();
	}
}

template<typename Type,
	typename TAllocator>
std::ostream& operator<<(std::ostream& os, const Stack<Type, TAllocator>& stack)
{
	size_t size = stack._size;
	for (Stk_Node<Type, TAllocator> i = stack._top;
		 size--;
		 i = i->getPrev())
	{
		os << "Node " << size << ": " << i->data << std::endl;
	}
	return os;
}