#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>

namespace data_loader {

// Resolves a data file path by key from the "DATA" section of config.json.
// Relative paths are resolved against the config file's directory,
// so it works regardless of the current working directory.
std::string pathFor(const std::string& key, const std::string& configPath = "config.json");

// Loads a whole file into a vector of lines (typical exam-task buffer).
std::vector<std::string> readLines(const std::string& path);

std::vector<std::pair<std::string,std::string>> readPairs(const std::string& path);

// Loads a whole file into a single string.
std::string readAll(const std::string& path);

// Resolves a path inside the output directory ("OUTPUT" in config.json,
// default "output", relative to the config file's directory).
// Creates the directory if it does not exist yet.
std::string outputPathFor(const std::string& filename, const std::string& configPath = "config.json");


template <typename T>
void writeLines(const std::string& path, const std::vector<T>& elements) {
    std::ofstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open output file: " + path);
    }

    for (const auto& element : elements) {
        file << element << '\n'; // Strumień sam wie, jak sformatować typ T
    }
}

}
