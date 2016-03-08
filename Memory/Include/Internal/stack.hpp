#pragma once

namespace internal
{
	template<typename T>
	class Stack
	{
	public:
		Stack(size_t capacity);
		~Stack(void);

		void push(const T& elem);
		void pop(void);
		void clear(void);

		T& getTop(void) const;
		size_t getCapacity(void) const;
		size_t getSize(void) const;
	private:
		T*			_stack;
		size_t		_capacity;
		size_t		_size;
	};
}

#include "..\..\Source\Internal\stack.inl"