/**
 * @file check_code.hpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 实现各类校验码，如海明校验、奇偶校验、循环冗余校验
 * @version 0.1
 * @date 2023-06-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __HEADER_CHECK_CODE_INCLUDED___
#define __HEADER_CHECK_CODE_INCLUDED___
#include "iaq/iaq_defs.hpp"


namespace iaq::solve
{

intptr_t operator "" _B2I(const char* b);
std::string operator "" _I2B(unsigned long long  i);

struct CheckCode : public iaq::AlgBase
{
    enum class Method{
        kOddEven,   // 奇偶校验
        kHamming,   // 海明(汉明)校验
        kCRC        // 循环冗余校验
    };



    explicit CheckCode(iaq::Version ver = iaq::Version::V1)
        : iaq::AlgBase(ver)
    {
    }

    iaq::Version GetSupportMaxVersion() const override
    {
        return iaq::Version::V1;
    }

    intptr_t operator()(Method method, const char* data, char* validate) const;

};
    
}



#endif // __HEADER_CHECK_CODE_INCLUDED___