#pragma once

#include "..\..\..\Container\Include\qbool.h"

namespace internal
{
	class BoolSet
	{
	public:
		BoolSet();
		BoolSet(size_t size, QBool initial = false);
		BoolSet(const BoolSet& bSet);
		~BoolSet();

		void reset();
		void clear();

		QBool all() const;
		QBool any() const;
		QBool none() const;

		QBool& operator[](size_t index) const;
		void resize(size_t amount);

		size_t count() const;
		size_t getSize() const;
	private:
		QBool* _bools;
		size_t _size;
	};
}