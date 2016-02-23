#include "..\Include\base_allocator.h"

Block::Block(void* mem, size_t len)
	: memory(mem), length(len)
{
}

Block::Block(void)
	: memory(nullptr), length(0)
{
}

void Block::free(void)
{
	memory = nullptr;
	length = 0;
}

Block::operator bool(void) const
{
	return(memory != nullptr && length != 0);
}