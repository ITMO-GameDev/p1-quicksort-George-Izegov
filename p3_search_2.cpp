#include "Dictionary.h"
#include <iostream>
#include "gtest/gtest.h"

TEST(DictionaryTest, DefaultConstruct)
{
    Dictionary<int, int> d;

    EXPECT_EQ(d.size(), size_t(0));
}

TEST(DictionaryTest, CopyConstruct)
{
    Dictionary<int, int> d;
    d.put(1, 1);
    d.put(2, 2);
    d.put(3, 3);

    auto d_copy = d;
    EXPECT_EQ(d_copy.size(), d.size());
}

TEST(DictionaryTest, CopyAssignment)
{
    Dictionary<int, int> d;
    d.put(1, 1);
    d.put(2, 2);
    d.put(3, 3);

    decltype(d) d_copy;
    d_copy[1] = -1;
    d_copy = d;
    EXPECT_EQ(d_copy.size(), d.size());
}

TEST(DictionaryTest, Put)
{
    Dictionary<int, int> d;

    d.put(1, 1);
    EXPECT_EQ(d.size(), size_t(1));
    d.put(2, 1);
    EXPECT_EQ(d.size(), size_t(2));
    d.put(2, 2);
    EXPECT_EQ(d.size(), size_t(2));
    d.put(3, 3);
    EXPECT_EQ(d.size(), size_t(3));
    EXPECT_EQ(d[1], 1);
    EXPECT_EQ(d[2], 2);
    EXPECT_EQ(d[3], 3);
}

TEST(DictionaryTest, Remove)
{
    Dictionary<int, int> d;

    d.put(1, 1);
    d.put(2, 2);
    d.put(3, 3);

    d.remove(2);
    EXPECT_EQ(d.size(), size_t(2));
    EXPECT_EQ(d[1], 1);
    EXPECT_FALSE(d.contains(2));
    EXPECT_EQ(d[3], 3);

    d.remove(1);
    EXPECT_EQ(d.size(), size_t(1));
    EXPECT_FALSE(d.contains(1));
    EXPECT_EQ(d[3], 3);

    d.remove(3);
    EXPECT_EQ(d.size(), size_t(0));
    EXPECT_FALSE(d.contains(3));
}

TEST(DictionaryTest, Subscript)
{
    Dictionary<int, std::string> dict;
    std::string strings[] = {
            "zero",
            "one",
            "two"
    };

    for (int i = 0; i < 3; ++i)
    {
        EXPECT_FALSE(dict.contains(i));
        dict.put(i, "none");
        dict[i] = strings[i];
        EXPECT_TRUE(dict.contains(i));
        EXPECT_EQ(dict[i], strings[i]);
    }
}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

