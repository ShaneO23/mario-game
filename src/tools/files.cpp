#include "files.h"

std::string FileReadString(const std::string& name) {
  std::ifstream fstream(name);
  return std::string((std::istreambuf_iterator<char>(fstream)), (std::istreambuf_iterator<char>()));
}
