/**
 * @file twosum.cpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 两数之和
 * @version 0.1
 * @date 2021-06-15
 * 
 * @copyright Copyright (c) 2021 Quenwaz
 * 
 */
#ifndef _h_two_sum_included__
#define _h_two_sum_included__
#include "iaq/iaq_defs.hpp"

namespace solve
{
    struct TwoSum : public iaq::AlgBase
    {
        explicit TwoSum(iaq::Version ver=iaq::Version::V1)
        : iaq::AlgBase(ver)
        {

        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V3;
        }

        std::vector<int> operator()(const std::vector<int>& nums, int target)  const;
    };

}

#endif // _h_two_sum_included__