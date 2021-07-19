#include <cstddef>
#include <cstdint>
#include <cstring>
#include "iaq/solve/base64.hpp"


size_t iaq::solve::base64::Encode::operator()(const unsigned char* bytes, size_t nbyte, char* base64str) const
{
    if (bytes == nullptr || nbyte <= 0){
        return 0;
    }

    const size_t nbase64 = ((nbyte / 3) +  ((nbyte % 3) >0 ? 1 : 0)) * 4;
    if (base64str == nullptr){
        return nbase64;
    }
    
    for (size_t n_base64_pos = 0;n_base64_pos < nbase64; ++n_base64_pos)
    {
        size_t n_byte_idx = int(n_base64_pos * 6.0 / 8.0  + 0.5);
        unsigned char curbyte = '\x00';
        char base64char = '=';
        if (n_byte_idx < nbyte){
            curbyte = bytes[n_byte_idx];
        }
        size_t n_byte_pos = n_byte_idx * 8; 
        intptr_t previous_left_mv_pos = n_byte_pos - (n_base64_pos * 6);
        size_t previous_idx = previous_left_mv_pos > 0? n_byte_idx -1: n_byte_idx;
        if (previous_idx < nbyte)
        {
            unsigned char previous_byte = bytes[previous_idx];
            const size_t idx = 0x3f & (( uint8_t(previous_byte << (8-previous_left_mv_pos)) >> 2 )| uint8_t(curbyte >>( 8 - (6 - previous_left_mv_pos))));
            base64char = kBase64Char[idx];
        }
        base64str[n_base64_pos] = base64char;
    }

    return nbase64;
}




size_t iaq::solve::base64::Decode::operator()(const char* base64str, size_t nstr, unsigned char* bytes) const
{

}