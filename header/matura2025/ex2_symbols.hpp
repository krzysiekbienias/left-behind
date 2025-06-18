#pragma once
#include <string>
#include <vector>

bool isSymbolPalindrome(std::string symbol);
char symbolToInt(char symbol);
int fromTernaryToDecimal(const std::string & ternary);
bool isHomegenousBlock(const std::vector<std::string>& grid,int row,int col);
void countHomegenous3x3Squares(const std::vector<std::string>& grid);
