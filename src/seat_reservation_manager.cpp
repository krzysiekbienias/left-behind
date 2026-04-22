#include <queue>
#include "seat_reservation_manager.hpp"


SeatManager::SeatManager(int n){};

int SeatManager::reserve() {
    if (minHeap.empty()) {
        nextFreshSeat++;
        return nextFreshSeat;
    }
    {
        int res=minHeap.top();
        minHeap.pop();
     return res;
    }
}

void SeatManager::unreserve(int seatNumber) {
    minHeap.push(seatNumber);
}
