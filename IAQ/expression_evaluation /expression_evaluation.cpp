#include "iaq/solve/expression_evaluation.hpp"
#include "iaq/utility/utility.hpp"
#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using namespace iaq;

struct FnMaps {
  char code;
  std::string function;
};

struct ExpressionItem {
  std::string value;

  /// @brief 是否为操作数
  bool is_operand;
};


class OperatorMgr
{
public:
  struct Item{
    char short_name;
    int priority;
    enum OperatorType{
      unary = 1,
      binary,
      ternary
    }operator_type;

    union FnOperator
    {
      double(*_1p)(double);
      double(*_2p)(double,double);
      FnOperator(decltype(_1p) _ty): _1p(_ty){}
      FnOperator(decltype(_2p) _ty): _2p(_ty){}
    }call;
    
    std::string full_name;
  };
private:
  std::map<char, Item>  operators_;
  static OperatorMgr* instance_;
private:
  OperatorMgr() = default;
  ~OperatorMgr() = default;
public:
  static OperatorMgr* GetInstance();

  void AddOperator(char short_name, const Item& item);

};
OperatorMgr* OperatorMgr::instance_ = nullptr;

OperatorMgr* OperatorMgr::GetInstance()
{
  static OperatorMgr inst;
  return &inst;
}

void OperatorMgr::AddOperator(char short_name, const Item& item)
{
  if(!this->operators_.insert(std::make_pair(short_name, item)).second){
    throw std::runtime_error("Operator already exists.");
  }
}

#define DECLARE_OPERATOR(short_name, full_name,operator_type,priority, fn)\
OperatorMgr::GetInstance()->AddOperator(short_name,OperatorMgr::Item{short_name, priority,operator_type,fn,full_name});



std::string replace_function_code(std::string& inputs) {

  std::vector<FnMaps> maps = {
      {'S', "sqrt"},
      {'s', "sin"},
      {'c', "cos"},
      {'t', "tan"},
  };

  for (auto item : maps) {
    std::string code;
    code.push_back(item.code);
    utility::replace_all(inputs, item.function, code);
  }
  return inputs;
}

/**
 * @brief 中缀表达式切分
 * 
 * @param outputs [out] 返回中缀表达式列表
 * @param inputs 输入中缀表达式字符串
 * @param separator 切割的操作符
 * @return size_t 被切分后的操作数与操作符个数
 */
size_t splice_string(std::vector<ExpressionItem>& outputs,
                     const std::string& inputs, const std::string& separator) {
  for (size_t pos = 0, pos_before = 0; pos != std::string::npos;
       pos_before = pos + 1) {
    pos = inputs.find_first_of(separator, pos_before);
    std::string __tmp = inputs.substr(pos_before, pos - pos_before);
    
    if (!__tmp.empty()) outputs.push_back(ExpressionItem({__tmp, true}));
    if (pos != std::string::npos)
      outputs.push_back(ExpressionItem({inputs.substr(pos, 1), false}));
  }
  return outputs.size();
}



int priority(const std::string& _operator) {
  if (_operator.size() == 1) {
    char oper = _operator.front();
    switch (oper) {
      case ')':
        return 0;
      case '+': case '-':
        return 1;
      case '*': case '/': case '^': case 'S':
      case 's': case 'c': case 't':
        return 2;
      case '(':
        return 3;
      default:
        break;
    }
  }
  return 0;
}

/**
 * @brief 将切分后的中缀表达式转化为后缀表达式
 * 
 * @param exps 切分后的中缀表达式列表
 * @param suffix_expression [out] 返回逆波兰式
 * @return true 转换成功
 * @return false 表达式存在语法错误
 */
bool convert_to_postfix_expression(
    const std::vector<ExpressionItem>& exps,
    std::vector<ExpressionItem>& suffix_expression) {
  std::stack<ExpressionItem> stack_of_operator;
  for (size_t i = 0; i < exps.size(); ++i) {
    const ExpressionItem& exp = exps.at(i);
    if (exp.is_operand) {
      // 操作数
      suffix_expression.push_back(exp);
    } else {
      if (stack_of_operator.empty()) {
        stack_of_operator.push(exp);
      } else {
        if (exp.value == ")") {
          while (!stack_of_operator.empty() && stack_of_operator.top().value != "(") {
            suffix_expression.push_back(stack_of_operator.top());
            stack_of_operator.pop();
          }
          if (stack_of_operator.empty() || stack_of_operator.top().value != "("){
            return false;
          }
          stack_of_operator.pop();

        } else {
          const int current_priority = priority(exp.value);
          while (!stack_of_operator.empty()) {
            const auto top = stack_of_operator.top();
            if (priority(top.value) >= current_priority && top.value != "(") {
              suffix_expression.push_back(top);
              stack_of_operator.pop();
            } else {
              break;
            }
          }
          stack_of_operator.push(exp);
        }
      }
    }
  }

  while (!stack_of_operator.empty()) {
    auto & item = stack_of_operator.top();
    if (item.value == "(" || item.value == ")"){
      return false;
    }
    suffix_expression.push_back(stack_of_operator.top());
    stack_of_operator.pop();
  }

  return true;
}

struct solve::ExpressionEvaluation::Impl {};

double solve::ExpressionEvaluation::operator()(const char* expression) const
{
  std::string expstr(expression);
  // replace all spaces
  utility::replace_all(expstr, " ", "");

  // replace all function names with short names
  replace_function_code(expstr);

  // separates operands from operators
  std::vector<ExpressionItem> exps;
  splice_string(exps, expstr, "+-*/()^Ssct");

  // converts an infix expression to a postfix expression
  std::vector<ExpressionItem> suffix_exps;
  if (exps.size() < 2 || !convert_to_postfix_expression(exps, suffix_exps)){
    throw std::logic_error("expression syntax error");
  }

#ifdef _DEBUG
  expstr.clear();
  for (auto& item : suffix_exps)
  {
    // printf("[%s]",item.value.c_str());
    // fflush(stdout);
    expstr += item.value;
  }
#endif 

  std::stack<double> stack_of_operand;
  for (auto& item : suffix_exps) {
    if (item.is_operand) {
      if (!utility::isdigit(item.value.c_str())){
        throw std::logic_error("expression syntax error");
      }
      stack_of_operand.push(std::atof(item.value.c_str()));
    } else {
      if (item.value.size() == 1) {
        double rhs = stack_of_operand.top();
        stack_of_operand.pop();
        double lhs = 0;
        if (!std::isalpha(item.value.front())) {
          lhs = stack_of_operand.top();
          stack_of_operand.pop();
        }

        // 四则运算
        switch (item.value.front()) {
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
            stack_of_operand.push(lhs / rhs);
            break;
          case '^':
            stack_of_operand.push(powf(lhs, rhs));
            break;
          case 'S':
            stack_of_operand.push(sqrtf(rhs));
            break;
          case 's':
            stack_of_operand.push(sin(utility::degree_to_radian(rhs)));
            break;
          case 'c':
            stack_of_operand.push(cos(utility::degree_to_radian(rhs)));
            break;
          case 't':
            stack_of_operand.push(tan(utility::degree_to_radian(rhs)));
            break;
          default:
            throw std::logic_error("expression syntax error");
            break;
        }
      } else {
        throw std::logic_error("expression syntax error");
      }
    }
  }
  return stack_of_operand.top();
}