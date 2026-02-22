#include <gtest/gtest.h>
#include <vector>


#include <gmock/gmock.h>
#include "matura2025/ex3_drone.hpp"


using ::testing::ElementsAre;

TEST(Drone, CoordinateFromVector) {
    std::pair<int,int> displacement ={2,1};
    Point p={3,2};
    Point pAfterShift=endVector(displacement,p);
    Point expected={5,3};
    EXPECT_EQ(pAfterShift,expected);
}


TEST(Drone,Coordinates) {
    std::vector<std::pair<int,int>>displacements={{3000,2000},
                                        {2000, 9000},
                                        {5000, -7000},
                                        {5000, 4000},
                                        {3000, 6000},
                                        {2000, -14000}};
    int n =displacements.size();
    std::vector<Point>expected={
        {0,0},
        {3000,2000},
        {5000,11000},
        {10000,4000},
        {15000,8000},
        {18000,14000},
        {20000,0},
    };
    std::vector<Point>actual;
    actual.push_back(Point{0,0});
    for (int i = 1; i <=n; ++i) {
        Point endVec=endVector(displacements[i-1],actual[i-1]);
        actual.push_back(endVec);


    }
    EXPECT_THAT(actual,expected);

}


TEST (Drone, IsWithinSquare) {
    std::vector<Point>coordinates={
        {0,0},
        {3000,2000},
        {5000,11000},
        {10000,4000},
        {15000,8000},
        {18000,14000},
        {20000,0},
    };
    int expected=1;
    int actual=pointsInSquare(coordinates);
    EXPECT_EQ(expected,actual);
}
