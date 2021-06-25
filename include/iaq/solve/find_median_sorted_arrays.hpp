#ifndef _h_longest_substring_without_repeat_included
#define _h_longest_substring_without_repeat_included
#include "iaq/iaq_defs.hpp"

namespace iaq::solve
{
    struct FindMedianSortedArrays : public iaq::AlgBase
    {
        explicit FindMedianSortedArrays(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }


        double operator()(std::vector<int>& nums1, std::vector<int>& nums2) const;
    };

}



#endif // _h_longest_substring_without_repeat_included