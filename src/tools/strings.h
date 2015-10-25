#ifndef TOOLS_STRINGS_H
#define TOOLS_STRINGS_H

#include <string>
#include <vector>

std::vector<std::string> StringSplit(const std::string& str, const std::string& sep);
std::vector<std::string> StringLines(const std::string &str);
std::vector<char> StringChars(const std::string &str);

#endif
