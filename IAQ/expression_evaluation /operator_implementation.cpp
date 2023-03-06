#include "iaq/utility/utility.hpp"
#include <vector>
#include <cmath>

using namespace iaq;

double operator_plus(const std::vector<double>& args)
{
  return args.at(1) + args.at(0);
}

double operator_subtract(const std::vector<double>& args)
{
  return args.at(1) - args.at(0);
}

double operator_multiply(const std::vector<double>& args)
{
  return args.at(1) * args.at(0);
}

double operator_divide(const std::vector<double>& args)
{
  return args.at(1) / args.at(0);
}

double operator_power(const std::vector<double>& args)
{
  return powf(args.at(1), args.at(0));
}

double operator_sqrt(const std::vector<double>& args)
{
  return sqrtf(args.at(0));
}

double operator_sin(const std::vector<double>& args)
{
  return sin(utility::degree_to_radian(args.at(0)));
}

double operator_cos(const std::vector<double>& args)
{
  return cos(utility::degree_to_radian(args.at(0)));
}

double operator_tan(const std::vector<double>& args)
{
  return tan(utility::degree_to_radian(args.at(0)));
}
