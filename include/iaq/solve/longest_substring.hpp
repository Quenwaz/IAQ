#ifndef _h_longest_substring_without_repeat_included
#define _h_longest_substring_without_repeat_included
#include "iaq/iaq_defs.hpp"

namespace iaq::solve
{
    struct LongSubStrNoRepeat : public iaq::AlgBase
    {
        explicit LongSubStrNoRepeat(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V2;
        }


        int operator()(const char* pszInput) const;
    };

}



#endif // _h_longest_substring_without_repeat_included