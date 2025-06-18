#include "neighbor_sum_service.hpp"

NeighborSum::NeighborSum(const std::vector<std::vector<int>>& grid):m_grid(grid){};

int NeighborSum::adjacentSum(int value){
    int rows=m_grid.size();
    int cols=m_grid[0].size();
    int pos_i=-1;
    int pos_j=-1;
    bool found =false;
    //Step 1 find position of the value, so its coordinates
    
    for (int i=0;i<rows && !found;++i){
        for (int j=0;j<cols;++j){
            if(m_grid[i][j]==value){
                pos_i=i;
                pos_j=j;
                found=true;
                break;
            }
            
        }
    }
    if (!found) return -1;
    
    //Step 2 Define adjacent directions
    const std::vector<std::pair<int,int>> directions={
        {-1,0}, //up
        {1,0}, //down
        {0,-1}, //left
        {0,1} //right
    };
    int results{0};
    for (const auto &[di,dj]:directions){
        int new_i=pos_i+di;
        int new_j=pos_j+dj;
        if(new_i>=0 && new_i<rows && new_j>=0 && new_j<cols){
            results+=m_grid[new_i][new_j];
        }
    }
    return results;
}


int NeighborSum::diagonalSum(int value){
    int rows=m_grid.size();
    int cols=m_grid[0].size();
    int pos_i=-1;
    int pos_j=-1;
    bool found =false;
    //Step 1 find position of the value, so its coordinates
    
    for (int i=0;i<rows && !found;++i){
        for (int j=0;j<cols;++j){
            if(m_grid[i][j]==value){
                pos_i=i;
                pos_j=j;
                found=true;
                break;
            }
            
        }
    }
    if (!found) return -1;
    
    //Step 2 Define adjacent directions
    const std::vector<std::pair<int,int>> directions={
        {-1,-1}, //up-left
        {-1,1}, //up-right
        {1,-1}, //bottom-left
        {1,1} //bottom-right
    };
    int results{0};
    for (const auto &[di,dj]:directions){
        int new_i=pos_i+di;
        int new_j=pos_j+dj;
        if(new_i>=0 && new_i<rows && new_j>=0 && new_j<cols){
            results+=m_grid[new_i][new_j];
        }
    }
    return results;
}
