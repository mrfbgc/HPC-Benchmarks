#ifndef TIMING_HPP
#define TIMING_HPP

#include <chrono>

inline double getTimeStamp() {
    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration<double>(duration).count();
}

#endif // TIMING_HPP
