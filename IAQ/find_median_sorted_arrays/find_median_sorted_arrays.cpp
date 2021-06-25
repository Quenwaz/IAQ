#include <vector>
#include "iaq/solve/find_median_sorted_arrays.hpp"



double iaq::solve::FindMedianSortedArrays::operator()(std::vector<int>& nums1, std::vector<int>& nums2) const
{
    double dresult = 0;
    int lastval = 0;
    size_t size_all = nums1.size() + nums2.size();
    const int median = size_all * 0.5;
    for (size_t i_lhs = 0, i_rhs = 0, curidx = 0;i_rhs < size_all || i_lhs < size_all; ++curidx)
    {
        int lhs = 0, rhs = 0;
        bool is_not_exist_left = false;
        if (i_lhs < nums1.size()){
            lhs = nums1.at(i_lhs);
        }else is_not_exist_left = true;

        if (i_rhs < nums2.size()){
            rhs = nums2.at(i_rhs);
            if(is_not_exist_left){
                lhs = rhs + 1;
            }
        }else if (!is_not_exist_left) rhs = lhs + 1;

        const int curval = lhs < rhs? lhs : rhs;
        if (curidx == median)
        {
            if(size_all % 2 == 0)
            {
                // 偶数
                dresult = (curval + lastval) * 0.5;
            }else{
                // 奇数
                dresult = curval;
            }
            break;
        }

        if (lhs < rhs) ++i_lhs; 
        else ++i_rhs;
        lastval= curval;
    }
    return dresult;
}