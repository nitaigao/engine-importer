#include "Extension.h"

std::string extension(const std::string& filename) {
  if(filename.find_last_of(".") != std::string::npos)
    return filename.substr(filename.find_last_of(".")+1);
  return "";
}
