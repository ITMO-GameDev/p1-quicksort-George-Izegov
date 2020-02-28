#include "gtest/gtest.h"
#include <random>
#include "sort.cpp"

TEST(SortTest, AlreadySortedArray)
{
	const int size = 5; 
	int a[size] = { 1,2,3,4,5 };
	int b[size] = { 1,2,3,4,5 };
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });

	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, SameNumberArray)
{
	const int size = 5;
	int a[size] = { 1,1,1,1,1 };
	int b[size] = { 1,1,1,1,1 };
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });
	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, BackSortedArray)
{
	const int size = 5;
	int a[size] = { 5,4,3,2,1 };
	int b[size] = { 1,2,3,4,5 };
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });
	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, RandomArray)
{
	const int size = 5;
	int a[size] = { 6,3,5,8,3 };
	int b[size] = { 3,3,5,6,8 };
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });
	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, RepeatNumbersArray)
{
	const int size = 5;
	int a[size] = { 6,6,5,3,3 };
	int b[size] = { 3,3,5,6,6 };
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });
	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, AlreadySortedArrayQuick)
{
	const int size = 57;
	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = i;
		b[i] = i;
	}
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });

	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, SameNumberArrayQuick)
{
	const int size = 57;
	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = 1;
		b[i] = 1;
	}
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });

	EXPECT_EQ(isEqual(a, b, size), true);
}

TEST(SortTest, BackSortedArrayQuick)
{
	const int size = 57;
	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = size - i - 1;
		b[i] = i;
	}
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });

	EXPECT_EQ(isEqual(a, b, size), true);
}

int compare(const void* x1, const void* x2)   // функция сравнения элементов массива
{
	return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

TEST(SortTest, RandomArrayQuick)
{
	const int size = 57;
	int a[size];
	int b[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = rand();
		b[i] = a[i];
	}
	Sort(a, a + size - 1, [](int a, int b) {return a < b; });
	std::qsort(b, size, sizeof(int), compare);
	EXPECT_EQ(isEqual(a, b, size), true);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

