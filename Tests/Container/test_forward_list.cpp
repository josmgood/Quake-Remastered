#include "..\..\Quake\Container\Include\forward_list.hpp"

#include <GTest\gtest.h>

#define NAME DISABLED_FORWARD_LIST

TEST(NAME, CONSTRUCTOR)
{
	ForwardList<int> list(3);
	list.pushBack(100);
	list.pushBack(9);
	list.pushFront(4);

	list.pushBack(232);

	EXPECT_EQ(3, list.size());
	EXPECT_EQ(3, list.maxSize());
	EXPECT_EQ(9, list.back());
	EXPECT_EQ(4, list.front());

	ForwardList<int> list2(list);
	EXPECT_EQ(3, list2.size());
	EXPECT_EQ(3, list2.maxSize());
	EXPECT_EQ(9, list2.back());
	EXPECT_EQ(4, list2.front());

	ForwardList<int> list3(list.begin(), list.end());
	EXPECT_EQ(3, list3.size());
	EXPECT_EQ(3, list3.maxSize());
	EXPECT_EQ(9, list3.back());
	EXPECT_EQ(4, list3.front());
}

/*Iterator mess up link connection.*/
TEST(NAME, FRONT)
{
	ForwardList<int> list(10);
	for (size_t i = 0; i < 10; i++)
	{
		list.pushFront(i);
		EXPECT_EQ(i, list.front());
	}
	size_t j = 0;
	ForwardList<int>::Iterator i = list.begin();
	std::cout << list << std::endl;
	while (i < list.end())
	{
		EXPECT_EQ(j, i.get().data);
		++i;
		++j;
	}

	for (size_t i = 0; i < 4; i++)
	{
		list.popFront();
	}
	/*j = 4;
	i = list.begin();
	while (i < list.end())
	{
		EXPECT_EQ(j, i.get().data);
		++i;
		++i;
	}*/
}