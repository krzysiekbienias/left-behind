#include <iostream>
#include "moving_average.hpp"

int main() {
    std::cout << "Welcome to Left Behind!" << std::endl;
    MovingAverage ma(3);
    float avg1=ma.next(4);
    std::cout<<avg1<<"\n";
    float avg2=ma.next(5);
    std::cout<<avg2<<"\n";
    float avg3=ma.next(8);
    std::cout<<avg3<<"\n";
    float avg4=ma.next(2);
    std::cout<<avg4<<"\n";
    
    
    
    
    return 0;
}
