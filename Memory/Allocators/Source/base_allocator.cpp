#include "..\Include\base_allocator.h"

Block::Block(void* mem, size_t len)
	: address(mem), size(len)
{
}

Block::Block(void)
	: address(nullptr), size(0)
{
}

void Block::free(void)
{
	address = nullptr;
	size = 0;
}

Block::operator bool(void) const
{
	return(address != nullptr && size > 0);
}