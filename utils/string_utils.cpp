
#include "string_utils.hpp"
#include <algorithm> //for std::all_of
#include <cctype> //for ::isdigit


namespace string_utils {
bool isAllDigits(const std::string& str){
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

}
