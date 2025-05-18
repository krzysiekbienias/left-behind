#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace print_utils {

    template <typename T>
    void printVector(const std::vector<T>& vec, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        for (const auto& item : vec) std::cout << item << " ";
        std::cout << "\n";
    }

    template <typename T>
    void printList(const std::list<T>& lst, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        for (const auto& item : lst) std::cout << item << " ";
        std::cout << "\n";
    }

    template <typename T>
    void printDeque(const std::deque<T>& dq, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        for (const auto& item : dq) std::cout << item << " ";
        std::cout << "\n";
    }

    template <typename T>
    void printSet(const std::set<T>& s, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        for (const auto& item : s) std::cout << item << " ";
        std::cout << "\n";
    }

    template <typename T>
    void printUnorderedSet(const std::unordered_set<T>& us, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        for (const auto& item : us) std::cout << item << " ";
        std::cout << "\n";
    }

    template <typename K, typename V>
    void printMap(const std::map<K, V>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, value] : m) {
            std::cout << "  " << key << " -> " << value << "\n";
        }
    }

    template <typename K, typename V>
    void printUnorderedMap(const std::unordered_map<K, V>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, value] : m) {
            std::cout << "  " << key << " -> " << value << "\n";
        }
    }

    // More complex: map<string, vector<int>>
    void printMapOfVectors(const std::map<std::string, std::vector<int>>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, vec] : m) {
            std::cout << "  " << key << " -> ";
            for (int val : vec) std::cout << val << " ";
            std::cout << "\n";
        }
    }

    // vector<set<int>>
    void printVectorOfSets(const std::vector<std::set<int>>& v, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        int i = 0;
        for (const auto& s : v) {
            std::cout << "  [" << i++ << "]: ";
            for (int val : s) std::cout << val << " ";
            std::cout << "\n";
        }
    }

    // map<float, deque<CustomType>> — generic handler with formatter
    template <typename T>
    void printMapOfDeque(const std::map<float, std::deque<T>>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [price, orders] : m) {
            std::cout << "  " << price << ": ";
            for (const auto& order : orders) {
                std::cout << "[" << order << "] "; // customize this per your `Order`
            }
            std::cout << "\n";
        }
    }

}


