#include "time.hpp"

using Clock = std::chrono::high_resolution_clock;
using Timestamp = Clock::time_point;
using Duration = Clock::duration;

Timestamp Motueur::Time::_last_time;
Timestamp Motueur::Time::_start_time;
float Motueur::Time::_delta_time;

inline float get_delta_seconds(Timestamp a, Timestamp b) {
    return std::chrono::duration_cast<std::chrono::duration<float>>(a - b).count();
}

void Motueur::Time::init() { _start_time = Clock::now(); }

void Motueur::Time::next_frame() {
    Timestamp current_time = Clock::now();

    _delta_time = get_delta_seconds(current_time, _last_time);

    _last_time = current_time;
}

float Motueur::Time::delta() { return _delta_time; }

float Motueur::Time::since_start() {
    return get_delta_seconds(Clock::now(), _last_time);
}
