#ifndef _H_UNICODE_INCLUDED__
#define _H_UNICODE_INCLUDED__

#include "iaq/iaq_defs.hpp"


namespace iaq::solve::unicode
{

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
         * @brief 宽字符转Unicode字符串
         * 
         * @param wstr 宽字符数组
         * @param nstr 数组长度
         * @param unicodestr [out] Unicode字符串
         * @param upper 是否大写输出
         * @param keep_acsii 对于ASCII字符是否进行Unicode转换，true时， Unicode字符将以\u前缀以示区分。
         * @return size_t 返回Unicode字符串长度
         * @note 当unicodestr为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const wchar_t* wstr, size_t nstr, char* unicodestr, bool upper = false, bool keep_acsii=true) const;
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
         * @brief Unicode字符串转宽字符
         * 
         * @param unicodestr Unicode字符串
         * @param nstr Unicode字符串长度
         * @param wstr [out] 宽字符数组
         * @param exist_acsii 是否存在ASCII字符，存在的话Unicode字符前缀必须是\u
         * @return size_t 返回wstr长度
         * @note 当wstr为nullptr时， 返回其所需数组长度
         */
        size_t operator()(const char* unicodestr, size_t nstr, wchar_t* wstr, bool exist_acsii) const;
    };

}


#endif // _H_Unicode_INCLUDED__