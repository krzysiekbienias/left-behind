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
#include <utility>
#include <optional>
#include <algorithm>

namespace print_utils {

    inline size_t effectivePrintCount(size_t size, std::optional<size_t> limit) {
        if (!limit) return size;
        return std::min(*limit, size);
    }

    inline void printTruncatedSuffix(size_t shown, size_t total) {
        if (shown < total) {
            std::cout << "... (" << (total - shown) << " more, total " << total << ")";
        }
    }

    template <typename T>
    void printVector(const std::vector<T>& vec, const std::string& label = "", std::optional<size_t> limit = std::nullopt) {
        if (!label.empty()) std::cout << label << ": ";
        const size_t count = effectivePrintCount(vec.size(), limit);
        for (size_t i = 0; i < count; ++i) std::cout << vec[i] << " ";
        printTruncatedSuffix(count, vec.size());
        std::cout << "\n";
    }

    template <typename A, typename B>
    void printPair(const std::pair<A, B>& p, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }

    template <typename A, typename B>
    void printVectorOfPairs(const std::vector<std::pair<A, B>>& vec, const std::string& label = "", std::optional<size_t> limit = std::nullopt) {
        if (!label.empty()) std::cout << label << ": ";
        const size_t count = effectivePrintCount(vec.size(), limit);
        for (size_t i = 0; i < count; ++i) {
            const auto& [first, second] = vec[i];
            std::cout << "(" << first << ", " << second << ")\n";
        }
        if (count < vec.size()) {
            std::cout << "... (" << (vec.size() - count) << " more, total " << vec.size() << ")\n";
        }
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
    void printMapOfVectors(const std::map<std::string, std::vector<int>>& m, const std::string& label = "", std::optional<size_t> limit = std::nullopt) {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, vec] : m) {
            std::cout << "  " << key << " -> ";
            const size_t count = effectivePrintCount(vec.size(), limit);
            for (size_t i = 0; i < count; ++i) std::cout << vec[i] << " ";
            printTruncatedSuffix(count, vec.size());
            std::cout << "\n";
        }
    }

    // vector<set<int>>
    void printVectorOfSets(const std::vector<std::set<int>>& v, const std::string& label = "", std::optional<size_t> limit = std::nullopt) {
        if (!label.empty()) std::cout << label << ":\n";
        const size_t count = effectivePrintCount(v.size(), limit);
        for (size_t i = 0; i < count; ++i) {
            std::cout << "  [" << i << "]: ";
            for (int val : v[i]) std::cout << val << " ";
            std::cout << "\n";
        }
        if (count < v.size()) {
            std::cout << "  ... (" << (v.size() - count) << " more sets, total " << v.size() << ")\n";
        }
    }

    template <typename K, typename V>
    void printMapOfDeque(const std::map<K, std::deque<V>>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, dq] : m) {
            std::cout << "  " << key << " -> ";
            for (const auto& item : dq) {
                std::cout << item << " ";
            }
            std::cout << "\n";
        }
    }
    
    template <typename K, typename V>
    void printMapOfUnorderedSets(const std::map<K, std::unordered_set<V>>& m, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ":\n";
        for (const auto& [key, uset] : m) {
            std::cout << "  " << key << " -> { ";
            for (const auto& item : uset) {
                std::cout << item << " ";
            }
            std::cout << "}\n";
        }
    }

    
template <typename K, typename V>
void printUnorderedMapOfUnorderedSets(const std::unordered_map<K, std::unordered_set<V>>& m, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ":\n";
    for (const auto& [key, uset] : m) {
        std::cout << "  " << key << " -> { ";
        for (const auto& item : uset) {
            std::cout << item << " ";
        }
        std::cout << "}\n";
    }
}

void printBoxedLabel(const std::string& label, int totalWidth = 40) {
    const int padding = 2; // for '| ' and ' |'
    int contentWidth = totalWidth - padding;

    std::cout << "\n+" << std::string(contentWidth, '=') << "+\n";
    std::cout << "| " << label << std::string(contentWidth - label.length(), ' ') << "|\n";
    std::cout << "+" << std::string(contentWidth, '=') << "+\n";
}


}


