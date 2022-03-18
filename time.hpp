#pragma once

#include <chrono>

namespace Motueur {

class Time {

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;

private:
    static Timestamp _last_time;
    static Timestamp _start_time;
    static float _delta_time;

public:
    static void init();
    static void next_frame();

    static float delta();
    static float since_start();
}; // namespace Time

} // namespace Motueur
