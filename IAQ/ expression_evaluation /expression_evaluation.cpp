#include <string>
#include "iaq/solve/expression_evaluation.hpp"
#include <stack>
#include <vector>

using namespace iaq;

size_t splice_string(std::vector<std::string>& outputs, const std::string& inputs, const std::string& separator)
{
    for(size_t pos = 0, pos_before = 0; pos != std::string::npos;pos_before = pos + 1)
    {
        pos = inputs.find_first_of(separator,pos_before);
        std::string __tmp= inputs.substr(pos_before,pos-pos_before);
        if (!__tmp.empty())
            outputs.push_back(__tmp);
        if (pos != std::string::npos)
            outputs.push_back(inputs.substr(pos,1));
    }
    return outputs.size();
}

struct solve::ExpressionEvaluation::Impl
{

};

double solve::ExpressionEvaluation::compute(const std::string& expression)
{   
    std::vector<std::string> eee;
    splice_string(eee,expression,"+-*/()");
    return 0;
}