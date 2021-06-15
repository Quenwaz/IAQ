#ifndef _h_two_sum_included__
#define _h_two_sum_included__
#include "iaq/iaq_defs.hpp"

namespace solve
{
    struct two_sum : public iaq::AlgBase
    {
        explicit two_sum(iaq::Version ver=iaq::Version::V1)
        : iaq::AlgBase(ver)
        {

        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V3;
        }

        std::vector<int> operator()(const std::vector<int>& nums, int target);
    };

}

#endif // _h_two_sum_included__