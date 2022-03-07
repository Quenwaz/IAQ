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
    
    auto step = iaq::solve::EscapeMaze()(maze, 9, 9);
    ASSERT_EQ(step, 17);
    
}