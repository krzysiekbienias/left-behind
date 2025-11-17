// common.hpp
#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <utility>
#include <optional>
#include <variant>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <limits>
#include <chrono>
#include <iomanip>
#include <random>   // generatory i rozkłady
#include <cstdint>


namespace stl {
    using std::vector;
    using std::array;
    using std::pair;
    using std::string;
    using std::map;
    using std::set;
    using std::unordered_map;
    using std::unordered_set;
    using std::queue;
    using std::priority_queue;
    using std::stack;


    // Krótsze aliasy szablonowe (opcjonalnie)
    template<class T> using Vec = std::vector<T>;
    template<class K, class V> using HashMap = std::unordered_map<K, V>;

    //operacje na kontenerach
    using std::sort;
}

namespace io {
    using std::iostream;
    using std::ostringstream;
    using std::setw;
    using std::setfill;
    using std::cout;
    using std::cin;
    using std::endl;
}

namespace custom_alias {
    template<class A, class B> using Pair = std::pair<A,B>;
    using ll  = long long;
    using ull = unsigned long long;
    using i64 = std::int64_t;
    using u32=std::uint32_t;
    using u64 = std::uint64_t;
    using Str = std::string;
    using Svw = std::string_view;
}

namespace rnd {
    // Silniki (tylko aliasy typów)
    using RNG64      = std::mt19937_64;
    using RNG32      = std::mt19937;
    using RandomDev  = std::random_device;
    using SeedSeq    = std::seed_seq;

    // Rozkłady (aliasy szablonowe)
    template<class Int>   using UniformInt  = std::uniform_int_distribution<Int>;
    template<class Real>  using UniformReal = std::uniform_real_distribution<Real>;
    using Bernoulli                     = std::bernoulli_distribution;
    template<class Real>  using Normal  = std::normal_distribution<Real>;
    template<class Real>  using Exponential = std::exponential_distribution<Real>;
    template<class Real>  using Gamma   = std::gamma_distribution<Real>;
    template<class Real>  using LogNormal = std::lognormal_distribution<Real>;
}


// --- heap-y gotowe do użycia ---
//template<class T>
//using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
//
//template<class T>
//using MaxHeap = std::priority_queue<T>; // domyślnie max-heap