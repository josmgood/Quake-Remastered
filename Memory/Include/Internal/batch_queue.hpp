#pragma once


#include "..\Allocator\base_allocator.h"
#include "boolset.h"

#define DEFAULT_BATCH_SIZE	8
#define BATCH_NULL_INDEX	-1
#define QUEUED				1
#define DEQUEUED			0

namespace internal
{
	template<typename TAllocator, 
		size_t maxBatch = DEFAULT_BATCH_SIZE>
	class BatchQueue
	{
	public:
		BatchQueue(TAllocator* parent);
		~BatchQueue();

		void flush();
		void queue(Block& block);
		void queue(size_t index, Block& block);

		size_t dequeue(Block& block);
		Block& dequeue(size_t index);
		bool owns(Block block) const;
		void clear();
		bool isFull() const;

		size_t getMaxBatchSize() const;
		size_t getNumQueued() const;
		bool hasFlushed() const;
	private:
		bool _isQueued(size_t index) const;
		bool _isDequeued(size_t index) const;
		void _checkFlushStatus() const;

		TAllocator* _parent;
		Block _queue[maxBatch];
		BoolSet _flags;
		size_t _numQueued;
		bool _hasFlushed;
	};
}