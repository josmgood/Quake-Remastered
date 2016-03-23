#pragma once

template<typename TIterator, typename TValue>
TIterator find(TIterator begin, TIterator end, TValue value)
{
	for (TIterator i = begin; i < end; ++i)
	{
		if (i.get() == value)
		{
			return i;
		}
	}
	return end;
}

template<typename TIterator, typename TValue>
TIterator find_last(TIterator begin, TIterator end, TValue value)
{
	TIterator last = end;
	for (TIterator i = begin; i < end; ++i)
	{
		if (i.get() == value)
		{
			last = i;
		}
	}
	return last;
}

template<typename TIterator, typename TConditional>
TIterator find_if(TIterator begin, TIterator end, TConditional conditional)
{
	for (TIterator i = begin; i < end; ++i)
	{
		if (conditional(i.get()))
		{
			return i;
		}
	}
	return end;
}

template<typename TIterator, typename TConditional, typename TValue>
TIterator find_if_val(TIterator begin, TIterator end, TConditional conditional, TValue value)
{
	for (TIterator i = begin; i < end; ++i)
	{
		if (conditional(value, i.get()))
		{
			return i;
		}
	}
	return end;
}

template<typename TIterator, typename TConditional, typename TValue>
TIterator find_last_if_val(TIterator begin, TIterator end, TConditional conditional, TValue value)
{
	TIterator last = end;
	for (TIterator i = begin; i < end; ++i)
	{
		if (conditional(value, i.get()))
		{
			last = i;
		}
	}
	return last;
}

template<typename TIterator, typename TConditional>
TIterator find_if_not(TIterator begin, TIterator end, TConditional conditional)
{
	for (TIterator i = begin; i < end; ++i)
	{
		if (!conditional(i.get()))
		{
			return i;
		}
	}
	return end;
}

template<typename TIterator, typename TConditional, typename TValue>
TIterator find_if_not_val(TIterator begin, TIterator end, TConditional conditional, TValue value)
{
	for (TIterator i = begin; i < end; ++i)
	{
		if (!conditional(value, i.get()))
		{
			return i;
		}
	}
	return end;
}