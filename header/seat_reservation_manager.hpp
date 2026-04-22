#pragma once
#include <queue>


class SeatManager {
public:
    SeatManager(int n);

    int reserve();

    void unreserve(int seatNumber);

private:
    int nextFreshSeat=0;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};
