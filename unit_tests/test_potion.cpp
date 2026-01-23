#include <gtest/gtest.h>
#include <array>
#include "potion.hpp"
#include <gmock/gmock.h>


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

TEST(PotionMixing, SampleFixedCases)
{
    std::array<Potion, 6> potions{
        Potion({153, 210, 199}, 32),
        Potion({135,  34,   0}, 17),
        Potion({ 18,  19,  20}, 25),
        Potion({174, 211,  13},  4),
        Potion({255,  23, 148}, 19),
        Potion({ 51, 102,  51},  6)
    };

    Potion a = potions[0].mix(potions[1]);
    Potion b = potions[0].mix(potions[2]).mix(potions[4]);
    Potion c = potions[1].mix(potions[2]).mix(potions[3]).mix(potions[5]);
    Potion d = potions[0].mix(potions[1]).mix(potions[2]).mix(potions[4]).mix(potions[5]);
    Potion e = potions[0].mix(potions[1]).mix(potions[2]).mix(potions[3]).mix(potions[4]).mix(potions[5]);

    EXPECT_THAT(colorToString(a.m_color), testing::StrEq("{R: 147, G: 149, B: 130}"));
    EXPECT_EQ(a.m_volume, 49u);

    EXPECT_THAT(colorToString(b.m_color), testing::StrEq("{R: 135, G: 101, B: 128}"));
    EXPECT_EQ(b.m_volume, 76u);

    EXPECT_THAT(colorToString(c.m_color), testing::StrEq("{R: 74, G: 50, B: 18}"));
    EXPECT_EQ(c.m_volume, 52u);

    EXPECT_THAT(colorToString(d.m_color), testing::StrEq("{R: 130, G: 91, B: 102}"));
    EXPECT_EQ(d.m_volume, 99u);

    EXPECT_THAT(colorToString(e.m_color), testing::StrEq("{R: 132, G: 96, B: 99}"));
    EXPECT_EQ(e.m_volume, 103u);
}