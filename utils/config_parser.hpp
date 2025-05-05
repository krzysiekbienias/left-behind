#pragma once

#include <string>
#include <unordered_map>

class Config {
public:
    static Config from_json(const std::string& path);
    std::string get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> values;
};
