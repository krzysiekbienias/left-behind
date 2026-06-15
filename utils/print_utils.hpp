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

    inline void printLabelPrefix(const std::optional<std::string>& label, bool multiline = false) {
        if (label) std::cout << *label << (multiline ? ":\n" : ": ");
    }

    template <typename T>
    void printVectorImpl(const std::vector<T>& vec, std::optional<size_t> limit, std::optional<std::string> label) {
        printLabelPrefix(label);
        const size_t count = effectivePrintCount(vec.size(), limit);
        for (size_t i = 0; i < count; ++i) std::cout << vec[i] << " ";
        printTruncatedSuffix(count, vec.size());
        std::cout << "\n";
    }

    template <typename T>
    void printVector(const std::vector<T>& vec) {
        printVectorImpl(vec, std::nullopt, std::nullopt);
    }

    template <typename T>
    void printVector(const std::vector<T>& vec, size_t limit) {
        printVectorImpl(vec, limit, std::nullopt);
    }

    template <typename T>
    void printVector(const std::vector<T>& vec, const std::string& label, std::optional<size_t> limit = std::nullopt) {
        printVectorImpl(vec, limit, label);
    }

    template <typename A, typename B>
    void printPair(const std::pair<A, B>& p, const std::string& label = "") {
        if (!label.empty()) std::cout << label << ": ";
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }

    template <typename A, typename B>
    void printVectorOfPairsImpl(const std::vector<std::pair<A, B>>& vec, std::optional<size_t> limit, std::optional<std::string> label) {
        printLabelPrefix(label);
        const size_t count = effectivePrintCount(vec.size(), limit);
        for (size_t i = 0; i < count; ++i) {
            const auto& [first, second] = vec[i];
            std::cout << "(" << first << '\t' << second << ")\n";
        }
        if (count < vec.size()) {
            std::cout << "... (" << (vec.size() - count) << " more, total " << vec.size() << ")\n";
        }
    }

    template <typename A, typename B>
    void printVectorOfPairs(const std::vector<std::pair<A, B>>& vec) {
        printVectorOfPairsImpl(vec, std::nullopt, std::nullopt);
    }

    template <typename A, typename B>
    void printVectorOfPairs(const std::vector<std::pair<A, B>>& vec, size_t limit) {
        printVectorOfPairsImpl(vec, limit, std::nullopt);
    }

    template <typename A, typename B>
    void printVectorOfPairs(const std::vector<std::pair<A, B>>& vec, const std::string& label, std::optional<size_t> limit = std::nullopt) {
        printVectorOfPairsImpl(vec, limit, label);
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

    void printMapOfVectorsImpl(const std::map<std::string, std::vector<int>>& m, std::optional<size_t> limit, std::optional<std::string> label) {
        printLabelPrefix(label, true);
        for (const auto& [key, vec] : m) {
            std::cout << "  " << key << " -> ";
            const size_t count = effectivePrintCount(vec.size(), limit);
            for (size_t i = 0; i < count; ++i) std::cout << vec[i] << " ";
            printTruncatedSuffix(count, vec.size());
            std::cout << "\n";
        }
    }

    void printMapOfVectors(const std::map<std::string, std::vector<int>>& m) {
        printMapOfVectorsImpl(m, std::nullopt, std::nullopt);
    }

    void printMapOfVectors(const std::map<std::string, std::vector<int>>& m, size_t limit) {
        printMapOfVectorsImpl(m, limit, std::nullopt);
    }

    void printMapOfVectors(const std::map<std::string, std::vector<int>>& m, const std::string& label, std::optional<size_t> limit = std::nullopt) {
        printMapOfVectorsImpl(m, limit, label);
    }

    void printVectorOfSetsImpl(const std::vector<std::set<int>>& v, std::optional<size_t> limit, std::optional<std::string> label) {
        printLabelPrefix(label, true);
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

    void printVectorOfSets(const std::vector<std::set<int>>& v) {
        printVectorOfSetsImpl(v, std::nullopt, std::nullopt);
    }

    void printVectorOfSets(const std::vector<std::set<int>>& v, size_t limit) {
        printVectorOfSetsImpl(v, limit, std::nullopt);
    }

    void printVectorOfSets(const std::vector<std::set<int>>& v, const std::string& label, std::optional<size_t> limit = std::nullopt) {
        printVectorOfSetsImpl(v, limit, label);
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


