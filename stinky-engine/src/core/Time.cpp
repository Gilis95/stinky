//
// Created by christian on 18.12.20 г..
//
#include "StinkyMacros.h"

#ifdef SK_PLATFORM_LINUX

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "core/Time.h"

#endif

namespace stinky {
#ifdef SK_PLATFORM_LINUX

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame TimeFrame::now() {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        return TimeFrame(now.tv_sec * 1000000000 + now.tv_nsec);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame::TimeFrame() : m_Data{0, 0} {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame::TimeFrame(const TimeFrame &other) : m_Data(other.m_Data) {};

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame::TimeFrame(TimeFrame &&other) noexcept: m_Data(other.m_Data) {};

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame::TimeFrame(__syscall_slong_t nanoseconds) : m_Data{nanoseconds / (1000000000),
                                                                 (std::abs((nanoseconds / (1000000000) * 1000000000) -
                                                                      nanoseconds))} {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame::TimeFrame(timespec timepoint) : m_Data(timepoint) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    void TimeFrame::Assign(__syscall_slong_t nanoseconds) {
        m_Data = {nanoseconds / (1000000000), ((nanoseconds / (1000000000)) * 1000000000) - nanoseconds};
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TimeFrame::AssignCurrentTime() {
        clock_gettime(CLOCK_MONOTONIC, &m_Data);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    __syscall_slong_t TimeFrame::NanoSeconds() const {
        return (m_Data.tv_sec * 10000000000) + m_Data.tv_nsec;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    __syscall_slong_t TimeFrame::MicroSeconds() const {
        //nanosecond->miliseconds=10^3
        return m_Data.tv_nsec / 1000;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    __syscall_slong_t TimeFrame::MiliSeconds() const {
        //nanosecond->miliseconds=10^6
        return m_Data.tv_nsec / (1000 * 1000);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    __syscall_slong_t TimeFrame::Seconds() const {
        //nanosecond->seconds=10^9
        return m_Data.tv_sec;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame TimeFrame::operator-(const TimeFrame &other) const {
        return TimeFrame(
                {
                        std::clamp(m_Data.tv_sec - other.m_Data.tv_sec, 0l, 999999999l),
                        std::clamp(m_Data.tv_nsec - other.m_Data.tv_nsec, 0l, 999999999l)
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame TimeFrame::operator+(const TimeFrame &other) const {
        return TimeFrame(
                {
                        std::clamp(m_Data.tv_sec + other.m_Data.tv_sec, 0l, 999999999l),
                        std::clamp(m_Data.tv_nsec + other.m_Data.tv_nsec, 0l, 999999999l)
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void TimeFrame::operator-=(const TimeFrame &other) {
        m_Data.tv_sec = std::clamp(m_Data.tv_sec - other.m_Data.tv_sec, 0l, 999999999l);
        m_Data.tv_nsec = std::clamp(m_Data.tv_nsec - other.m_Data.tv_nsec, 0l, 999999999l);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TimeFrame &TimeFrame::operator=(const TimeFrame &other) {
        m_Data = other.m_Data;

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool TimeFrame::operator<(const TimeFrame &other) const {
        return m_Data.tv_sec < other.m_Data.tv_sec || m_Data.tv_nsec < other.m_Data.tv_nsec;
    }


#endif

}
