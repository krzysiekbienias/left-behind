
#include "my_calendar_1.hpp"

#include <std_aliases.hpp>

using namespace stl;
using namespace io;


bool MyCalendar:: book(int startTime, int endTime) {
    auto nextIt=calendar.lower_bound(startTime); //lower_bound from definition gives us next key >= startTime
    // -->
    if (nextIt!=calendar.end()) {
        int nextStart=nextIt->first;
        int nextEnd=nextIt->second;

        if (endTime>nextStart) return false;
    }
        // <--
        if (nextIt!=calendar.begin()){
            auto prevIt=std::prev(nextIt);
            int prevStart=prevIt->first;
            int prevEnd=prevIt->second;
            if (startTime<prevEnd) return false;

        }
    calendar.emplace(startTime,endTime);
    return true;
    }