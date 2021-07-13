#ifndef _h_hexadecimal_conversion_included__
#define _h_hexadecimal_conversion_included__
#include "iaq/iaq_defs.hpp"


namespace iaq::solve
{
    struct HexConv : public iaq::AlgBase
    {
        explicit HexConv(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }

        size_t operator()(unsigned char* bytes, size_t nbyte, char* hexstr) const;
    };

}

#endif // _h_hexadecimal_conversion_included__