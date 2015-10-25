#include "strings.h"

std::vector<std::string> StringSplit(const std::string &str, const std::string &sep) {
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(sep, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    strings.push_back(str.substr(prev));

    return strings;
}

std::vector<std::string> StringLines(const std::string &str) {
    return StringSplit(str, std::string("\n"));
}

std::vector<char> StringChars(const std::string &str) {
    return std::vector<char>(str.begin(), str.end());
}
