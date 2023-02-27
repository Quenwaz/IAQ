#include <cstddef>
#include <cstdint>
#include <cstring>
#include "iaq/solve/hexadecimal_conversion.hpp"


iaq::solve::HexConv::ByteOrder iaq::solve::HexConv::CurrentByteOrder() const
{
    union{
        char byte;
        int integer;
    }un;

    un.integer = 0x12345678;
    if (un.byte == 0x12){
        return kBigEndian;
    }else if (un.byte == 0x78){
        return kLittleEndian;
    }
}

unsigned char * iaq::solve::HexConv::reverse(unsigned char * bytes, size_t nbyte) const
{
    for (size_t i =0;i < nbyte; ++i)
    {
        const size_t idx_last = nbyte - i - 1;
        if (idx_last <= i){
            break;
        }
        unsigned char tmp= bytes[i];
        bytes[i] = bytes[idx_last];
        bytes[idx_last] = tmp;
    }
    return bytes;
}

        
char* iaq::solve::HexConv::byte2hex(unsigned char byte, hexchar hex, bool toupper) const
{
        const unsigned char divisor = (byte >> 4);
        const unsigned char remainder = byte & 0x0f;
#define char2hex(ch)  ((ch) < 10 ? '0' + ch: (ch - 10) + ((toupper)?'A':'a'))
        hex[0] = char2hex(divisor);
        hex[1] =   char2hex(remainder);
#undef char2hex
    return hex;
}

unsigned char iaq::solve::HexConv::hex2byte(hexchar hex)const
{
#define hex2char(h)  (h > '9' ? ( h + 10 - (h >= 'a' ? 'a': 'A')) : (h - '0'))
        const unsigned char c1 = hex2char(hex[0]) << 4;
        const unsigned char c2 = hex2char(hex[1]);
#undef hex2char

        return c1 +  c2;
}

size_t iaq::solve::HexConv::operator()(const unsigned char* bytes, size_t nbyte, char* hexstr, bool toupper /*= true*/) const
{
    if (bytes == nullptr || nbyte == 0){
        return 0;
    }

    if (hexstr == nullptr){
        return (nbyte << 1) + 1;
    }

    for (size_t i =0;i < nbyte; ++i)
    {
        hexchar hexs={0, 0};
        byte2hex(bytes[i], hexs, toupper);
        hexstr[i<<1] = hexs[0];
        hexstr[(i<<1) + 1] =   hexs[1];
    }
    return nbyte << 1;
}

size_t iaq::solve::HexConv::operator()(intptr_t data, char* hexstr, bool toupper) const
{
    const size_t nbytes = sizeof(intptr_t);
    if (hexstr == nullptr){
        return (nbytes << 1) + 1;
    }

    unsigned char bytes[nbytes]={0};
    memcpy(bytes, &data, nbytes);

    if (CurrentByteOrder() == kLittleEndian)
    {
        this->reverse(bytes, sizeof(bytes));
    }
    return this->operator()(bytes, nbytes, hexstr, toupper);
}

size_t iaq::solve::HexConv::operator()(const char* hexstr, size_t nstr, intptr_t& data) const
{
    unsigned char bytes[sizeof(intptr_t)]={0};
    const size_t ret = this->operator()(hexstr, nstr, bytes);
    if (CurrentByteOrder() == kLittleEndian)
    {
        this->reverse(bytes, sizeof(bytes));
    }

    memcpy(&data, bytes, sizeof(intptr_t));
    return ret;
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
        hexchar hexs={hexstr[i], hexstr[i + 1]};
        bytes[i >> 1] = hex2byte(hexs);
    }
    return (nstr >> 1);
}