#include "gtest/gtest.h"
#include "type_reader.h"

using namespace cpputils;

TEST(block_size_tests, single_element_size)
{
    std::tuple<value_reader<int>> single_element;

    ASSERT_EQ(sizeof(int), block_size(single_element));
}

TEST(block_size_tests, array_size)
{
    std::tuple<array_reader<int, 10>> array_def;

    ASSERT_EQ(sizeof(int) * 10, block_size(array_def));
}

TEST(block_size_tests, mixed_tuple_size)
{
    std::tuple<value_reader<int>, array_reader<int, 9>> mixed_def;

    ASSERT_EQ(sizeof(int) + (sizeof(int) * 9), block_size(mixed_def));
}

TEST(block_size_tests, tuple_in_tuple)
{
    std::tuple<int, std::tuple<int>> tuple_in_tuple_def;

    ASSERT_EQ(2 * sizeof(int), block_size(tuple_in_tuple_def));
}
