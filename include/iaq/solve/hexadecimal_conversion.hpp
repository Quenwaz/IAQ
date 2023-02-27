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

        enum ByteOrder
        {
            kBigEndian,
            kLittleEndian
        };

        /**
         * @brief 当前CPU的字节序
         * 
         * @return ByteOrder 返回字节序
         */
        ByteOrder CurrentByteOrder() const;    

        /**
         * @brief 字节数组反转
         * 
         * @param bytes 字节数组
         * @param nbyte 数组长度
         * @return unsigned char* 返回反转后的字节数组
         */
        unsigned char * reverse(unsigned char * bytes, size_t nbyte) const;

        /// 十六进制2字节数组
        typedef char hexchar[2] ;
        
        /**
         * @brief 字节转换为十六进制
         * 
         * @param byte 字节
         * @param hex [out] 十六进制
         * @param toupper 是否输出大写十六进制
         * @return char* 返回转换后的十六进制
         */
        char* byte2hex(unsigned char byte, hexchar hex, bool toupper) const;

        /**
         * @brief 十六进制转换为byte
         * 
         * @param hex 十六进制
         * @return unsigned char byte
         */
        unsigned char hex2byte(hexchar hex)const;

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

        /**
         * @brief 整数转十六进制字符串
         * 
         * @param data 整数
         * @param hexstr [out] 十六进制字符串
         * @param toupper 是否大写
         * @return size_t 返回输出数组长度
         */
        size_t operator()(intptr_t data, char* hexstr, bool toupper = true) const;

        /**
         * @brief 十六进制字符串转整数
         * 
         * @param hexstr 十六进制字符串
         * @param nstr 字符串长度
         * @param data [out] 整数
         * @return size_t 返回字符串长度
         */
        size_t operator()(const char* hexstr, size_t nstr, intptr_t& data) const;
    };

}

#endif // _h_hexadecimal_conversion_included__