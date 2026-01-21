#pragma once
#include<array>

using uch = unsigned char;
std::string colorToString(std::array<uch,3>col);

class Potion {
public:
    std::array<unsigned char,3> m_color; //unsigned char [0,255]
    unsigned int m_volume;

    Potion(const std::array<unsigned char,3>& color,unsigned int volume);

    Potion mix(Potion &other) const;

};