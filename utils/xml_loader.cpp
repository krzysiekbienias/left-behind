#include "xml_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>


std::string readXMLToString(const std::string& filepath){
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()){
        throw std::runtime_error("Could not open file: "+filepath);
    }
    std::stringstream buffer;
    buffer<<inputFile.rdbuf();
    return  buffer.str();
}
