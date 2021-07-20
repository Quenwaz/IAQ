#ifndef _H_BASE64_INCLUDED__
#define _H_BASE64_INCLUDED__

#include "iaq/iaq_defs.hpp"


namespace iaq::solve::base64
{
    /// Base64基础字符
    const char kBase64Char[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    /**
     * @brief 根据字符获取其索引
     * 
     * @param ch 字符
     * @return uint8_t 索引
     * @note 依赖kBase64Char变量的定义
     */
    uint8_t base64_char_index(char ch);


    struct Encode : public iaq::AlgBase
    {
        explicit Encode(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }


        /**
         * @brief 字节转Base64字符串
         * 
         * @param bytes 字节数组
         * @param nbyte 数组长度
         * @param base64str [out] Base64字符串
         * @return size_t 返回Base64字符串长度
         * @note 当base64str为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const unsigned char* bytes, size_t nbyte, char* base64str, bool safe = false) const;
    };


    struct Decode : public iaq::AlgBase
    {
        explicit Decode(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }


        /**
         * @brief Base64字符串转字节
         * 
         * @param base64str Base64字符串
         * @param nstr Base64字符串长度
         * @param bytes [out] 字节数组
         * @return size_t 返回bytes长度
         * @note 当bytes为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const char* base64str, size_t nstr, unsigned char* bytes) const;
    };

}


#endif // _H_BASE64_INCLUDED__