# include <vector>
# include <string>
# include "matura2024/hurtownia.hpp"
# include <fstream>
# include <iostream>
# include <sstream>


Hurtownia Sprzedaz::parseLineToHurtownia(const std::string & line){
    std::istringstream iss(line);
    Hurtownia h;
    std::string poraStr; //be careful with char
    
    std::getline(iss,h.dataSprzedazy,'\t');
    std::getline(iss,h.odmiana, '\t');
    std::getline(iss, poraStr, '\t');
    iss>>h.sprzedazKg;
    h.poraRoku=poraStr[0];
    return h;
    
}


void Sprzedaz::loadData(std::string fileName){
    std::ifstream file("../../data/matura2024/"+fileName);
    if (!file) {
        std::cerr << "Failed to open file.\n";

    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && (line.back()=='\r' || line.back()=='\n')){  // Skip empty lines if any
            line.pop_back();
        }
        m_hurtownia.push_back(parseLineToHurtownia(line));
    }
    
    file.close();
}

//std::unordered_map<std::string, int> Sprzedaz::perClient(){
//    std::unordered_map<std::string, int> result;
//    for (int i=0;i<m_hurtownia.size();++i){
//        
//        result[magazyn[i]]+=
//        
//    }
//}
