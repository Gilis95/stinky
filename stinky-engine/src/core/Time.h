//
// Created by christian on 18.12.20 г..
//

#pragma once

#include "stinky_macros.h"
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
    class time_frame {
    public:
        friend int stinky::this_thread::sleep(const time_frame&, time_frame&);

    public:
        [[nodiscard]] static time_frame now();

    public:
#ifdef SK_PLATFORM_LINUX

        /**
         * Initialize time point 0 nanoseconds
         */
        time_frame();

        time_frame(const time_frame &other);

        time_frame(time_frame &&other) noexcept;

        explicit time_frame(__syscall_slong_t nanoseconds);

        explicit time_frame(timespec timepoint);

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
        time_frame operator-(const time_frame &other) const;

        /**
         * Add given time frame to current and return new resulting time frame.
         * New time frame is clamped in values between 0 and 999999999.
         */
        time_frame operator+(const time_frame &other) const;

        /**
         * Subtract given time frame from current, time is clamped in values between 0 and 999999999.
         */
        void operator-=(const time_frame &other);

        time_frame &operator=(const time_frame &other);

        bool operator<(const time_frame &other) const;

    private:
#ifdef SK_PLATFORM_LINUX
        struct timespec m_Data;
#endif
    };
}
