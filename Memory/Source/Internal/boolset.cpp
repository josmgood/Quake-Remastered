#include "..\..\Include\Internal\boolset.h"

namespace internal
{
	BoolSet::BoolSet()
	{
	}

	BoolSet::BoolSet(size_t size, QBool initial)
		: _bools(new QBool[size]), _size(size)
	{
		for (size_t i = 0; i < size; i++)
		{
			_bools[i] = initial;
		}
	}

	BoolSet::BoolSet(const BoolSet& bSet)
		: _bools(new QBool[bSet._size]), _size(bSet._size)
	{	
		*this = bSet;
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

	QBool BoolSet::all() const
	{
		size_t size = _size;
		for (size_t i = 0; i < size; i++)
		{
			if (!_bools[i])
			{
				return false;
			}
		}
		return true;
	}

	QBool BoolSet::any() const
	{
		size_t size = _size;
		for (size_t i = 0; i < size; i++)
		{
			if (_bools[i])
			{
				return true;
			}
		}
		return false;
	}

	QBool BoolSet::none() const
	{
		size_t size = _size;
		for (size_t i = 0; i < size; i++)
		{
			if (_bools[i])
			{
				return false;
			}
		}
		return true;
	}

	void BoolSet::operator=(const BoolSet& bSet)
	{
		_size = bSet._size;
		_bools = new QBool[_size];
		//std::copy(bSet._bools, bSet._bools + _size, _bools);
		internal::copy(bSet._bools, _size, _bools);
	}

	QBool& BoolSet::operator[](size_t index) const
	{
		return _bools[index];
	}

	void BoolSet::resize(size_t amount)
	{
		size_t oldSize = _size;
		size_t newSize = amount + oldSize;
		QBool* newBools = new QBool[newSize];
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
		return count;
	}

	size_t BoolSet::getSize() const
	{
		return _size;
	}
}