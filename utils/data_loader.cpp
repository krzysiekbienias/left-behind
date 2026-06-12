#include "data_loader.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace data_loader {

std::string pathFor(const std::string& key, const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file) {
        throw std::runtime_error("Cannot open config: " + configPath);
    }

    nlohmann::json cfg;
    file >> cfg;

    if (!cfg.contains("DATA") || !cfg["DATA"].contains(key)) {
        throw std::runtime_error("No DATA entry in config for key: " + key);
    }

    std::filesystem::path dataPath = cfg["DATA"][key].get<std::string>();
    if (dataPath.is_relative()) {
        dataPath = std::filesystem::path(configPath).parent_path() / dataPath;
    }
    return dataPath.string();
}

std::vector<std::string> readLines(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open data file: " + path);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::string readAll(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open data file: " + path);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}
