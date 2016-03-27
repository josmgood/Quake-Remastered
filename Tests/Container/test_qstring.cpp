#include "..\..\Quake\Container\Include\qstring.h"

#include <GTest\gtest.h>

#define NAME QSTRING

TEST(NAME, PUSH_FRONT)
{
	QString string(15);
	char expected = 'W';
	string.pushFront(expected);
	EXPECT_EQ(expected, string.getFront());
}

//TEST()

TEST(NAME, HAS)
{
	QString string("775191asdfaf0362asdfasdfmljk");
	EXPECT_EQ(true, string.has('3'));
	EXPECT_EQ(false, string.has("ashdjfoiasodfkj"));
	EXPECT_EQ(false, string.has("7519 1asdfa"));
}

TEST(NAME, GET_FRONT)
{
	/*QString string("Hello World");
	EXPECT_EQ('H', string.getFront());
	string.pushFront('_');
	EXPECT_EQ('_', string.getFront());*/
}

TEST(NAME, RESERVE)
{
	/*QString string("Hello World");
	size_t len = string.getLength() + 1;
	string.reserve(len);
	EXPECT_EQ(len, string.getMaxLength());*/
}