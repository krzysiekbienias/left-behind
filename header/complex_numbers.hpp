#include "std_aliases.hpp"

using namespace stl;
using namespace io;

class Complex
{
public:
    int a,b;
    void input(string s);

};

std::ostream& operator<<(std::ostream& os, const Complex& c);