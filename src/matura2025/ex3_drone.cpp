# include "matura2025/ex3_drone.hpp"
#include <cstddef>
#include <iostream>
# include <numeric>
#include<fstream>
#include <algorithm>



std::vector<std::pair<int,int>> readPairs(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open file: " + path);

    std::vector<std::pair<int,int>> rows;
    rows.reserve(1024); // optional

    int a, b;
    while (in >> a >> b) {
        rows.emplace_back(a, b);
    }

    // If it stopped due to a parsing error (not just EOF), signal it.
    if (!in.eof()) throw std::runtime_error("Parse error while reading: " + path);

    return rows;
}

void gcdPairs(int a,int b,int& counter){
    int abs_a=std::abs(a);
    int abs_b=std::abs(b);
    if(std::gcd(abs_a, abs_b)!=1){
        counter++;
    }
}

Point endVector(std::pair<int,int> disp, Point p) {
    return {p.x+disp.first,p.y+disp.second};
}


static bool isWithinSquare(Point p) {
    if (p.x<5000 && p.y<5000 && p.x>0 && p.y>0)  {
        return true;
    }
    return false;
}

int pointsInSquare(const std::vector<Point>& coordinates) {
    int cnt=0;
    for ( Point p:coordinates) {
        if (isWithinSquare(p)) cnt++;
    }
    return cnt;
}


std::vector<Point> findThreePoints(std::vector<Point>& points){
    size_t n=points.size();
    std::sort(points.begin(),points.end());

    for(int i =0; i<n;i++){
        for (int j=i+1; j<n; j++) {
            //nieparzysta sume wspolrzednych nie ma co sprawdzac
        if((points[i].x+points[j].x)%2!=0 ||(points[i].y+points[j].y)%2!=0 ){
            continue;
        }
        Point mid={(points[i].x+points[j].x)/2,(points[i].y+points[j].y)/2};
        if(std::binary_search(points.begin(),points.end(),mid)){
            return {points[i],points[j],mid};
        }
        }

    }
    return {};
}