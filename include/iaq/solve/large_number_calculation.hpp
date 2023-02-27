#ifndef _h_large_number_calculation_included
#define _h_large_number_calculation_included

#include "iaq/iaq_defs.hpp"

namespace iaq::solve
{
    struct CalculateBigNumbers : public iaq::AlgBase
    {
        explicit CalculateBigNumbers(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }
        
        enum Operator{
            kAdd,
            kSubtract,
            kMultiply,
            kDivide
        };

        size_t operator()(Operator opera, const char* lhs, const char* rhs,char* result, int* n_result) const;
    };

}



#endif // _h_large_number_calculation_included