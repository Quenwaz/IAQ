#include <stddef.h>
#include "iaq/solve/hexadecimal_conversion.hpp"


size_t iaq::solve::HexConv::operator()(const unsigned char* bytes, size_t nbyte, char* hexstr, bool toupper /*= true*/) const
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
#define char2hex(ch)  ((ch) < 10 ? '0' + ch: (ch - 10) + ((toupper)?'A':'a'))
        hexstr[i<<1] = char2hex(divisor);
        hexstr[(i<<1) + 1] =   char2hex(remainder);
#undef char2hex
    }
    return nbyte * 2;
}

size_t iaq::solve::HexConv::operator()(const char* hexstr, size_t nstr, unsigned char* bytes) const
{
    if (hexstr == nullptr || nstr == 0 || (nstr % 2) != 0){
        return 0;
    }

    if (bytes == nullptr){
        return (nstr >> 1) + 1;
    }

    for (size_t i =0;i < nstr; i += 2)
    {
        const char h1 = hexstr[i];
        const char h2 = hexstr[i + 1];
#define hex2char(h)  (h > '9' ? ( h + 10 - (h >= 'a' ? 'a': 'A')) : (h - '0'))
        const unsigned char c1 = hex2char(h1) << 4;
        const unsigned char c2 = hex2char(h2);
#undef hex2char
        bytes[i >> 1] = c1 +  c2;
    }
    return (nstr >> 1);
}