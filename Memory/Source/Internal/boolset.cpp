#include "..\..\Include\Internal\boolset.h"

namespace mem
{
	namespace internal
	{
		BoolSet::BoolSet(size_t size, bool initial)
			: _bools(new bool[size]), _size(size)
		{
			for (size_t i = 0; i < size; i++)
			{
				_bools[i] = initial;
			}
		}

		BoolSet::~BoolSet()
		{
			clear();
		}

		void BoolSet::reset()
		{
			size_t size = _size;
			for (size_t i = 0; i < size; i++)
			{
				if (_bools[i])
				{
					_bools[i] = false;
				}
			}
		}

		void BoolSet::clear()
		{
			_size = 0;
			delete[] _bools;
		}

		bool BoolSet::all() const
		{
			size_t size = _size;
			for (size_t i = 0; i < size; i++)
			{
				if (!_bools[i])
				{
					return(false);
				}
			}
			return(true);
		}

		bool BoolSet::any() const
		{
			size_t size = _size;
			for (size_t i = 0; i < size; i++)
			{
				if (_bools[i])
				{
					return(true);
				}
			}
			return(false);
		}

		bool BoolSet::none() const
		{
			size_t size = _size;
			for (size_t i = 0; i < size; i++)
			{
				if (_bools[i])
				{
					return(false);
				}
			}
			return(true);
		}

		bool& BoolSet::operator[](size_t index) const
		{
			return(_bools[index]);
		}

		void BoolSet::resize(size_t amount)
		{
			size_t oldSize = _size;
			size_t newSize = amount + oldSize;
			bool* newBools = new bool[newSize];
			for (size_t i = 0; i < oldSize; i++)
			{
				newBools[i] = _bools[i];
			}
			_bools = newBools;
			_size = newSize;
		}

		size_t BoolSet::count() const
		{
			size_t count = 0;
			size_t size = _size;
			for (size_t i = 0; i < size; i++)
			{
				if (_bools[i])
				{
					count++;
				}
			}
			return(count);
		}

		size_t BoolSet::getSize() const
		{
			return(_size);
		}
	}
}