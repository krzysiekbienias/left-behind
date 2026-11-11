#include <stdexcept>
#include <traffic_light.hpp>
#include <algorithm>
#include <cctype>
#include <utility>


namespace {
    Color colorFromName(std::string name){
        //unify
        std::transform(name.begin(),name.end(),name.begin(),[](unsigned char c){
            return std::toupper(c);});
        if (name=="RED") { return Color::RED;}
        if (name=="GREEN") { return Color::GREEN;}
        if (name=="YELLOW") { return Color::YELLOW;
}
        throw std::invalid_argument("Unknow color "+name);

    }
}


    string colorName(Color color){
        switch (color){
            case Color::RED: return "RED"; //: po case
            case Color::GREEN: return "GREEN"; //: po case
            case Color::YELLOW: return "YELLOW"; //: po case
        }
    return "UNKNOWN";    
    }

    int colorDuration(Color color){
        switch (color){
            case Color::RED: return 30; //: po case
            case Color::GREEN: return 25; //: po case
            case Color::YELLOW: return 5; //: po case
        }
        return 0;
    }

    Color colorNext(Color color){
        switch (color){
        case Color::RED: return Color::GREEN;
        case Color::GREEN: return Color::YELLOW;
        case Color::YELLOW: return Color::RED;
        }

        return Color::RED;
    }




TrafficLight::TrafficLight(string startColor):current_(colorFromName(std::move(startColor))){}

string TrafficLight::getColor(){
    return colorName(current_);
}

int TrafficLight::getDuration(){
    return colorDuration(current_);
}

string TrafficLight::next(){
    current_=colorNext(current_);
    return colorName(current_);
}


string TrafficLight::describe(){
    return colorName(current_) + " (" + std::to_string(colorDuration(current_)) + "s)";
}