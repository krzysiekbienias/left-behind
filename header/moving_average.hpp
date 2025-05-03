#pragma once
#include <deque>


class MovingAverage{
    private :
    int m_size;
    std::deque<int> m_window;
    int m_runningSum{0};//there is no need to expose it, becasue it's purely an internal optimization, to make next() O(1)
    
public:
    
    
    explicit MovingAverage(int size); //constructor
    float next(int val);
    
    int getSize()const ;
    
    
    void setSize(int newSize);
    
};
