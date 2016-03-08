#include "..\..\Include\Internal\stack.hpp"

namespace internal
{
	template<typename T>
	Stack<T>::Stack(size_t capacity)
		: _stack(nullptr), _capacity(capacity), _size()
	{
		_stack = new T[stackSize];
	}

	template<typename T>
	Stack<T>::~Stack(void)
	{
		clear();
	}

	template<typename T>
	void Stack<T>::push(const T& elem)
	{
		size_t size = _capacity;
		size_t pos = _size + 1;
		if (pos <= size)
		{
			_stack[pos] = elem;
			_size++;
		}
	}

	template<typename T>
	void Stack<T>::pop(void)
	{
		size_t size = _capacity;;
		size_t pos = _size;
		if (pos >= 0 && _stack[pos])
		{
			_stack[pos] = T();
			if (pos > 0)
			{
				_size--;
			}
		}
	}

	template<typename T>
	void Stack<T>::clear(void)
	{
		while (_stack[0])
		{
			pop();
		}
	}

	template<typename T>
	T& Stack<T>::getTop(void) const
	{
		size_t top = _size;
		return(_stack[top]);
	}

	template<typename T>
	size_t Stack<T>::getSize(void) const
	{
		return(_size);
	}
}