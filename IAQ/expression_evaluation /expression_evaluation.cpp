#include "iaq/solve/expression_evaluation.hpp"

#include <cmath>
#include <functional>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "iaq/utility/utility.hpp"

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

#define DECLARE_OPERATOR(short_name, full_name, priority, fn) \
  extern double operator_##fn(const std::vector<double>&);
#include "operator_define.hpp"
#undef DECLARE_OPERATOR

class OperatorMgr {
  enum OperatorPriority {
    kPriorityMin = 0,
#define DECLARE_OPERATOR(short_name, full_name, priority, fn) kPriority_##fn,
#include "operator_define.hpp"
    kPriorityMax
  };
#undef DECLARE_OPERATOR

 private:
  std::string all_operator_string_;
  static OperatorMgr* instance_;

 private:
  OperatorMgr();
  ~OperatorMgr() = default;

  /**
   * @brief 获取所有操作符组成的字符串
   *
   */
  const std::string get_all_operator() const { return all_operator_string_; }

  /**
   * @brief 获取指定操作符的优先级
   *
   * @param ch 操作符
   * @return int 优先级
   */
  int get_priority(char ch);

  /**
   * @brief 替换表达式中函数全称为内置的简称
   *
   * @param expression 表达式
   */
  void replace_function_to_operator(std::string& expression);

  /**
   * @brief 中缀表达式切分
   *
   * @param outputs [out] 返回中缀表达式列表
   * @param inputs 输入中缀表达式字符串
   * @param separator 切割的操作符
   * @return size_t 被切分后的操作数与操作符个数
   */
  size_t splice_string(std::vector<ExpressionItem>& outputs,
                       const std::string& inputs, const std::string& separator);

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
      std::vector<ExpressionItem>& suffix_expression);

  /**
   * @brief 根据指定运算符进行运算
   *
   * @param ch 运算符
   * @param args 参数，目前最大支持2个参数，其顺序为 [右操作数,左操作数]
   * @return double 返回运算结果
   */
  double compute(char ch, const std::vector<double>& args);

 public:
  static OperatorMgr* GetInstance();

  /**
   * @brief 计算字符串表达式的值
   *
   * @param expression 字符串表达式
   * @return double 返回计算的值
   */
  double compute(const std::string& expression);
};

OperatorMgr* OperatorMgr::instance_ = nullptr;

OperatorMgr::OperatorMgr() : all_operator_string_("()") {
#define DECLARE_OPERATOR(short_name, full_name, priority, fn) \
  all_operator_string_.push_back(short_name);
#include "operator_define.hpp"
#undef DECLARE_OPERATOR
}

OperatorMgr* OperatorMgr::GetInstance() {
  static OperatorMgr inst;
  return &inst;
}

int OperatorMgr::get_priority(char ch) {
  switch (ch) {
    case ')':
      return OperatorPriority::kPriorityMin;
    case '(':
      return OperatorPriority::kPriorityMax;
#define DECLARE_OPERATOR(short_name, full_name, priority, fn) \
  case short_name:                                            \
    return priority;
#include "operator_define.hpp"
    default:
      throw std::logic_error("Operator does not exist");
      break;
  }
#undef DECLARE_OPERATOR
}

void OperatorMgr::replace_function_to_operator(std::string& expression) {
#define DECLARE_OPERATOR(short_name, full_name, priority, fn) \
  utility::replace_all(expression, full_name, std::string(1, short_name));
#include "operator_define.hpp"
#undef DECLARE_OPERATOR
}

size_t OperatorMgr::splice_string(std::vector<ExpressionItem>& outputs,
                                  const std::string& inputs,
                                  const std::string& separator) {
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

bool OperatorMgr::convert_to_postfix_expression(
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
          while (!stack_of_operator.empty() &&
                 stack_of_operator.top().value != "(") {
            suffix_expression.push_back(stack_of_operator.top());
            stack_of_operator.pop();
          }
          if (stack_of_operator.empty() ||
              stack_of_operator.top().value != "(") {
            return false;
          }
          stack_of_operator.pop();

        } else {
          const int current_priority =
              OperatorMgr::GetInstance()->get_priority(exp.value.front());
          while (!stack_of_operator.empty()) {
            const auto top = stack_of_operator.top();
            if (OperatorMgr::GetInstance()->get_priority(top.value.front()) >=
                    current_priority &&
                top.value != "(") {
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
    auto& item = stack_of_operator.top();
    if (item.value == "(" || item.value == ")") {
      return false;
    }
    suffix_expression.push_back(stack_of_operator.top());
    stack_of_operator.pop();
  }

  return true;
}

double OperatorMgr::compute(char ch, const std::vector<double>& args) {
  switch (ch) {
#define DECLARE_OPERATOR(short_name, full_name, priority, fn) \
  case short_name:                                            \
    return operator_##fn(args);
#include "operator_define.hpp"
    default:
      throw std::logic_error("Operator does not exist");
      break;
  }
#undef DECLARE_OPERATOR
}

double OperatorMgr::compute(const std::string& expression) {
  std::string expstr(expression);
  // replace all spaces
  utility::replace_all(expstr, " ", "");

  // replace all function names with short names
  OperatorMgr::GetInstance()->replace_function_to_operator(expstr);

  // separates operands from operators
  std::vector<ExpressionItem> exps;
  splice_string(exps, expstr, OperatorMgr::GetInstance()->get_all_operator());

  // converts an infix expression to a postfix expression
  std::vector<ExpressionItem> suffix_exps;
  if (exps.size() < 2 || !convert_to_postfix_expression(exps, suffix_exps)) {
    throw std::logic_error("expression syntax error");
  }

#ifdef _DEBUG
  expstr.clear();
  printf("\n");
  fflush(stdout);
  for (auto& item : suffix_exps) {
    printf("[%s]", item.value.c_str());
    fflush(stdout);
    expstr += item.value;
  }
#endif

  std::stack<double> stack_of_operand;
  for (auto& item : suffix_exps) {
    if (item.is_operand) {
      if (!utility::isdigit(item.value.c_str())) {
        throw std::logic_error("expression syntax error");
      }
      stack_of_operand.push(std::atof(item.value.c_str()));
    } else {
      if (item.value.size() == 1) {
        std::vector<double> args;
        // 先出栈的为右操作符
        args.push_back(stack_of_operand.top());
        stack_of_operand.pop();
        // 只有非字母才为二元操作
        if (!std::isalpha(item.value.front())) {
          // 后出栈的为左操作符
          args.push_back(stack_of_operand.top());
          stack_of_operand.pop();
        }
        stack_of_operand.push(
            OperatorMgr::GetInstance()->compute(item.value.front(), args));

      } else {
        throw std::logic_error("expression syntax error");
      }
    }
  }
  return stack_of_operand.top();
}

double solve::ExpressionEvaluation::operator()(const char* expression) const {
  return OperatorMgr::GetInstance()->compute(expression);
}