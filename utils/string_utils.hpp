#pragma once
#include<string>


namespace string_utils{
    bool isAllDigits(const std::string& str);


    inline std::string trim(const std::string& s) {
        size_t b = 0;
        size_t e = s.size();

        while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
        while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;

        return s.substr(b, e - b);
    }

}
