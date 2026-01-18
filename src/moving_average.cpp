#include "moving_average.hpp"


MovingAverage::MovingAverage(int size) : m_size(size) {
};

void MovingAverage::setSize(int newSize) {
    if (newSize <= 0) {
        throw std::out_of_range("Size must be positive number");
    }
    m_size = newSize;
}

int MovingAverage::getSize() const {
    return m_size;
}

float MovingAverage::next(int val) {
    m_runningSum += val;
    m_window.push_back(val);
    if (m_window.size() > m_size) {
        m_runningSum -= m_window.front();
        m_window.pop_front();
    }
    return static_cast<double>(m_runningSum) / m_window.size();
}
