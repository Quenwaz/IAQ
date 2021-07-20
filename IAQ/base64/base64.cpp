#include <cstddef>
#include <cstdint>
#include <cstring>
#include "iaq/solve/base64.hpp"


uint8_t iaq::solve::base64::base64_char_index(char ch)
{
    if ( ch >= 'A' && ch <= 'Z'){
        return ch - 64 - 1;
    }else if ( ch >= 'a' && ch <= 'z'){
        return 26 + ch - 'a';
    }else if ( ch >= '0' && ch <= '9'){
        return 52 + ch - '0';
    }else if (ch == '+' || ch=='-'){
        return 62;
    }else if (ch == '/'|| ch=='_'){
        return 63;
    }
}

size_t iaq::solve::base64::Encode::operator()(const unsigned char* bytes, size_t nbyte, char* base64str, bool safe ) const
{
    if (bytes == nullptr || nbyte <= 0){
        return 0;
    }

    size_t nbase64 = ((nbyte / 3) +  ((nbyte % 3) >0 ? 1 : 0)) * 4;
    nbase64 = safe && (nbyte % 3)>0? nbase64 - (3- (nbyte % 3)): nbase64;
    if (base64str == nullptr){
        return nbase64;
    }
    
    intptr_t n_remainder = 0;
    for (size_t n_base64_pos = 0, n_byte_idx = 0;n_base64_pos < nbase64; ++n_base64_pos)
    {   
        // 当前字节索引
        n_byte_idx = (n_base64_pos + 1) * 6 / 8;

        // 当前字节
        unsigned char curbyte = '\x00';

        // 如果不满3的倍数， 默认base64为=
        char base64char = '=';
        if (n_byte_idx < nbyte){
            curbyte = bytes[n_byte_idx];
        }
   
        n_remainder = (n_byte_idx * 8) - (n_base64_pos * 6);
        const size_t previous_idx = n_remainder > 0? n_byte_idx - 1: n_byte_idx;
        if (previous_idx < nbyte)
        {
            unsigned char previous_byte = bytes[previous_idx];
            const size_t idx = 0x3f & ((previous_byte << (6-n_remainder)) | (curbyte >>( 8 - (6 - n_remainder))));
            base64char = kBase64Char[idx];
            if (safe){
                if (base64char=='+') base64char = '-';
                else if(base64char=='/') base64char='_';
            }
        }
        base64str[n_base64_pos] = base64char;
    }
    
    return nbase64;
}



size_t iaq::solve::base64::Decode::operator()(const char* base64str, size_t nstr, unsigned char* bytes) const
{
    if (base64str == nullptr || nstr <= 0){
        return 0;
    }

    size_t n_base64_size = nstr;
    while ((n_base64_size % 4) != 0) ++n_base64_size;

    size_t nbyte = (n_base64_size / 4) * 3;
    for (size_t i = nstr - 1; base64str[i] == '='; --i)--nbyte;
    nbyte -= n_base64_size - nstr;
    if (bytes == nullptr){
        return nbyte;
    }

    for (size_t n_base64_pos =0, n_byte_idx = 0;n_byte_idx < nbyte;++n_byte_idx)
    {
        n_base64_pos = n_byte_idx * 8 / 6;
        const char cur_base64_char = base64str[n_base64_pos];

        intptr_t n_miss_bit = ((n_byte_idx + 1) * 8) - ((n_base64_pos + 1) * 6);
        uint8_t base64_idx = base64_char_index(cur_base64_char);
        uint8_t base64_next_idx = 0;
        size_t base64_next_pos = n_base64_pos + 1;
        if (base64_next_pos < nstr){
            base64_next_idx = base64_char_index(base64str[base64_next_pos]);
        }
        
        bytes[n_byte_idx] = (base64_idx << n_miss_bit) | (base64_next_idx >> (6-n_miss_bit));
    }
    return nbyte;
}