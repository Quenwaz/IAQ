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

        /**
         * @brief 字节转十六进制字符串
         * 
         * @param bytes 字节数组
         * @param nbyte 数组长度
         * @param hexstr [out] 十六进制字符串
         * @param toupper 是否大写， 默认大写
         * @return size_t 返回十六进制字符串长度
         * @note 当hexstr为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const unsigned char* bytes, size_t nbyte, char* hexstr, bool toupper = true) const;

        /**
         * @brief 十六进制字符串转字节数组
         * 
         * @param hexstr 十六进制字符串
         * @param nstr 字符串长度
         * @param bytes [out] 字节数组
         * @return size_t 字节数组长度
         * @note 当bytes为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const char* hexstr, size_t nstr, unsigned char* bytes) const;
    };

}

#endif // _h_hexadecimal_conversion_included__