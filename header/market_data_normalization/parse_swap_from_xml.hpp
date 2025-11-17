#pragma once
#include <string>
#include "market_data_normalization/fpml_swap.hpp"

Swap parseSwapFromXml(const std::string& xmlContent);
