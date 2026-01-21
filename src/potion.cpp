#include<array>
#include <potion.hpp>

static unsigned int validateVolume(unsigned int v) {
    if (v==0)  {
        throw std::invalid_argument("Potion::validateVolume : Volume must be positive");
    }
    return v;
}

Potion::Potion(const std::array<unsigned char,3>& color,unsigned int volume):m_color(color),m_volume(validateVolume(volume)) {};

