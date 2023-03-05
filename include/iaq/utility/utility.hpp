#include <string>
#include <cmath>


namespace iaq::utility
{
/**
 * @brief 判断指定字符串是否都为数字
 * 
 * @param string 字符串
 * @return true 都为数字
 * @return false 存在不为数字的字符
 */
bool isdigit(const char* string)
{
  for (;*string != '\0';++string)
  {
    if (!std::isdigit(*string)){
      return false;
    }
  }
  return true;
}

/**
 * @brief 在源字符串中找到指定字符串并替换
 * 
 * @param base 源字符串
 * @param oldstr 旧字符串
 * @param newstr 新字符串
 */
std::string& replace_all(std::string& base, const std::string& oldstr,
                 const std::string& newstr) {
  std::string::size_type len_of_src = oldstr.size();
  std::string::size_type len_of_des = newstr.size();
  std::string::size_type pos = base.find(oldstr);
  while ((pos != std::string::npos)) {
    base.replace(pos, len_of_src, newstr);
    pos = base.find(oldstr, (pos + len_of_des));
  }

  return base;
}

/**
 * @brief 角度转弧度:1°=PI/180弧度
 * 
 * @param degree 角度
 * @return double 弧度
 */
inline double degree_to_radian(double degree) { return degree * M_PI / 180; }

/**
 * @brief 弧度转角度:1弧度=180/PI°
 * 
 * @param radian 弧度
 * @return double 角度
 */
inline double radian_to_degree(double radian) { return radian * 180/M_PI; }
}