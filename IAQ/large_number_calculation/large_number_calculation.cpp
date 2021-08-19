#include <cstddef>
#include "iaq/solve/large_number_calculation.hpp"
#include <string>
#include <cstring>
#include <algorithm>

namespace __internal{

#define OPERATOR_DECLARE(name) std::string name(const std::string& lhs, const std::string& rhs)

OPERATOR_DECLARE(Add)
{
    if (lhs.empty()) return rhs;
    if (rhs.empty()) return lhs;

    std::string result;
    const auto max_size = std::max(lhs.size(), rhs.size());
    int carry = 0;
    for (int nlhs = lhs.size() - 1, nrhs = rhs.size() -1; nlhs < lhs.size() || nrhs < rhs.size();)
    {
        short l_num = 0, r_num = 0;
        if (nlhs >= 0){
            l_num = lhs.at(nlhs) - '0';
            --nlhs;
        }

        if (nrhs >= 0){
            r_num = rhs.at(nrhs) - '0';
            --nrhs;
        }

        const auto ret = l_num + r_num + carry;
        result.push_back((ret % 10) + '0');
        carry = ret / 10;
    }

    std::reverse(result.begin(),result.end());
    return result;
}

OPERATOR_DECLARE(Subtract)
{

}


OPERATOR_DECLARE(Multiply)
{

}


OPERATOR_DECLARE(Divide)
{

}

#undef OPERATOR_DECLARE
}

size_t iaq::solve::CalculateBigNumbers::operator()(Operator opera, const char* lhs, const char* rhs, char* result, int* n_result) const
{
    if (lhs == nullptr  || rhs == nullptr || result == nullptr || n_result == nullptr)
        return 0;

    std::string __result;
    switch (opera)
    {
    case kAdd:
        __result = __internal::Add(lhs, rhs);
        break;
    case kSubtract:
        __result = __internal::Subtract(lhs, rhs);
        break;
    case kMultiply:
        __result = __internal::Multiply(lhs, rhs);
        break;
    case kDivide:
        __result = __internal::Divide(lhs, rhs);
        break;
    default:
        break;
    }
    
    memcpy(result, __result.data(), *n_result);
    return __result.size();
}