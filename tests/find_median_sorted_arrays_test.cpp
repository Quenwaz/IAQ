#include "gtest/gtest.h"
#include "iaq/solve/find_median_sorted_arrays.hpp"



TEST(FindMedianSortedArraysTest, t1)
{
    iaq::solve::FindMedianSortedArrays find_median_sorted_arrays;
    std::vector<int> n1={1, 3};
    std::vector<int> n2={2};
    ASSERT_EQ(find_median_sorted_arrays(n1, n2), 2);

    n1={1, 2};
    n2={3, 4};
    ASSERT_EQ(find_median_sorted_arrays(n1, n2), 2.5);

    n1={};
    n2={1};
    ASSERT_EQ(find_median_sorted_arrays(n1, n2), 1);

    n1={2};
    n2={};
    ASSERT_EQ(find_median_sorted_arrays(n1, n2), 2);

    n1={1, 3};
    n2={2, 7};
    ASSERT_EQ(find_median_sorted_arrays(n1, n2), 2.5);
}

