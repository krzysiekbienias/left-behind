#include "std_aliases.hpp"
#include "complex_numbers.hpp"
#include <iostream>

using namespace stl;
using namespace io;


void Complex:: input(string s)
    {
        int v1=0;
        int i=0;
        while(s[i]!='+')
        {
            v1=v1*10+s[i]-'0';
            i++;
        }
        while(s[i]==' ' || s[i]=='+'||s[i]=='i')
        {
            i++;
        }
        int v2=0;
        while(i<s.length())
        {
            v2=v2*10+s[i]-'0';
            i++;
        }
        a=v1;
        b=v2;
    }

std::ostream &operator << (std::ostream& os,const Complex& c) {
    return os<<c.a<<"+ i"<<c.b;
}