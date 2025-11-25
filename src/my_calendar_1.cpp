
#include "my_calendar_1.hpp"

#include <std_aliases.hpp>

using namespace stl;
using namespace io;


bool MyCalendar:: book(int startTime, int endTime) {
    cout <<"Incoming event"<<endl;
    cout<<"\t[" <<startTime<<","<<endTime<<")"<<endl;
    if (calendar.empty()) {

        calendar[startTime]=endTime;
        return true;
    }

    auto it=calendar.lower_bound(startTime);

    if (it!=calendar.end() && endTime>it->first) {
        std::cout<<"next: ["<<it->first<< ","<<it->second<<")\n";

        return false;
    }
    else {
        cout<<"there is no next \n";
    }

    if (it!=calendar.begin()) {
        auto pit=std::prev(it);
        std::cout<<"prev: ["<<pit->first<<","<<pit->second<<")\n";
        if (startTime<pit->second) return false;
    }
    else cout <<"there is no previous event"<<endl;

    calendar.emplace(startTime,endTime);
    return true;

    return true;

}