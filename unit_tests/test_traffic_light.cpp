#include <traffic_light.hpp>

#include <gtest/gtest.h>

#include <stdexcept>

// ---------------------------------------------------------------------------
// Free helper functions
// ---------------------------------------------------------------------------

TEST(TrafficLightTest, ColorNameReturnsUppercaseName) {
    EXPECT_EQ(colorName(Color::RED), "RED");
    EXPECT_EQ(colorName(Color::GREEN), "GREEN");
    EXPECT_EQ(colorName(Color::YELLOW), "YELLOW");
}

TEST(TrafficLightTest, ColorNameOfInvalidValueIsUnknown) {
    EXPECT_EQ(colorName(static_cast<Color>(99)), "UNKNOWN");
}

TEST(TrafficLightTest, ColorDurationMatchesSpec) {
    EXPECT_EQ(colorDuration(Color::RED), 30);
    EXPECT_EQ(colorDuration(Color::GREEN), 25);
    EXPECT_EQ(colorDuration(Color::YELLOW), 5);
}

TEST(TrafficLightTest, ColorNextFollowsRedGreenYellowCycle) {
    EXPECT_EQ(colorNext(Color::RED), Color::GREEN);
    EXPECT_EQ(colorNext(Color::GREEN), Color::YELLOW);
    EXPECT_EQ(colorNext(Color::YELLOW), Color::RED);
}

// ---------------------------------------------------------------------------
// Construction (this also covers the private colorFromName)
// ---------------------------------------------------------------------------

TEST(TrafficLightTest, ConstructWithUppercaseName) {
    EXPECT_EQ(TrafficLight("RED").getColor(), "RED");
    EXPECT_EQ(TrafficLight("GREEN").getColor(), "GREEN");
    EXPECT_EQ(TrafficLight("YELLOW").getColor(), "YELLOW");
}

TEST(TrafficLightTest, ConstructorIsCaseInsensitive) {
    EXPECT_EQ(TrafficLight("red").getColor(), "RED");
    EXPECT_EQ(TrafficLight("Green").getColor(), "GREEN");
    EXPECT_EQ(TrafficLight("yElLoW").getColor(), "YELLOW");
}

TEST(TrafficLightTest, ConstructorThrowsOnUnknownColor) {
    EXPECT_THROW(TrafficLight("purple"), std::invalid_argument);
}

TEST(TrafficLightTest, ConstructorThrowsOnEmptyString) {
    EXPECT_THROW(TrafficLight(""), std::invalid_argument);
}

TEST(TrafficLightTest, ConstructorDoesNotTrimWhitespace) {
    EXPECT_THROW(TrafficLight(" RED"), std::invalid_argument);
    EXPECT_THROW(TrafficLight("RED "), std::invalid_argument);
}

TEST(TrafficLightTest, ConstructorRejectsMisspelledColor) {
    EXPECT_THROW(TrafficLight("YELOW"), std::invalid_argument);
    EXPECT_THROW(TrafficLight("REDD"), std::invalid_argument);
}

TEST(TrafficLightTest, ConstructorErrorMentionsOffendingName) {
    try {
        TrafficLight light("purple");
        FAIL() << "expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_NE(std::string(e.what()).find("PURPLE"), std::string::npos);
    }
}

// ---------------------------------------------------------------------------
// getDuration
// ---------------------------------------------------------------------------

TEST(TrafficLightTest, GetDurationDependsOnCurrentColor) {
    EXPECT_EQ(TrafficLight("RED").getDuration(), 30);
    EXPECT_EQ(TrafficLight("GREEN").getDuration(), 25);
    EXPECT_EQ(TrafficLight("YELLOW").getDuration(), 5);
}

// ---------------------------------------------------------------------------
// next
// ---------------------------------------------------------------------------

TEST(TrafficLightTest, NextReturnsNewColorName) {
    TrafficLight light("RED");

    EXPECT_EQ(light.next(), "GREEN");
}

TEST(TrafficLightTest, NextChangesCurrentColor) {
    TrafficLight light("RED");

    light.next();

    EXPECT_EQ(light.getColor(), "GREEN");
    EXPECT_EQ(light.getDuration(), 25);
}

TEST(TrafficLightTest, NextCyclesThroughAllColors) {
    TrafficLight light("RED");

    EXPECT_EQ(light.next(), "GREEN");
    EXPECT_EQ(light.next(), "YELLOW");
    EXPECT_EQ(light.next(), "RED");
    EXPECT_EQ(light.next(), "GREEN");
}

TEST(TrafficLightTest, NextFromYellowWrapsToRed) {
    TrafficLight light("yellow");

    EXPECT_EQ(light.next(), "RED");
    EXPECT_EQ(light.getDuration(), 30);
}

TEST(TrafficLightTest, FullCycleReturnsToStartColor) {
    for (const char* start : {"RED", "GREEN", "YELLOW"}) {
        TrafficLight light(start);

        light.next();
        light.next();
        light.next();

        EXPECT_EQ(light.getColor(), start);
    }
}

TEST(TrafficLightTest, ManyStepsStayInSync) {
    TrafficLight light("RED");
    const char* expected[] = {"GREEN", "YELLOW", "RED"};

    for (int i = 0; i < 300; ++i) {
        ASSERT_EQ(light.next(), expected[i % 3]) << "step=" << i;
    }
}

TEST(TrafficLightTest, LightsAreIndependent) {
    TrafficLight a("RED");
    TrafficLight b("RED");

    a.next();

    EXPECT_EQ(a.getColor(), "GREEN");
    EXPECT_EQ(b.getColor(), "RED");
}

// ---------------------------------------------------------------------------
// getColor / describe
// ---------------------------------------------------------------------------

TEST(TrafficLightTest, GetColorIsStableWithoutNext) {
    TrafficLight light("GREEN");

    EXPECT_EQ(light.getColor(), "GREEN");
    EXPECT_EQ(light.getColor(), "GREEN");
}

TEST(TrafficLightTest, DescribeContainsColorAndDuration) {
    EXPECT_EQ(TrafficLight("RED").describe(), "RED (30s)");
    EXPECT_EQ(TrafficLight("GREEN").describe(), "GREEN (25s)");
    EXPECT_EQ(TrafficLight("YELLOW").describe(), "YELLOW (5s)");
}

TEST(TrafficLightTest, DescribeReflectsStateAfterNext) {
    TrafficLight light("red");

    light.next();
    EXPECT_EQ(light.describe(), "GREEN (25s)");

    light.next();
    EXPECT_EQ(light.describe(), "YELLOW (5s)");
}
