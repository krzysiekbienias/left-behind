#include "matura2025/ex1.hpp"
# include <iostream>

long long przestaw(long long n, int & callCounter){
    callCounter++;
    int r=n%100;
    int a=r/10;
    int b=r%10;
    n=n/100;
    long long w;
    if (n>0) {
        w=a+10LL*b+100LL*przestaw(n,callCounter);
    
    }
    else{
        if (a>0) {
            w=a+10*b;
        } else {
            w=b;
        }
    }
    return w;
}
