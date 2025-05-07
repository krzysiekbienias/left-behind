#include "config_parser.hpp"
#include "json_loader.hpp"
#include <vector>
#include <stdexcept>

Config Config::from_json(const std::string& path) {
    JsonLoader::load("config",path);
    const auto& jsonContent = JsonLoader::getJson("config");

    Config config;
    std::vector<std::string> keys = {
        "STANDARISED_INPUT",
        "STUDENTS_DATA",
        "ALPHA_VENTAGE_API_KEY",
        "FRED_API_KEY",
        "QUANDL_API_KEY",
        "POLYGON_IO_API_KEY"
    };

    for (const auto& key : keys) {
        if (!jsonContent.contains(key)) {
            throw std::runtime_error("Missing required config key: " + key);
        }
        config.values[key] = jsonContent.at(key);
    }

    return config;
}

std::string Config::get(const std::string& key) const {
    auto it = values.find(key);
    return it != values.end() ? it->second : "";
}
