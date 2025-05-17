#include <iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>

#include "crud.hpp"

void URLStore::saveUrl(const std::string& token, const std::string& url){
        storage[token].insert(url);
}

bool URLStore::isUrlSaved(const std::string &token, const std::string &url)const{
    auto it=storage.find(token);
    if (it==storage.end()) return false;
    return it->second.count(url)>0;
    
}

std::vector<std::string>URLStore:: getURL(const std::string& token){
    std::vector<std::string> results;
    auto it=storage.find(token);
    if (it!=storage.end()) {
        results.insert(results.end(), it->second.begin(),it->second.end());
    }
    return results;
}

void URLStore::print() const {
        for (const auto& [token, urls] : storage) {
            std::cout << token << ":\n";
            for (const auto& url : urls) {
                std::cout << "  - " << url << "\n";
            }
        }
    }






