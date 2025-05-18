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

bool URLStore::deleteUrl (const std::string& token, const std::string& url){
    auto it=storage.find(token);
    if (it!=storage.end()) return false; // becasue if we cannot find token we cannot erase
    bool erased=it->second.erase(url)>0;
    // it may also happen that there is only one url in for a token, then we want to remove as well token to not being left with empty set
    if(it->second.empty()){
        storage.erase(it);
    }
    return erased;
    
}

void URLStore::print() const {
        for (const auto& [token, urls] : storage) {
            std::cout << token << ":\n";
            for (const auto& url : urls) {
                std::cout << "  - " << url << "\n";
            }
        }
    }






