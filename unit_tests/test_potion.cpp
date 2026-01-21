#include <gtest/gtest.h>
#include <array>
#include "potion.hpp"


TEST(Potion, TestConstructor)
{
    std::array<unsigned char, 3> color{255, 128, 0};
    unsigned int volume = 10;

    Potion p(color, volume);

    EXPECT_EQ(p.m_color, color);
    EXPECT_EQ(p.m_volume, volume);
}


TEST(Potion, ConstructorWith0Volume)
{
    std::array<unsigned char, 3> color{255, 128, 0};
    unsigned int volume = 0u;

    EXPECT_THROW(Potion(color,volume),std::exception);


}


TEST(Potion, Mix2Eliksirs)
{
    std::array<unsigned char, 3> color1{255, 255, 255};
    unsigned int volume1 = 7;
    std::array<unsigned char, 3> color2{51, 102, 51};
    unsigned int volume2 = 12;

    Potion p(color1, volume1);
    Potion p2(color2, volume2);

    Potion p3= p.mix(p2);

    EXPECT_EQ(colorToString(p3.m_color),"{R: 127, G: 159, B: 127}");





}
