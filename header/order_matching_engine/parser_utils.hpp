#pragma once
#include <charconv>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <system_error>

namespace parse_utils {

    template <class Int>
    inline Int int_strict(const std::string& s, const char* what) {
        Int out{};
        auto* b = s.data();
        auto* e = s.data() + s.size();
        auto [p, ec] = std::from_chars(b, e, out);
        if (ec != std::errc{} || p != e) {
            throw std::invalid_argument(std::string("invalid ") + what + ": '" + s + "'");
        }
        return out;
    }

    inline int i32(const std::string& s, const char* what) {
        return int_strict<int>(s, what);
    }

    inline int64_t i64(const std::string& s, const char* what) {
        return int_strict<int64_t>(s, what);
    }

} // namespace parse_utils