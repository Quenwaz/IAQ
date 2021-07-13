#include <stddef.h>
#include "iaq/solve/hexadecimal_conversion.hpp"


size_t iaq::solve::HexConv::operator()(unsigned char* bytes, size_t nbyte, char* hexstr) const
{
    if (bytes == nullptr || nbyte == 0){
        return 0;
    }

    if (hexstr == nullptr){
        return nbyte * 2 + 1;
    }

    for (size_t i =0;i < nbyte; ++i)
    {
        const unsigned char divisor = (bytes[i] >> 4);
        const unsigned char remainder = bytes[i] & 0x0f;
        hexstr[i<<1] =  (divisor) < 10 ? '0' + divisor: (divisor - 10) + 'A';
        hexstr[(i<<1) + 1] =   (remainder) < 10 ? '0'+ remainder: (remainder - 10) + 'A';;
    }
    return nbyte * 2;
}