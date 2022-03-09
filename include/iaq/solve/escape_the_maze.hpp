/**
 * @file escape_the_maze.hpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 求解走出迷宫， 需要的步数
 * @version 0.1
 * @date 2022-03-04
 * 
 * @copyright Copyright (c) 2022 Quenwaz
 * 
 */
#ifndef _escape_the_maze_included_
#define _escape_the_maze_included_
#include "iaq/iaq_defs.hpp"


namespace iaq::solve
{
    struct EscapeMaze : public iaq::AlgBase
    {
        explicit EscapeMaze(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V2;
        }


        /**
         * @brief 0是墙，1可通行， (0, 0)是起点， (row - 1, col - 1)是终点
         *        计算走出迷宫所需步数
         * @param maze 迷宫
         * @param rsize 行数
         * @param csize 列数
         * @return int 返回步数， 不通则为-1
         */
        int operator()(const char* maze[], size_t rsize, size_t csize);
    };

}

#endif // _escape_the_maze_included_