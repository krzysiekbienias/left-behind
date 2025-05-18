#pragma once
#include <deque>


/**
 * @class MovingAverage
 * @brief A class that computes the moving average of a stream of integers using a sliding window.
 *
 * Maintains a fixed-size window of the most recent integers and calculates the average in O(1) time
 * by using an internal running sum. Internally uses a std::deque to manage window elements.
 *
 * Example usage:
 * @code
 * MovingAverage ma(3);
 * ma.next(1); // returns 1.0
 * ma.next(10); // returns 5.5
 * ma.next(3); // returns 4.67
 * ma.next(5); // returns 6.0
 * @endcode
 *
 * @note The running sum is kept private for optimization purposes and not exposed to the user.
 */

class MovingAverage{
    private :
    int m_size;
    std::deque<int> m_window;
    int m_runningSum{0};//there is no need to expose it, becasue it's purely an internal optimization, to make next() O(1)
    
public:
    
    /**
     * @brief Constructs a MovingAverage object with a specified window size.
     * @param size The size of the moving average window (must be > 0).
     */
    explicit MovingAverage(int size);
    
    /**
    * @brief Adds a new value to the stream and returns the updated moving average.
    *
    * If the window exceeds the maximum size, the oldest value is removed.
    *
    * @param val The new value to add to the moving average calculation.
    * @return The current moving average after adding the value.
    */
    float next(int val);
    /**
     * @brief Gets the current window size used for the moving average.
     * @return The size of the moving average window.
     */
    int getSize()const ;
    
    /**
     * @brief Sets a new window size for the moving average.
     *
     * Resets the internal state (window and running sum), since changing the size
     * invalidates the previous moving average state.
     *
     * @param newSize The new window size (must be > 0).
     */
    void setSize(int newSize);
    
};
