#include "gtest/gtest.h"
#include "iaq/solve/escape_the_maze.hpp"


TEST(test_escape_the_maze, t1)
{
    const char* maze[] = {
        "111101011",
        "111100100",
        "111111101",
        "111101011",
        "111111111",
        "111111011",
        "110111111",
        "110111111",
        "011111111"
    };
    
    ASSERT_EQ(iaq::solve::EscapeMaze()(maze, 9, 9), 17);
    ASSERT_EQ(iaq::solve::EscapeMaze(iaq::V2)(maze, 9, 9), 17);
}

TEST(test_escape_the_maze, t2)
{
    const char* maze[] = {
        "111111110",
        "100110110",
        "111010100",
        "001010111",
        "111010001",
        "100010111",
        "110010100",
        "011010100",
        "001111111"
    };
    
    ASSERT_EQ(iaq::solve::EscapeMaze()(maze, 9, 9), 17);
    ASSERT_EQ(iaq::solve::EscapeMaze(iaq::V2)(maze, 9, 9), 17);
}