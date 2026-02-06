#include <gtest/gtest.h>
#include <string>
#include <vector>


#include "itinerary.hpp"

TEST(Itinerary, SingleTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO")
    };

    std::string expected = "TRN-FCO";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(Itinerary, MultipleTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("CIA", "JFK")
    };

    std::string expected = "TRN-FCO-CIA-JFK";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(Itinerary, SameAirportsAreSkippedTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("FCO", "JFK")
    };

    std::string expected = "TRN-FCO-JFK";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(Itinerary, RoundTripAreConservedTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("CIA", "TRN")
    };

    std::string expected = "TRN-FCO-CIA-TRN";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(Itinerary, RoundTripAreConservedWithSharedAirportsTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("FCO", "TRN")
    };

    std::string expected = "TRN-FCO-TRN";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

// ===== Describe(ExtendedTests) =====

TEST(ItineraryExtended, RoundTripAreConservedWithSharedAirports1Test)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("FCO", "TRN")
    };

    std::string expected = "TRN-FCO-TRN";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(ItineraryExtended, RoundTripAreConservedWithSharedAirports2Test)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("FCO", "TRN"),
        Route("TRN", "NCE"),
        Route("NCE", "PAR"),
        Route("PAR", "JFK"),
        Route("JFK", "MIA"),
        Route("MIA", "FCO"),
        Route("CIA", "TRN")
    };

    std::string expected = "TRN-FCO-TRN-NCE-PAR-JFK-MIA-FCO-CIA-TRN";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(ItineraryExtended, NotConnectedTravelTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("CIA", "FRA"),
        Route("FRB", "JFK"),
        Route("MIA", "CIA"),
        Route("RIA", "GOA")
    };

    std::string expected = "TRN-FCO-CIA-FRA-FRB-JFK-MIA-CIA-RIA-GOA";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}

TEST(ItineraryExtended, RecurrentAirportTest)
{
    std::vector<Route> travel = {
        Route("TRN", "FCO"),
        Route("CIA", "FRA"),
        Route("FRA", "JFK"),
        Route("JFK", "CIA"),
        Route("CIA", "GOA"),
        Route("GOA", "CIA")
    };

    std::string expected = "TRN-FCO-CIA-FRA-JFK-CIA-GOA-CIA";
    std::string actual = itinerary(travel);

    EXPECT_EQ(actual, expected);
}