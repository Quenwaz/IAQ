#include "iaq/solve/str2float.hpp"

double solve::StrToFloat::operator()(const char* pszInput, size_t validbit/* = 3*/)  const
{
    if (pszInput == NULL){
        return 0;
    }

    bool bNegative = false;
    size_t decimal = 0;
    size_t integer = 0;
    for(;*pszInput != '\0';++pszInput)
    {
        const char ch = *pszInput;
        if (ch == '-'){
            bNegative = true;
        }else if(ch == '.'){
            decimal = 1;
        }else if(ch >= '0' && ch <= '9')
        {
            if (decimal > 0){
                // 小数部分
                decimal *= 10;
            }
            // 整数部分
            integer *= 10;
            integer += ch - '0';
            
        }else{
            // 存在非数字
            return 0;
        }
    }
    decimal = decimal==0?1:decimal;
    double result = double(integer)/decimal;
    // 精度
    if (decimal > 1){
        // 存在小数
        size_t precision = 1;
        while (validbit-->0) precision*=10;
        result = double(int(result * precision + .5))/precision;
    }
    if (bNegative) result =-result;
    return result;
}