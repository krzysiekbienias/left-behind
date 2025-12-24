#include "std_aliases.hpp"
#include "complex_numbers.hpp"
#include <iostream>

using namespace stl;
using namespace io;

Complex::Complex(int a, int b) : a(a), b(b) {
};

void Complex::input(string s) {
    auto skipSpaces = [&](size_t &i) {
        while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    };

    auto parseInt = [&](size_t &i) -> int {
        skipSpaces(i);
        bool neg = false;
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            neg = (s[i] == '-');
            ++i;
        }
        skipSpaces(i);
        if (i >= s.size() || !std::isdigit(static_cast<unsigned char>(s[i])))
            throw std::invalid_argument("Bad complex format. Use: a+bi or a-bi (e.g. 3-5i).");

        int val = 0;
        while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
            val = val * 10 + (s[i] - '0');
            ++i;
        }
        return neg ? -val : val;
    };

    size_t i = 0;

    // real part: a
    int real = parseInt(i);

    // sign between a and b: '+' or '-'
    skipSpaces(i);
    if (i >= s.size() || (s[i] != '+' && s[i] != '-'))
        throw std::invalid_argument("Bad complex format. Use: a+bi or a-bi (e.g. 3-5i).");
    char sign = s[i];
    ++i;

    // imaginary magnitude: b (digits only, sign comes from '+'/'-' above)
    skipSpaces(i);
    if (i >= s.size() || !std::isdigit(static_cast<unsigned char>(s[i])))
        throw std::invalid_argument("Bad complex format. Use: a+bi or a-bi (e.g. 3-5i).");

    int imag = 0;
    while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
        imag = imag * 10 + (s[i] - '0');
        ++i;
    }

    // trailing 'i'
    skipSpaces(i);
    if (i >= s.size() || s[i] != 'i')
        throw std::invalid_argument("Bad complex format. Use: a+bi or a-bi (e.g. 3-5i).");
    ++i;

    // no extra junk at the end
    skipSpaces(i);
    if (i != s.size())
        throw std::invalid_argument("Bad complex format. Use: a+bi or a-bi (e.g. 3-5i).");

    a = real;
    b = (sign == '-') ? -imag : imag;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(a + other.a, b + other.b);
}


Complex Complex::conjugate() const {
    return Complex(a,-b);
}

float Complex::modulus() const {
    return sqrt(a*a+b*b);
}

std::ostream &operator <<(std::ostream &os, const Complex &c) {
    return os << c.a << "+" << c.b<<"i";
}


