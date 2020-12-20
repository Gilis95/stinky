//
// Created by christian on 18.12.20 г..
//

#pragma once

#include "StinkyMacros.h"
#include "StinkyPrerequisites.h"

#ifdef SK_PLATFORM_LINUX

#include <cstdint>
#include <bits/types/struct_timespec.h>

#endif

namespace stinky {
    /**
     * This class represents either certain time point or duration frame between two points. The precision of the class
     * is nanoseconds.
     */
    class TimeFrame {
    public:
        friend int stinky::this_thread::sleep(const TimeFrame&, TimeFrame&);

    public:
        [[nodiscard]] static TimeFrame now();

    public:
#ifdef SK_PLATFORM_LINUX

        /**
         * Initialize time point 0 nanoseconds
         */
        TimeFrame();

        TimeFrame(const TimeFrame &other);

        TimeFrame(TimeFrame &&other) noexcept;

        explicit TimeFrame(__syscall_slong_t nanoseconds);

        explicit TimeFrame(timespec timepoint);

        /**
         * @param nanoseconds - time point class one to be aligned with.
         */
        void Assign(__syscall_slong_t nanoseconds);

        /**
         * Assigns time frame data to current time.
         */
        void AssignCurrentTime();

        /**
         * @return frame represented as a nano seconds.
         */
        [[nodiscard]] __syscall_slong_t NanoSeconds() const;

        /**
         * @return rounded up micro seconds of the frame.
         */
        [[nodiscard]] __syscall_slong_t MicroSeconds() const;

        /**
         * @return rounded up mili seconds of the frame.
         */
        [[nodiscard]] __syscall_slong_t MiliSeconds() const;

        /**
         * @return rounded up seconds of the frame.
         */
        [[nodiscard]] __syscall_slong_t Seconds() const;

#endif
    public:
        /**
         * Subtract given time frame from current and return new resulting time frame.
         * New time frame is clamped in values between 0 and 999999999.
         */
        TimeFrame operator-(const TimeFrame &other) const;

        /**
         * Add given time frame to current and return new resulting time frame.
         * New time frame is clamped in values between 0 and 999999999.
         */
        TimeFrame operator+(const TimeFrame &other) const;

        /**
         * Subtract given time frame from current, time is clamped in values between 0 and 999999999.
         */
        void operator-=(const TimeFrame &other);

        TimeFrame &operator=(const TimeFrame &other);

        bool operator<(const TimeFrame &other) const;

    private:
#ifdef SK_PLATFORM_LINUX
        struct timespec m_Data;
#endif
    };
}
