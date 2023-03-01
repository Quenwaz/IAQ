#include "iaq/solve/expression_evaluation.hpp"
#include <string>
#include <stack>
#include <vector>
#include <cmath>

using namespace iaq;


struct FnMaps{
    char code;
    std::string function;
};

struct  ExpressionItem{
    std::string value;

    /// @brief 是否为操作数
    bool  is_operand;
};

void replace_all(std::string &base, const std::string& src, const std::string& des)
{
	std::string::size_type len_of_src = src.size();
	std::string::size_type len_of_des = des.size();
	std::string::size_type pos=base.find(src); 
	while ((pos != std::string::npos))
	{
		base.replace(pos, len_of_src, des);
		pos=base.find(src, (pos+len_of_des));
	}
}

std::string replace_function_code(std::string& inputs)
{
    std::vector<FnMaps> maps = {
        {'S', "sqrt"},
        {'s', "sin"},
    };

    for (auto item : maps)
    {
        std::string code;
        code.push_back(item.code);
        replace_all(inputs, item.function,code);
    }
    return inputs;
}

size_t splice_string(std::vector<ExpressionItem>& outputs, const std::string& inputs, const std::string& separator)
{
    for(size_t pos = 0, pos_before = 0; pos != std::string::npos;pos_before = pos + 1)
    {
        pos = inputs.find_first_of(separator,pos_before);
        std::string __tmp= inputs.substr(pos_before,pos-pos_before);
        if (!__tmp.empty())
            outputs.push_back(ExpressionItem({__tmp,true}));
        if (pos != std::string::npos)
            outputs.push_back(ExpressionItem({inputs.substr(pos,1),false}));
    }
    return outputs.size();
}

int priority(const std::string& _operator)
{
    if (_operator.size() == 1){
        char oper = _operator.front();
        switch (oper)
        {
        case ')':
            return 0;
        case '+': case '-':
            return 1;
        case '*': case '/': case '^': case 'S':
            return 2;
        case '(':
            return 3;
        default:
            break;
        }
    }
    return 0;
}

bool convert_to_postfix_expression(const std::vector<ExpressionItem>& exps, std::vector<ExpressionItem>& suffix_expression)
{
    std::stack<ExpressionItem>  stack_of_operator;
    for (size_t i = 0 ;i < exps.size(); ++i)
    {
        const ExpressionItem& exp = exps.at(i);
        if (exp.is_operand){
            // 操作数
            suffix_expression.push_back(exp);
        }else{

            if (stack_of_operator.empty()){
                stack_of_operator.push(exp);
            }else{
                if (exp.value == ")"){
                    while (stack_of_operator.top().value != "(")
                    {
                        suffix_expression.push_back(stack_of_operator.top());
                        stack_of_operator.pop();
                    }
                    stack_of_operator.pop();
                    
                }else{
                    const int current_priority = priority(exp.value);
                    while (!stack_of_operator.empty())
                    {
                        const auto top = stack_of_operator.top();
                        if (priority(top.value) >= current_priority && top.value != "("){
                            suffix_expression.push_back(top);
                            stack_of_operator.pop();
                        }else{
                            break;
                        }
                    }
                    stack_of_operator.push(exp);
                }

            }

        }

    }

    while (!stack_of_operator.empty())
    {
        suffix_expression.push_back(stack_of_operator.top());
        stack_of_operator.pop();
    }

    return true;
}

struct solve::ExpressionEvaluation::Impl
{

};

double solve::ExpressionEvaluation::compute(const char* expression)
{   

    std::string expstr(expression);
    replace_function_code(expstr);
    std::vector<ExpressionItem> exps;
    splice_string(exps,expression,"+-*/()^S");

    std::vector<ExpressionItem> suffix_exps;
    convert_to_postfix_expression(exps,suffix_exps);

    expstr.clear();
    for (auto& item : suffix_exps) expstr += item.value;


    std::stack<double> stack_of_operand;
    for (auto& item : suffix_exps)
    {
        if (item.is_operand){
            stack_of_operand.push(std::atof(item.value.c_str()));
        }else{
            if (item.value.size() == 1){
                double rhs = stack_of_operand.top();
                stack_of_operand.pop();
                double lhs = 0;
                if (!std::isalpha(item.value.front())){
                    lhs = stack_of_operand.top();
                    stack_of_operand.pop();
                }

                // 四则运算
                switch (item.value.front())
                {
                case '+':
                    stack_of_operand.push(lhs + rhs);
                    break;
                case '-':
                    stack_of_operand.push(lhs - rhs);
                    break;
                case '*':
                    stack_of_operand.push(lhs * rhs);
                    break;
                case '/':
                    stack_of_operand.push(lhs/rhs);
                    break;
                case '^':
                    stack_of_operand.push(powf(lhs,rhs));
                    break;
                case 'S':
                    stack_of_operand.push(sqrtf(rhs));
                    break;
                case 's':
                    stack_of_operand.push(sqrtf(rhs));
                    break;
                default:
                    break;
                }
            }else{
                // 函数
            }
        }

    }
    return stack_of_operand.top();
}