#include <cstddef>
#include <cstdint>
#include <cstring>
#include "iaq/solve/unicode.hpp"
#include "iaq/solve/hexadecimal_conversion.hpp"
#include <cstdio>



size_t iaq::solve::unicode::Encode::operator()(const wchar_t* wstr, size_t nstr, char* unicodestr, bool upper, bool keep_acsii) const
{
    if (wstr == nullptr || nstr <= 0){
        return 0;
    }

    const size_t nunicode =  nstr * 6;
    if (unicodestr == nullptr){
        return nunicode;
    }

    HexConv hexconv;
    HexConv::hexchar hexs;
    for (size_t i = 0, j = 0;i < nstr; ++i, ++j)
    {
        wchar_t ch = wstr[i];
        if (keep_acsii && ch < 128){
            unicodestr[j] = ch;
            continue;
        }
        if (keep_acsii)
        {
            unicodestr[j] = '\\';
            unicodestr[++j] = 'u';
        }else --j;

        hexconv.byte2hex(ch >>8, hexs, upper);
        unicodestr[++j] = hexs[0];
        unicodestr[++j] = hexs[1];
        hexconv.byte2hex(ch&0x00ff, hexs, upper);
        unicodestr[++j] = hexs[0];
        unicodestr[++j] = hexs[1];
    }

    return nunicode;
}



size_t iaq::solve::unicode::Decode::operator()(const char* unicodestr, size_t nstr, wchar_t* wstr, bool exist_acsii) const
{
    if (unicodestr == nullptr || nstr <= 0){
        return 0;
    }

    HexConv hexconv;
    for (size_t i = 0, j = 0;i < nstr; ++j)
    {   
        wchar_t& ch = wstr[j];
        if (unicodestr[i] =='\\' && unicodestr[i + 1] == 'u'){
            i+=2;
        }else if(exist_acsii){
            ch = unicodestr[i];
            ++i;
            continue;
        }

        HexConv::hexchar hex1 = {unicodestr[i], unicodestr[i + 1]};
        ch = hexconv.hex2byte(hex1);
        i += 2;
        HexConv::hexchar hex2 = {unicodestr[i], unicodestr[i + 1]};
        ch <<= 8;
        ch |= hexconv.hex2byte(hex2);
        i += 2;
    }

    return nstr;
}