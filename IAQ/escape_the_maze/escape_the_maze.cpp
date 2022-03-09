#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include "iaq/solve/escape_the_maze.hpp"

namespace __internal{

    template<typename T>struct HasSpecifyMember
    {
    private:
        template<typename U> static auto Check(int) -> decltype(std::declval<U>().size(), std::declval<U>().push(std::declval<typename U::value_type>()), std::true_type());
        template<typename U> static auto Check(...) -> decltype(std::false_type());
    public:
        static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
    };


    struct PairComp
    {
        typedef std::pair<size_t, size_t> PairIndex;
        bool operator()(const PairIndex& lhs, const PairIndex & rhs) const
        {
            if (lhs.first != rhs.first){
                return lhs.first < rhs.first;
            }

            if (lhs.second != rhs.second){
                return lhs.second < rhs.second;
            }

            return false;
        }
    };

    struct EscapeMazeSolution
    {
        struct MazeIndex{
            size_t step;
            int ridx;
            int cidx;
        };

        EscapeMazeSolution(const char* maze[], size_t rsize, size_t csize)
            : maze_(maze), row_size_(rsize), col_size_(csize)
        {
        }   

        int bfs()
        {
            int step = -1;
            int traversal_times = 0;
            std::queue<MazeIndex> que_neb;
            get_neighbor(MazeIndex{1, 0, 0}, que_neb);
            while (!que_neb.empty())
            {
                const auto top = que_neb.front();
                que_neb.pop();
                get_neighbor(top, que_neb);
                if (top.cidx == (col_size_ - 1) && top.ridx == (row_size_ - 1))
                {
                    step = top.step;
                    break;
                }
                ++traversal_times;
            }
            printf("(%s)traversal_times:%d\n", __FUNCTION__, traversal_times);
            return step;
        }

        int dfs()
        {
            int step = -1;
            int traversal_times = 0;
            std::stack<MazeIndex> stack_neb;
            get_neighbor(MazeIndex{1, 0, 0}, stack_neb);
            while (!stack_neb.empty())
            {
                const auto top = stack_neb.top();
                stack_neb.pop();
                get_neighbor(top, stack_neb);
                if (top.cidx == (col_size_ - 1) && top.ridx == (row_size_ - 1))
                {
                    step = top.step;
                    break;
                }
                ++traversal_times;
            }
  
            printf("(%s)traversal_times:%d\n", __FUNCTION__, traversal_times);
            return step;
        }

    private:
        template<typename Container , typename std::enable_if<HasSpecifyMember<Container>::value>::type * = nullptr>
        size_t get_neighbor(const MazeIndex& idx, Container& container)
        {
            if (idx.ridx >= row_size_ || idx.cidx >= col_size_ || idx.ridx < 0 || idx.cidx < 0){
                return size_t(0);
            }

            const auto cur_step = idx.step + 1;
            const auto befoure_size = container.size();
            if ((idx.ridx - 1) > 0  &&  maze_[idx.ridx - 1][idx.cidx] == '1' && already_searchs_.insert({idx.ridx - 1, idx.cidx}).second){
                container.push({cur_step, idx.ridx - 1, idx.cidx});
            }

            if ((idx.cidx - 1) > 0  &&  maze_[idx.ridx][idx.cidx - 1] == '1'&& already_searchs_.insert({idx.ridx, idx.cidx - 1}).second){
                container.push({cur_step,idx.ridx, idx.cidx - 1});
            }

            if ((idx.ridx + 1) < row_size_ && maze_[idx.ridx + 1][idx.cidx] == '1'&& already_searchs_.insert({idx.ridx + 1, idx.cidx}).second)
                container.push({cur_step,idx.ridx + 1, idx.cidx});
                
            if ((idx.cidx + 1) < col_size_ && maze_[idx.ridx][idx.cidx + 1] == '1'&& already_searchs_.insert({idx.ridx, idx.cidx + 1}).second)
                container.push({cur_step,idx.ridx, idx.cidx + 1});
            
            return (container.size() - befoure_size);
        }


        // 限制其只能在栈上分配内存
        void* operator new(size_t size) = delete;
        void operator delete(void* ptr) = delete;
    private:
        std::set<std::pair<size_t, size_t>, __internal::PairComp> already_searchs_;
        const char** maze_;
        size_t row_size_;
        size_t col_size_;
    };

    int escape_maze_bfs(const char* maze[], size_t rsize, size_t csize)
    {
        return EscapeMazeSolution(maze, rsize, csize).bfs();
    }


    int escape_maze_dfs(const char* maze[], size_t rsize, size_t csize)
    {
        return EscapeMazeSolution(maze, rsize, csize).dfs();
    }



}

int iaq::solve::EscapeMaze::operator()(const char* maze[], size_t rsize, size_t csize)
{
    if (maze == nullptr || rsize == 0 || csize  == 0){
        return -1;
    }

    switch (this->version_)
    {
    case iaq::V1: return __internal::escape_maze_bfs(maze, rsize, csize);
    case iaq::V2: return __internal::escape_maze_dfs(maze, rsize, csize);
    default:
        break;
    }

    std::stack<int> stack_test_;
    

    return -1;
}