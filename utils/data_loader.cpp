#include "data_loader.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <string>

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


std::vector<std::pair<std::string,std::string>> readPairs(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open file: " + path);

    std::vector<std::pair<std::string,std::string>> rows;
    rows.reserve(1024); // optional

    std::string a, b;
    while (in >> a >> b) {
        rows.emplace_back(a, b);
    }

    // If it stopped due to a parsing error (not just EOF), signal it.
    if (!in.eof()) throw std::runtime_error("Parse error while reading: " + path);

    return rows;
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

std::string outputPathFor(const std::string& filename, const std::string& configPath) {
    std::ifstream file(configPath);
    if (!file) {
        throw std::runtime_error("Cannot open config: " + configPath);
    }

    nlohmann::json cfg;
    file >> cfg;

    std::filesystem::path outputDir = cfg.value("OUTPUT", "output");
    if (outputDir.is_relative()) {
        outputDir = std::filesystem::path(configPath).parent_path() / outputDir;
    }

    std::filesystem::create_directories(outputDir);
    return (outputDir / filename).string();
}


}
