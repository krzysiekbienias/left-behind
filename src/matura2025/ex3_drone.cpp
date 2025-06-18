# include "matura2025/ex3_drone.hpp"
#include <iostream>
# include <numeric>

void gcdPairs(int a,int b,int& counter){
    int abs_a=std::abs(a);
    int abs_b=std::abs(b);
    if(std::gcd(abs_a, abs_b)!=1){
        counter++;
    }
}
