#pragma once
#include<array>

class Potion {
public:
    std::array<unsigned char,3> color; //unsigned char [0,255]
    unsigned int volume;

    Potion(const std::array<unsigned char,3>& color,unsigned int volume);

    Potion mix(Potion &other);

};