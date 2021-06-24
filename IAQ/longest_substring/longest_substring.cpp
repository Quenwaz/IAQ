#include <string>
#include "iaq/solve/longest_substring.hpp"
#include <map>

namespace __internal{
    int longest_substring_v1(const std::string& input)
    {
        int max_len = 0;
        int lastpos = 0;
        for (size_t i = 0;i < input.size(); ++i)
        {
            for (size_t j = lastpos; j < i; ++j)
            {
                if (input.at(j) == input.at(i)){
                    lastpos = j + 1;
                    break;
                }
            }
            const size_t subsize = i + 1 - lastpos;
            if (subsize > max_len)
                max_len = subsize;
        }
        return max_len;
    }

    int longest_substring_v2(const std::string& input)
    {
        std::map<char, size_t> mapstr;
        int max_len = 0;
        int lastpos = 0;
        for (size_t i = 0;i < input.size(); ++i)
        {
            auto insert_ret = mapstr.insert({input.at(i), i});
            if (!insert_ret.second){
                lastpos = lastpos <= insert_ret.first->second ? insert_ret.first->second + 1 : lastpos;
                insert_ret.first->second = i;
            }
  
            const size_t subsize = i + 1 - lastpos;
            if (subsize > max_len)
                max_len = subsize;
        }
        return max_len;
    }
}

int iaq::solve::LongSubStrNoRepeat::operator()(const char* pszInput) const
{
    std::string s(pszInput);
    if(this->version_ == iaq::V1)
        return __internal::longest_substring_v1(s);
    return __internal::longest_substring_v2(s);
}