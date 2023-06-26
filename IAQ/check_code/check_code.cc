#include <cstdint>
#include <string>
#include <cstring>
#include <bitset>
#include <cmath>
#include <unordered_map>
#include "iaq/solve/check_code.hpp"



intptr_t iaq::solve::operator "" _B2I(const char* b)
{
    return std::stoi(b, nullptr, 2);
}

std::string iaq::solve::operator "" _I2B(unsigned long long i)
{
    std::bitset<9> bitint(i);
    return bitint.to_string();
}


namespace __method{

    /**
     * @brief 计算海明验证码位数。2^m-m>=k+1, m表示验证码位数，k表示数据位数
     * 
     * @param data_length 数据位数
     * @return uintptr_t 返回验证码位数
     */
    uintptr_t __number_of_check_code(int data_length){
        uintptr_t check_code_length = 0;
        for(;(pow(2, check_code_length) - check_code_length) < (data_length + 1); ++check_code_length);
        return check_code_length;
    }

    bool __is_power_of_two(uintptr_t num){
        auto d = log(num) / log(2);
        return std::abs(std::floor(d) - d) < 1e-10? true: false;
    }

    uintptr_t __next_data_index(uintptr_t current_index){
        if (current_index == 0){
            return 3;
        }

        for(;;)
        {
            ++current_index;
            if (!__is_power_of_two(current_index)){
                break;
            }
        }
        return current_index;
    }

    intptr_t hamming(const std::string& data, std::string& validate){
        uintptr_t len_of_check_code = __number_of_check_code(data.size());
        uintptr_t amount_data_length = len_of_check_code + data.size();
        std::unordered_map<uintptr_t, char>  char_index_map;
        for(size_t i = 0, prev = 0;i < data.size(); ++i){
            prev = __next_data_index(prev);
            char_index_map[prev] = data.at(i);
        }

        amount_data_length += 1;
        for (size_t i = 1; i < amount_data_length; ++i)
        {
            if (__is_power_of_two(i)){
                intptr_t c = -1;
                for(auto pair : char_index_map)
                {
                    if ((i & pair.first) == 0)
                        continue;

                    int i = pair.second - '0';
                    if (c == -1){
                        c = i;
                    }else{
                        c^=i;
                    }
                }
                validate.push_back(c + '0');
            }else{
                validate.push_back(char_index_map[i]);
            }
        }
        return 1;
    }


}


intptr_t iaq::solve::CheckCode::operator()(Method method, const char* _data, char* _validate) const
{
    auto t1 = 8_I2B;
    auto t2 = 1001_B2I;
    std::string data(_data);
    std::string validate(_validate==nullptr? "": _validate);
    switch (method)
    {
    case Method::kHamming:
    {
        const int ret = __method::hamming(data, validate);
        if (_validate != nullptr)
            memcpy(_validate, validate.c_str(), validate.size());
        return ret;
    }
    default:
        break;
    }
    return -1;
}