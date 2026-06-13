#pragma once
#include <string>
#include <vector>


struct Point {
    int x;
    int y;
    bool operator==(const Point&) const = default;
    //magic 🪄 spaceship to trojstronne porownanie z c++20
    //auto operator <=> (const Point&) const = default;

    bool operator < (const Point & other) const{
        if(x!=other.x) return x<other.x;
        return y<other.y;
    }

};



std::vector<std::pair<int,int>> readPairs(const std::string& path);

void gcdPairs(int a,int b,int &counter);


Point endVector(std::pair<int,int> disp,Point p);

int pointsInSquare(const std::vector<Point>& coordinates);

std::vector<Point> findThreePoints(std::vector<Point>& points);