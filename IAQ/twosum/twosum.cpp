#include <vector>
#include <map>
#include "iaq/solve/two_sum.hpp"

namespace __internal{

std::vector<int> two_sum_v1(const std::vector<int>& nums, int target)
{
    std::vector<int> result;
    result.reserve(2);
    for (size_t i = 0; i < nums.size() && result.empty(); ++i)
    {
        for(size_t j = 0; j < nums.size(); ++j)
        {
            if (i == j) 
                continue;
            
            if ((nums[i] + nums[j]) == target){
                result.push_back(i);
                result.push_back(j);
                break;
            }
        }
    }

    return result;
}

std::vector<int> two_sum_v2(const std::vector<int>& nums, int target)
{
    std::map<int,size_t> mapnums;
    std::vector<int> result;
    result.reserve(2);
    for (size_t i = 0; i < nums.size() && result.empty(); ++i)
    {
        const auto val = nums.at(i);
        const auto ret = mapnums.emplace(val, i);
        if (!ret.second){
            result.push_back(ret.first->second);
            result.push_back(i);
            break;
        }
        mapnums.emplace(target - val, i);
    }

    return result;
}

std::vector<int> two_sum_v3(const std::vector<int>& nums, int target)
{
    std::map<int,size_t> mapnums;
    std::vector<int> result;
    result.reserve(2);
    for (size_t i = 0; i < nums.size() && result.empty(); ++i)
    {
        const auto val = nums.at(i);
        const auto ret = mapnums.emplace(val, i);
        if (!mapnums.emplace(target - val, i).second && i != ret.first->second){
            result.push_back(ret.first->second);
            result.push_back(i);
            break;
        }
        mapnums.emplace(val, i);
    }

    return result;
}

}


std::vector<int> solve::TwoSum::operator()(const std::vector<int>& nums, int target)  const
{
    if(nums.size() < 2){
        return {};
    }

    switch (this->version_)
    {
    case iaq::V2: return __internal::two_sum_v2(nums, target);
    case iaq::V3: return __internal::two_sum_v3(nums, target);
    case iaq::V1:
    default:
        return __internal::two_sum_v1(nums, target);
    }
}