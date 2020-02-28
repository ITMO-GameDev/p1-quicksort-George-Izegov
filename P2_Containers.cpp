#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include "Array.h"






TEST(ArrayTest, DefaultConstructor)
{
	Array<int> array_default;
	EXPECT_EQ(array_default.size(), size_t(0));

	auto it = array_default.iterator();
	EXPECT_FALSE(it.hasNext());
	EXPECT_FALSE(it.hasPrev());
}

TEST(ArrayTest, CapacityConstructor)
{
	Array<int> arr(10);
	EXPECT_EQ(arr.size(), 0);

	auto it = arr.iterator();
	EXPECT_FALSE(it.hasNext());
	EXPECT_FALSE(it.hasPrev());
}


TEST(ArrayTest, CopyAssignment)
{
	Array<int> array_default;
	for (auto i = 0; i < 10; ++i)
		array_default.insert(i);

	Array<int> arr;
	arr = array_default;
	auto it = arr.iterator();

	EXPECT_EQ(array_default.size(), size_t(10));
	EXPECT_EQ(arr.size(), size_t(10));
	for (auto i = 0; it.hasNext(); it.next(), ++i)
		EXPECT_EQ(it.get(), i);
}

TEST(ArrayTest, Insert)
{
	Array<int> array_default;
	for (auto i = 0; i < 10; ++i)
		array_default.insert(i);
	EXPECT_EQ(array_default.size(), size_t(10));

	auto it = array_default.iterator();
	for (auto i = 0; it.hasNext(); it.next(), ++i)
		EXPECT_EQ(it.get(), i);
}

TEST(ArrayTest, InsertAt)
{
	Array<int> array_default;
	for (auto i = 0; i < 10; ++i)
		array_default.insert(size_t(i), i);
	EXPECT_EQ(array_default.size(), size_t(10));

	auto it = array_default.iterator();
	for (auto i = 0; i < 10; ++i, it.next())
		EXPECT_EQ(it.get(), i);

	for (auto i = 0; i < 10; ++i)
		array_default.insert(size_t(i), i);
	EXPECT_EQ(array_default.size(), size_t(20));

	auto it2 = array_default.iterator();
	for (auto i = 0; i < 10; ++i, it2.next())
		EXPECT_EQ(it2.get(), i);
	for (auto i = 0; i < 10; ++i, it2.next())
		EXPECT_EQ(it2.get(), i);
}

TEST(ArrayTest, Remove)
{
	Array<int> array_default;
	array_default.insert(3);
	array_default.remove(0);
	EXPECT_EQ(array_default.size(), size_t(0));

	for (auto i = 0; i < 10; ++i)
		array_default.insert(i);
	array_default.remove(0);
	EXPECT_EQ(array_default.size(), size_t(9));
	array_default.remove(array_default.size() - 1);
	EXPECT_EQ(array_default.size(), size_t(8));
	array_default.remove((array_default.size() - 1) / 2);
	EXPECT_EQ(array_default.size(), size_t(7));
}


TEST(ArrayTest, Iterators)
{
	Array<int> array_default;
	for (auto i = 0; i < 10; ++i)
		array_default.insert(i);

	auto it = array_default.iterator();
	it.toIndex(5);

	EXPECT_EQ(it.get(), 5);
}


int main(int argc, char* argv[])
{

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

