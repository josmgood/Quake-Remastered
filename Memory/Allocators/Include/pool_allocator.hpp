#pragma once

/*Standard Library*/
#include <iostream>
#include <memory>

/*Custom Library*/
#include "..\..\Internal\Include\auxiliary.h"
#include "..\..\Internal\Include\stack.hpp"

#include "base_allocator.h"

/*
*=====================================================================================
*
* POOL ALLOCATOR
*
* Each chunk is of the same size. Works great with containers.
* Allocates chunks based on status flag.
* Newly allocated chunks are moved to the back of the list.
* Newly deallocated chunks are moved to the front of the list.
* Internally holds a singly linked list of allocated and free chunks of memory.
*
* /tparam - size of each individual chunk
*
*=====================================================================================
*/
template<size_t chunkSize>
class  PoolAllocator
	: public BaseAllocator,
	public alloc::GetAllocateVoid,
	public alloc::GetDeallocate,
	public alloc::GetOwns,
	public alloc::GetExpand
{
public:
	/*
	*===============================================
	*	
	* _CHUNK
	*
	* Singly Linked list of memory - (Node).
	* Holds allocation information for the pool.
	* Tracks status of the block(FREE or ALLOCATED)
	* 
	* /m block -	raw data
	* /m state -	status of block and availability 
	* /m next -		header, links to other chunks
	*
	*===============================================
	*/
	struct _Chunk
	{
		enum STATE
			: int8	/*Minimize size of _Chunk*/
		{
			FREE = 0,
			ALLOCATED = 1
		};
		_Chunk				(void);
		internal::Byte*		block;
		STATE				state;
		_Chunk*				next;
	};
	struct _ChunkPacket
	{
		_ChunkPacket		(_Chunk* cu, _Chunk* pr);
		bool operator!=		(const _ChunkPacket& other);
		_Chunk* curr;
		_Chunk* prev;
	};

	/*
	 Constructor

	 Requires a default capacity(can be extended).
	 By default, the pool is able to automatically expand when needed.

	 /param - overall size of the pool
	 /param - allowance to automatically extend(optional)
	*/
	PoolAllocator						(size_t capacity, bool allowExpansion = true);

	/*
	 Destructor

	 Internally uses desetroy().
	*/
	virtual ~PoolAllocator				(void) override;

	/*
	 Allocate()
	 
	 If next allocation exceeds, the pool will automatically extended if allowed to.
	 Searches for a free block to be allocated.
	 If a free chunk is found, memory is assigned to a block and is marked allocated.
	 */
	virtual Block allocate				(void) override;

	/*
	 Deallocate(Block&)
	 
	 If the block can be found, it is freed and
	 the referred chunk will be set to free.

	 /param -	block being deallocated
	 /r -		if there is enough space for allocation...
					-> new allocated block ready for use.
				else...
					-> a DEAD_BLOCK with a null address.
	 */
	virtual void deallocate				(Block& block) override;

	/*
	 Owns(Block)
	 
	 Searches each chunk's memory for a matching base address.
	 
	 /param - block being validated
	 */
	virtual bool owns					(Block block) override;

	/*
	 Expand(size_t)
	 
	 Expands the capacity of the pool.
	 If intrinsic expansion is allowed, does not need to be manually called.
	 Internally calls _alocateNewChunk().
	 
	 /param -	amount of space to be added to capacity
	 /r -		does the pool own the block?
	 */
	virtual void expand					(size_t amount) override;

	/*
	 Reset()

	 Sets all member values to default values.
	*/
	virtual void reset					(void) override;

	/*
	 Destroy()
	 
	 Deallocates all memory and unlinks the chunk list.
	 Internally uses reset() after deallocation.
	 */
	virtual void destroy				(void) override;

	/*
	 GetChunkCapacity()
	 
	 /r - total capacity size
	 */
	size_t getChunkCapacity				(void) const;

	/*
	 GetNumAllocatedChunks()
	 
	 /r - total amount of chunks allocated (<= _capacity)*/
	size_t getNumAllocatedChunks		(void) const;
private:
	/*
	 _getNext(_Chunk*)
	 
	 Returns the next chunk in the list.

	 /param -	current chunk
	 /r -		the current chunk's next chunk (nullptr if none)
	 */
	_Chunk* _getNext				(_Chunk* chunk) const;

	/*
	 _setNext(_Chunk*, _Chunk*)
	 
	 Sets the next chunk in the list relative to the current chunk.

	 /param - current chunk
	 /param - to be next chunk
	  */
	void _setNext					(_Chunk* chunk, _Chunk* _next);

	/*
	 _findFree()
	 
	 Searches for a free chunk to used for allocation.
	 
	 /r - a packet of the current free node and the previous chunk 
			or a DEAD_CHUNK_PACKET if no free chunks found.
	 */
	_ChunkPacket _findFree(void);

	/*
	 _findChunk(Block&)
	 
	 Searches for a chunk by the block address.
	 
	 /r - a packet of the requested chunk and the previous chunk
			or a DEAD_CHUNK_PACKET if the chunk is not found.
	*/
	_ChunkPacket _findChunk(Block& block);

	/*
	 _isFree(_Chunk*)
	 
	 Determines if a chunk is free for allocation.

	 /r - is the chunk free?
	 */
	bool _isFree(_Chunk* chunk);

	/*
	 _allocateNewChunk()
	 
	 /r - a newly allocated chunk.
	 */
	_Chunk* _allocateNewChunk		(void);

	/*Front of the memory pool*/
	_Chunk*							_front;
	/*Back of the memory pool. Makes for easy allocation of new chunks.*/
	_Chunk*							_back;
	/*Position where free blocks at beginning end. Initialised after first deallocation*/
	_Chunk*							_free;
	/*Overall size of the pool. Can be expanded.*/
	size_t							_capacity;
	/*The current amount of chunks allocated.*/
	size_t							_numAllocatedChunks;
	/*Default return type for failed chunk searches.*/
	const _ChunkPacket				DEAD_CHUNK_PACKET;
};

#include "..\Source\pool_allocator.inl"