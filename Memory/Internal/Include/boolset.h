#pragma once

namespace internal
{
	class BoolSet
	{
	public:
		BoolSet(size_t size = 0, bool initial = false);
		~BoolSet();

		void reset();
		void clear();

		bool all() const;
		bool any() const;
		bool none() const;

		bool& operator[](size_t index) const;
		void resize(size_t amount);

		size_t count() const;
		size_t getSize() const;
	private:
		bool* _bools;
		size_t _size;
	};
}