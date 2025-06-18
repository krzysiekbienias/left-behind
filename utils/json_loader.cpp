#include "json_loader.hpp"
#include "logger.hpp"
#include <fstream>
#include <stdexcept>

void JsonLoader::load(const std::string&  jsonIdentifier,const std::string& path) {
    std::ifstream file(path); //opens the file stream
    if (!file) {
        Logger::get()->error("JSON file not found: {}", path);
        throw std::runtime_error("JSON file not found: " + path);
    }

    try {
        nlohmann::json jsonData;
        file >> jsonData; //parses the fule contents and fills the container. Now configData holds structured, strongly typed access to all JSON data
        loadedJsons[jsonIdentifier]=jsonData;
        Logger::get()->info("Loaded JSON '{}' from {}",jsonIdentifier, path);
    } catch (const nlohmann::json::parse_error& e) {
        Logger::get()->error("JSON parsing error in {}: {}",path, e.what());
        throw std::runtime_error("Invalid JSON format in " + path);
    }
}


const nlohmann::json& JsonLoader::getJson(const std::string& jsonIdentifier) {
    if (!loadedJsons.contains(jsonIdentifier)) {
            Logger::get()->error("JSON with identifier '{}' not loaded.", jsonIdentifier);
            throw std::runtime_error("JSON not loaded: " + jsonIdentifier);
        }
        return loadedJsons.at(jsonIdentifier);
}


