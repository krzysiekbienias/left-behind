#pragma once
#include<vector>


class NeighborSum{
private :
    const std::vector<std::vector<int>>& m_grid;
public:
    NeighborSum(const std::vector<std::vector<int>> & grid);
    int adjacentSum(int value);
    int diagonalSum(int value);
};
