/**
 * @file  expression_evaluation.hpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 表达式求值
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023 Quenwaz
 * 
 */

#ifndef _h_expression_evaluation_included__
#define _h_expression_evaluation_included__
#include "iaq/iaq_defs.hpp"


namespace iaq::solve
{
struct ExpressionEvaluation : public iaq::AlgBase
{
    explicit ExpressionEvaluation(iaq::Version ver = iaq::Version::V1)
        : iaq::AlgBase(ver)
    {
    }

    iaq::Version GetSupportMaxVersion() const override
    {
        return iaq::Version::V1;
    }

    double compute(const std::string& expression);

private:
    struct Impl;
    Impl * impl_;
};
    
}

#endif //_h_expression_evaluation_included__