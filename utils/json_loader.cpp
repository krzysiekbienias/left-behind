#include "json_loader.hpp"
#include "logger.hpp"  // Optional: your logger
#include <fstream>
#include <stdexcept>

void JsonLoader::load(const std::string& path) {
    std::ifstream file(path); //opens the file stream
    if (!file) {
        Logger::get()->error("Configuration file not found: {}", path);
        throw std::runtime_error("Configuration file not found: " + path);
    }

    try {
        file >> jsonData; //parses the fule contents and fills the container. Now configData holds structured, strongly typed access to all JSON data
        Logger::get()->info("Loaded config from {}", path);
    } catch (const nlohmann::json::parse_error& e) {
        Logger::get()->error("JSON parsing error: {}", e.what());
        throw std::runtime_error("Invalid JSON format in " + path);
    }
}

std::string JsonLoader::getValue(const std::string& key) {
    if (jsonData.contains(key)) {
        return jsonData[key];
    }
    Logger::get()->warn("Key '{}' not found in config", key);
    return "";
}

const nlohmann::json& JsonLoader::getJson() {
    return jsonData;
}


