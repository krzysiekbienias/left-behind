#pragma once
#include<vector>


struct Point {
    int x;
    int y;
    bool operator==(const Point&) const = default;
};



std::vector<std::pair<int,int>> readPairs(const std::string& path);

void gcdPairs(int a,int b,int &counter);


Point endVector(std::pair<int,int> disp,Point p);

int pointsInSquare(const std::vector<Point>& coordinates);