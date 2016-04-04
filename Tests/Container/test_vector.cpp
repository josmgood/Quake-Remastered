#include "..\..\Quake\Container\Include\vector.hpp"

#include <GTest\gtest.h>

#define NAME VECTOR

TEST(NAME, CONSTRUCTOR)
{
	Vector<int> vector;
	EXPECT_EQ(DEFAULT_CONTAINER_SIZE, vector.maxSize());

	vector.pushBack(10);
	vector.pushBack(100);
	vector.pushBack(1000);
	EXPECT_EQ(1000, vector.back());
	EXPECT_EQ(3, vector.size());
}