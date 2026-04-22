#pragma once
#include<map>


class MyCalendar {
public:
    MyCalendar() {

    }
    //represents start (key) end (value) for each event
    std::map<int,int> calendar;

    bool book(int startTime, int endTime);
};