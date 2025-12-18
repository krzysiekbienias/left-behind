#pragma once
#include "market_tick.hpp"
#include <string>
#include <vector>


/**
 * @class IMarketDataParser
 * @brief Abstract interface for parsing market data from various input formats.
 *
 * This interface defines a common contract for parsing market tick data from either
 * individual lines (e.g., CSV or line-based text files) or full input streams (e.g., JSON arrays).
 *
 * Implementations of this interface can be used polymorphically in systems that handle
 * multiple data formats without needing to know the concrete parsing logic.
 *
 * Typical implementations:
 * - CSVParser: Parses market ticks line-by-line from a CSV file.
 * - JSONParser: Parses a full JSON array of market ticks from an input stream.
 *
 * @note This interface enables plug-and-play parser selection based on file format or user configuration.
 */
class IMarketDataParser {
public:
   /**
    * @brief Parses a single line of input into a MarketTick object.
    *
    * This method is typically used for line-oriented formats like CSV or TSV.
    *
    * @param line A single line of text representing a market tick.
    * @return A MarketTick object constructed from the input line.
    * @throws std::runtime_error If the line is malformed or cannot be parsed.
    */
    
    virtual MarketTick parse(const std::string& line) const = 0;
    /**
     * @brief Parses an entire input stream into a vector of MarketTick objects.
     *
     * This is useful for formats that must be processed as a whole, such as JSON arrays.
     *
     * @param input A stream (e.g., std::ifstream) containing market data.
     * @return A vector of MarketTick objects parsed from the stream.
     * @throws std::runtime_error If the stream contains malformed data.
     */
    virtual std::vector<MarketTick> parseStream(std::istream & input) const=0;
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~IMarketDataParser() = default;
};
