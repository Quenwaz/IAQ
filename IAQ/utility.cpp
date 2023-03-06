
#include "iaq/utility/utility.hpp"


bool iaq::utility::isdigit(const char* string)
{
  for (;*string != '\0';++string)
  {
    if (!std::isdigit(*string)){
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


