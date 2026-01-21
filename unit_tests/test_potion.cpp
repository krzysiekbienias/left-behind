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
