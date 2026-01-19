#pragma once
#include <string>
#include<optional>

struct FixedLeg{
    std::string payer;
    std::string receiver;
    double notional;
    double fixedRate;

};


struct FloatingLeg{
    std::string index;
    int tenorMonths;
};


struct Swap{
    std::optional<FixedLeg> fixedLeg;
    std::optional<FloatingLeg> floatingLeg;
};
