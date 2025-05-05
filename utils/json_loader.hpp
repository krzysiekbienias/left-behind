#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

class JsonLoader {
public:
    static void load(const std::string& path);
    static std::string getValue(const std::string& key);
    static const nlohmann::json& getJson();

private:
    static inline nlohmann::json jsonData;
};

#endif // CONFIG_LOADER_HPP
