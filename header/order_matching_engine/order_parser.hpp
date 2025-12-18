#pragma once
#include "command.hpp"
#include <istream>
#include <string>
#include <vector>

class OrderParser {
public:
    Command parseLineCsv(const std::string& line) const;
    std::vector<Command> parseCommandStream(std::istream& input) const;

private:
    static int parseIntStrict(const std::string& s, const char* what);
};