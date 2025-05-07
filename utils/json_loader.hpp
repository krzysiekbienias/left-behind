#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "logger.hpp"

class JsonLoader {
public:
    static void load(const std::string&  jsonIdentifier,const std::string& path);
    
    template<typename T>
    T getValue(const std::string& jsonIdentifier, const std::string& tag) {
        const auto& j = getJson(jsonIdentifier);
        if (!j.contains(tag)) {
            Logger::get()->warn("Key '{}' not found in JSON '{}'", tag, jsonIdentifier);
            throw std::runtime_error("Missing key: " + tag);
        }
        return j.at(tag).get<T>();
    }
    
    static const nlohmann::json& getJson(const std::string&  jsonIdentifier);

private:
    static inline std::unordered_map<std::string,nlohmann::json> loadedJsons;
};

#endif // CONFIG_LOADER_HPP
