#include <iostream>

#include "data_loader.hpp"

int main() {
    // Switch the task here: SYMBOLE, SYMBOLE_2, DRON, LAZIKI... (see config.json -> DATA)
    const std::string path = data_loader::pathFor("SYMBOLE", CONFIG_PATH);
    const std::vector<std::string> lines = data_loader::readLines(path);

    std::cout << "Loaded " << lines.size() << " lines from " << path << "\n";
    for (const auto& line : lines) {
        std::cout << line << "\n";
    }
}
