#include "..\..\Quake\Container\Include\qstack.hpp"

#include <GTest\gtest.h>

#define NAME QSTACK

TEST(NAME, CONSTRUCTOR)
{
	QStack<int> one(5);
	for (size_t i = 1; i < 11; ++i)
	{
		one.push(i * i);
	}
	QStack<int> two(one);
	EXPECT_EQ(5, two.getSize());
	EXPECT_EQ(25, two.peek());

	for (size_t i = 1; i < 6; ++i)
	{
		one.pop();
	}
	EXPECT_EQ(0, one.getSize());
}