#ifndef _h_str_2_float_inclued__
#define _h_str_2_float_inclued__
#include "iaq/iaq_defs.hpp"
#include <stddef.h>

namespace solve
{
    struct str_to_float : public iaq::AlgBase
    {
        explicit str_to_float(iaq::Version ver=iaq::Version::V1)
        : iaq::AlgBase(ver) 
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }

        double operator()(const char* pszInput, size_t validbit = 3);
    };
}


#endif // _h_str_2_float_inclued__