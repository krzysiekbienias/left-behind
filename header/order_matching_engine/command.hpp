#pragma once

#include<string>
#include<vector>
#include "raw_order.hpp"

enum class CommandType {
    New,
    Amend,
    Cancel,
    Match,
    Query,
    Dump
};

struct Command {
    CommandType type{};
    RawOrder rawOrder{};                // N/A
    std::vector<std::string> tokens{};  // pełne tokeny (debug)

    // wspólne filtry/eventy dla X/M/Q (opcjonalnie)
    std::optional<int64_t> timestamp{}; // X/M/Q (jeśli podany)
    std::string symbol{};               // M/Q (opcjonalnie, "" = wszystkie)

    // dla Cancel
    int orderId{};                      // X
};

