#pragma once
#include <string>
#include <vector>

bool isSymbolPalindrome(std::string symbol);
bool isHomegenousBlock(const std::vector<std::string>& grid,int row,int col);
std::vector<std::pair<int,int>> centerOfSquare(const std::vector<std::string> &grid, int &nbOfSquares);
int symbolToInt(const std::string&  line);
