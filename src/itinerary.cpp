

#include <string>
#include <vector>
#include "itinerary.hpp"

std::string itinerary(std::vector<Route> travel)
{
    std::string res=travel[0].in+"-"+travel[0].out;

    for (int i = 1; i <travel.size(); ++i)
    {
        if (travel[i].in!=travel[i-1].out)
        {
            res+="-";
            res+=travel[i].in;
            res+="-";
            res+=travel[i].out;

        }
        else
        {
            res+="-";
            res+=travel[i].out;
        }

    }
    return res;
}
