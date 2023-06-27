
#include "iaq/utility/utility.hpp"


bool iaq::utility::isdigit(const char* string)
{
  for (;*string != '\0';++string)
  {
    if (!std::isdigit(*string) && (*string) != '.'){
      return false;
    }
  }
  return true;
}

std::string& iaq::utility::replace_all(std::string& base, const std::string& oldstr,
                 const std::string& newstr) {

  std::string::size_type len_of_src = oldstr.size();
  if(len_of_src < 1){
    return base;
  }
  std::string::size_type len_of_des = newstr.size();
  std::string::size_type pos = base.find(oldstr);
  while ((pos != std::string::npos)) {
    base.replace(pos, len_of_src, newstr);
    pos = base.find(oldstr, (pos + len_of_des));
  }

  return base;
}

size_t iaq::utility::splice_string(std::vector<std::string>& outputs,
                                  const std::string& inputs,
                                  const std::string& separator) {
  for (size_t pos = 0, pos_before = 0; pos != std::string::npos;
       pos_before = pos + 1) {
    pos = inputs.find_first_of(separator, pos_before);
    std::string __tmp = inputs.substr(pos_before, pos - pos_before);

    if (!__tmp.empty()) outputs.push_back(__tmp);
  }
  return outputs.size();
}





