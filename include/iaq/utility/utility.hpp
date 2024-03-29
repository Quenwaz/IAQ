#include <string>
#include <cmath>
#include <vector>

namespace iaq::utility
{
/**
 * @brief 判断指定字符串是否都为数字
 * 
 * @param string 字符串
 * @return true 都为数字
 * @return false 存在不为数字的字符
 */
bool isdigit(const char* string);

/**
 * @brief 在源字符串中找到指定字符串并替换
 * 
 * @param base 源字符串
 * @param oldstr 旧字符串
 * @param newstr 新字符串
 */
std::string& replace_all(std::string& base, const std::string& oldstr,
                 const std::string& newstr);


/**
 * @brief 字符串切割
 * 
 * @param outputs 输出切割后的字符串列表
 * @param inputs 输入字符串
 * @param separator 切割符， 如,.表示切割有,及.分割的字符串
 * @return size_t 
 */
size_t splice_string(std::vector<std::string>& outputs,
                    const std::string& inputs,
                    const std::string& separator);

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