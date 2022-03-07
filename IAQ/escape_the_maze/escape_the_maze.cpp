#include <queue>
#include <set>
#include "iaq/solve/escape_the_maze.hpp"

namespace __internal{
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
}

int iaq::solve::EscapeMaze::operator()(const char* maze[], size_t rsize, size_t csize)
{
        struct MazeIndex{
            size_t step;
            int ridx;
            int cidx;
        };

        std::set<std::pair<size_t, size_t>, __internal::PairComp> already_searchs;
        std::queue<MazeIndex> que_neb;
        auto get_neighbor = [maze, rsize, csize, &que_neb, &already_searchs](const MazeIndex& idx){
            if (idx.ridx >= rsize || idx.cidx >= csize || idx.ridx < 0 || idx.cidx < 0){
                return size_t(0);
            }
            
            const auto cur_step = idx.step + 1;
            const auto befoure_size = que_neb.size();
            if ((idx.ridx - 1) > 0  &&  maze[idx.ridx - 1][idx.cidx] == '1' && already_searchs.insert({idx.ridx - 1, idx.cidx}).second){
                que_neb.push({cur_step, idx.ridx - 1, idx.cidx});
            }

            if ((idx.cidx - 1) > 0  &&  maze[idx.ridx][idx.cidx - 1] == '1'&& already_searchs.insert({idx.ridx, idx.cidx - 1}).second){
                que_neb.push({cur_step,idx.ridx, idx.cidx - 1});
            }

            if ((idx.ridx + 1) < rsize && maze[idx.ridx + 1][idx.cidx] == '1'&& already_searchs.insert({idx.ridx + 1, idx.cidx}).second)
                que_neb.push({cur_step,idx.ridx + 1, idx.cidx});
                
            if ((idx.cidx + 1) < csize && maze[idx.ridx][idx.cidx + 1] == '1'&& already_searchs.insert({idx.ridx, idx.cidx + 1}).second)
                que_neb.push({cur_step,idx.ridx, idx.cidx + 1});
            
            return (que_neb.size() - befoure_size);
        };

        int step = -1;
        int way = 0;
        get_neighbor(MazeIndex{1, 0, 0});
        while (!que_neb.empty())
        {
            const auto top = que_neb.front();
            que_neb.pop();
            get_neighbor(top);

            if (top.cidx == (csize - 1) && top.ridx == (rsize - 1))
            {
                step = top.step;
                break;
            }
        }
        return step;
}