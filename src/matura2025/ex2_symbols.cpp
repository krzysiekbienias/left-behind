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

char symbolToInt(char symbol) {
  if (symbol == '+')
    return '1';
  else if (symbol == 'o')
    return '0';
  else
    return '2';
}

int fromTernaryToDecimal(const std::string &ternary) {
  int result = 0;
  for (char ch : ternary) {
    result = result * 3 + (ch - '0');
  }
  return result;
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

void countHomegenous3x3Squares(const std::vector<std::string> &grid) {
  int count = 0;
  int rows = grid.size();
  int cols = grid[0].size();

  for (int i = 0; i <= rows - 3; ++i) {
    for (int j = 0; j <= cols - 3; ++j) {
      if (isHomegenousBlock(grid, i, j)) {
        std::cout << ++count << " " << i + 2 << " " << j + 2
                  << '\n'; // becasue in challange we had indeces from 1 for
                           // cols and rows
      }
    }
  }

}
