#pragma once
#include<map>


class MyCalendar {
public:
    MyCalendar() {

    }
    std::map<int,int> calendar;

    bool book(int startTime, int endTime);
};