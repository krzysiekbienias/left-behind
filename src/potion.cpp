#include<array>
#include <potion.hpp>
#include <string>
#include <ostream>
#include <sstream>
#include <strstream>

using ui = unsigned int;
using uch = unsigned char;
using u64 = std::uint64_t;


static unsigned int validateVolume(unsigned int v) {
    if (v == 0) {
        throw std::invalid_argument("Potion::validateVolume : Volume must be positive");
    }
    return v;
}

std::string colorToString(std::array<uch,3>col) {
    std::ostringstream os;
    os<<"{R: "<<(int)col[0]<<", "<<"G: "<<(int)col[1]<<", "<<"B: "<<(int)col[2]<<"}";
    return os.str();
}

Potion::Potion(const std::array<unsigned char, 3> &color, unsigned int volume) : m_color(color),
    m_volume(validateVolume(volume)) {
};


Potion Potion::mix(Potion &other)  const{
    //add on bigger range
    u64 r = (this->m_color[0] * this->m_volume + other.m_color[0] * other.m_volume);
    u64 g = (this->m_color[1] * this->m_volume + other.m_color[1] * other.m_volume);
    u64 b = (this->m_color[2] * this->m_volume + other.m_color[2] * other.m_volume);
    ui combinedVolume = this->m_volume + other.m_volume;
    uch red = static_cast<uch>(std::ceil(static_cast<double>(r) / combinedVolume));
    uch green = static_cast<uch>(std::ceil(static_cast<double>(g) / combinedVolume));
    uch blue = static_cast<uch>(std::ceil(static_cast<double>(b) / combinedVolume));

    return Potion({red, green, blue}, combinedVolume);
}
