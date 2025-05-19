#include "parking_system.hpp"

ParkingSystem::ParkingSystem(int big,int medium, int small):m_big_slots(big),m_small_slots(small),m_medium_slots(medium){};

bool ParkingSystem::addCar(int carType){
    if (carType==3 && m_small_slots>0) {
        --m_small_slots;
        return true;
    }
    if (carType==2 && m_medium_slots) {
        --m_medium_slots;
        return true;
    }
    if (carType==1 && m_big_slots) {
        --m_big_slots;
        
    }
    return false;
}
