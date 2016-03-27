#include "..\..\Include\Internal\batch_queue.hpp"

namespace internal
{
	template<typename TAllocator,
		size_t maxBatch>
	BatchQueue<TAllocator, maxBatch>::BatchQueue(TAllocator* parent, QBool flushes)
		: _parent(parent), _flags(), _numQueued(), _hasFlushed(false), _flushOnClear(flushes)
	{
	}

	template<typename TAllocator, 
		size_t maxBatch>
	BatchQueue<TAllocator, maxBatch>::~BatchQueue()
	{
		clear();
	}

	template<typename TAllocator,
		size_t maxBatch>
	void BatchQueue<TAllocator, maxBatch>::flush()
	{
		for (size_t i = 0; i < maxBatch; i++)
		{
			if (_isQueued(i))
			{
				_parent->allocate(_queue[i]);
				_queue[i] = Block();
			}
		}
		_flags.clear();
		_numQueued--;
		_hasFlushed = true;
	}

	template<typename TAllocator, 
		size_t maxBatch>
	void BatchQueue<TAllocator, maxBatch>::queue(Block& block)
	{
		_checkFlushStatus();
		if (isFull())
		{
			flush();
		}
		for (size_t i = 0; i < maxBatch; i++)
		{
			if (_isDequeued(i))
			{
				_queue[i] = block;
				_flags[i] = QUEUED;
				_numQueued++;
				return;
			}
		}
	}

	template<typename TAllocator, 
		size_t maxBatch>
	void BatchQueue<TAllocator, maxBatch>::queue(size_t index, Block& block)
	{
		_checkFlushStatus();
		if (isFull())
		{
			flush();
		}
		if (_isDequeued(index))
		{
			_queue[index] = block;
			_flags[index] = QUEUED;
			_numQueued++;
		}
	}

	template<typename TAllocator,
		size_t maxBatch>
	size_t BatchQueue<TAllocator, maxBatch>::dequeue(Block& block)
	{
		for (size_t i = 0; i < maxBatch; i++)
		{
			if (_isQueued(i))
			{
				if (addressMatch(block.address, _queue[i].address))
				{
					_queue[i] = nullptr;
					_flags[i] = DEQUEUED;
					_numQueued--;
					return(i);
				}
			}
		}
		return(BATCH_NULL_INDEX);
	}

	template<typename TAllocator,
		size_t maxBatch>
	Block& BatchQueue<TAllocator, maxBatch>::dequeue(size_t index)
	{
		if (_isQueued(index))
		{
			_queue[i] = nullptr;
			_flags[i] = DEQUEUED;
			_numQueued--;
		}
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::owns(Block block) const
	{
		for (size_t i = 0; i < maxBatch; i++)
		{
			if (_isQueued(i))
			{
				if (addressMatch(block.address, _queue[i].address))
				{
					return true;
				}
			}
		}
		return false;
	}

	template<typename TAllocator,
		size_t maxBatch>
		void BatchQueue<TAllocator, maxBatch>::clear()
	{
		for (size_t i = 0; i < maxBatch; i++)
		{
			if (_isQueued(i))
			{
				delete _queue[i].address;
			}
		}
		_flags.clear();
		_numQueued = 0;
	}

	template<typename TAllocator, 
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::isFull() const
	{
		return(_flags.all());
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::isEmpty() const
	{
		return(!_numQueued);
	}

	template<typename TAllocator,
		size_t maxBatch>
	void BatchQueue<TAllocator, maxBatch>::setClearProtocol(QBool flushes)
	{
		_flushOnClear = flushes;
	}

	template<typename TAllocator,
		size_t maxBatch>
	size_t BatchQueue<TAllocator, maxBatch>::getMaxBatchSize() const
	{
		return(maxBatch);
	}

	template<typename TAllocator,
		size_t maxBatch>
	size_t BatchQueue<TAllocator, maxBatch>::getNumQueued() const 
	{
		return(_numQueued);
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::hasFlushed() const
	{
		return(_hasFlushed);
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::flushesOnClear() const
	{
		return(_flushOnClear);
	}

	template<typename TAllocator, 
		size_t maxBatch>
	std::ostream& BatchQueue<TAllocator, maxBatch>::operator<<(const std::ostream& os) const
	{
		/*Replace with QString when it is finished*/
		std::string message = "BatchQueue: \n";
		//message += "\t"
		return(os);
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::_isQueued(size_t index) const 
	{
		return(_flags[index] == QUEUED);
	}

	template<typename TAllocator,
		size_t maxBatch>
	QBool BatchQueue<TAllocator, maxBatch>::_isDequeued(size_t index) const 
	{
		return(_flags[index] == DEQUEUED);
	}

	template<typename TAllocator,
		size_t maxBatch>
	void BatchQueue<TAllocator, maxBatch>::_checkFlushStatus()
	{
		if (_hasFlushed)
		{
			_hasFlushed.setFalse();
		}
	}
}