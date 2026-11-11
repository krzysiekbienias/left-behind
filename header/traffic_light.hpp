#pragma once
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <vector>
#include <string>



using std::string;

enum class Color {
    RED,
    GREEN,
    YELLOW
};

string colorName(Color color);
int colorDuration( Color color);
Color colorNext(Color color);

//This has been provided do not touch
class TrafficLight {
    private:
        Color current_;
    
    public:
        TrafficLight(string startColor);
    
        string getColor();
    
        int getDuration();
    
        string next();
    
        string describe();
    };