//
// Created by christian on 18.12.20 г..
//
#include "stinky_macros.h"

#ifdef SK_PLATFORM_LINUX

#include "core/Time.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

#endif

namespace stinky {
#ifdef SK_PLATFORM_LINUX

/////////////////////////////////////////////////////////////////////////////////////////
time_frame time_frame::now() {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return time_frame(now.tv_sec * 1000000000 + now.tv_nsec);
}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame::time_frame() : m_Data{0, 0} {}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame::time_frame(const time_frame &other) : m_Data(other.m_Data){};

/////////////////////////////////////////////////////////////////////////////////////////
time_frame::time_frame(time_frame &&other) noexcept : m_Data(other.m_Data){};

/////////////////////////////////////////////////////////////////////////////////////////
time_frame::time_frame(__syscall_slong_t nanoseconds)
    : m_Data{nanoseconds / (1000000000),
             (std::abs((nanoseconds / (1000000000) * 1000000000) -
                       nanoseconds))} {}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame::time_frame(timespec timepoint) : m_Data(timepoint) {}

/////////////////////////////////////////////////////////////////////////////////////////
void time_frame::Assign(__syscall_slong_t nanoseconds) {
  m_Data = {nanoseconds / (1000000000),
            ((nanoseconds / (1000000000)) * 1000000000) - nanoseconds};
}

/////////////////////////////////////////////////////////////////////////////////////////
void time_frame::AssignCurrentTime() {
  clock_gettime(CLOCK_MONOTONIC, &m_Data);
}

/////////////////////////////////////////////////////////////////////////////////////////
__syscall_slong_t time_frame::NanoSeconds() const {
  return (m_Data.tv_sec * 10000000000) + m_Data.tv_nsec;
}

/////////////////////////////////////////////////////////////////////////////////////////
__syscall_slong_t time_frame::MicroSeconds() const {
  // nanosecond->miliseconds=10^3
  return m_Data.tv_nsec / 1000;
}

/////////////////////////////////////////////////////////////////////////////////////////
__syscall_slong_t time_frame::MiliSeconds() const {
  // nanosecond->miliseconds=10^6
  return m_Data.tv_nsec / (1000 * 1000);
}

/////////////////////////////////////////////////////////////////////////////////////////
__syscall_slong_t time_frame::Seconds() const {
  // nanosecond->seconds=10^9
  return m_Data.tv_sec;
}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame time_frame::operator-(const time_frame &other) const {
  return time_frame(
      {std::clamp(m_Data.tv_sec - other.m_Data.tv_sec, 0l, 999999999l),
       std::clamp(m_Data.tv_nsec - other.m_Data.tv_nsec, 0l, 999999999l)});
}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame time_frame::operator+(const time_frame &other) const {
  return time_frame(
      {std::clamp(m_Data.tv_sec + other.m_Data.tv_sec, 0l, 999999999l),
       std::clamp(m_Data.tv_nsec + other.m_Data.tv_nsec, 0l, 999999999l)});
}

/////////////////////////////////////////////////////////////////////////////////////////
void time_frame::operator-=(const time_frame &other) {
  m_Data.tv_sec =
      std::clamp(m_Data.tv_sec - other.m_Data.tv_sec, 0l, 999999999l);
  m_Data.tv_nsec =
      std::clamp(m_Data.tv_nsec - other.m_Data.tv_nsec, 0l, 999999999l);
}

/////////////////////////////////////////////////////////////////////////////////////////
time_frame &time_frame::operator=(const time_frame &other) {
  m_Data = other.m_Data;

  return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool time_frame::operator<(const time_frame &other) const {
  return m_Data.tv_sec < other.m_Data.tv_sec ||
         m_Data.tv_nsec < other.m_Data.tv_nsec;
}

#endif

} // namespace stinky
