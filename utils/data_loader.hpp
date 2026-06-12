#pragma once

#include <string>
#include <vector>

namespace data_loader {

// Resolves a data file path by key from the "DATA" section of config.json.
// Relative paths are resolved against the config file's directory,
// so it works regardless of the current working directory.
std::string pathFor(const std::string& key, const std::string& configPath = "config.json");

// Loads a whole file into a vector of lines (typical exam-task buffer).
std::vector<std::string> readLines(const std::string& path);

// Loads a whole file into a single string.
std::string readAll(const std::string& path);

}
