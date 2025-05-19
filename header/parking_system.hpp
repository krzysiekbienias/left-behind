#pragma once

class ParkingSystem{
private:
    int m_big_slots;
    int m_medium_slots;
    int m_small_slots;
public:
    ParkingSystem(int big, int medium, int small);
    bool addCar(int carType);
};


