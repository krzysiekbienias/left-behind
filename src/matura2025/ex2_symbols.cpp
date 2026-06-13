#include "matura2025/ex2_symbols.hpp"
#include <iostream>
#include <vector>

bool isSymbolPalindrome(std::string symbol) {
  while (!symbol.empty() && (symbol.back() == '\r') || symbol.back() == '\n') {
    symbol.pop_back();
  }
  int lPointer = 0;
  int rPointer = symbol.length() - 1;
  while (lPointer <= rPointer) {
    if (symbol[lPointer] == symbol[rPointer]) {
      lPointer++;
      rPointer--;
    } else
      return false;
  }
  return true;
}

int symbolToInt(const std::string&  line) {
  int res=0;
  for (char ch:line){
      res*=3;
      if (ch == '+')
         res+=1;
      else if (ch == 'o')
          res+=0;
      else if( ch=='*')
          res+=2;
  }
  return res;
}


bool isHomegenousBlock(const std::vector<std::string> &grid, int row, int col) {
  char ch = grid[row][col]; // top left
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (grid[row + i][col + j] != ch)
        return false;
    }
  }
  return true;
}

std::vector<std::pair<int,int>> centerOfSquare(const std::vector<std::string> &grid, int &nbOfSquares) {
  std::vector<std::pair<int,int>> centers;
  int rows = grid.size();
  int cols = grid[0].size();
  for (int i = 0; i <= rows - 3; ++i) {
    for (int j = 0; j <= cols - 3; ++j) {
      if (isHomegenousBlock(grid, i, j)) {
        nbOfSquares++;
        centers.push_back({i+2,j+2});
    }
  }
}
return centers;
}
