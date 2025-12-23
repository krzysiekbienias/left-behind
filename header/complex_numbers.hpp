#include "std_aliases.hpp"

using namespace stl;
using namespace io;

class Complex
{
public:
    int a;
    int b;
    Complex(int a=0,int b=0);

    void input(string s);

    Complex operator+(const Complex& other) const;

};

std::ostream& operator<<(std::ostream& os, const Complex& c);