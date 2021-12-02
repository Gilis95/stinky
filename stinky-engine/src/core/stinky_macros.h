//
// Created by christian on 5/3/20.
//
#pragma once

#include "core/stinky_logger.h"

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#ifdef _WIN64
/* Windows x64  */
#define SK_PLATFORM_WINDOWS
#else
/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define SK_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define SK_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
#define SK_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define SK_PLATFORM_LINUX
#else

#endif // End of platform detection

#ifdef STINKY_ENGINE_DEBUG
#define ENABLE_ASSERTS
#if defined(PLATFORM_WINDOWS)
#define DEBUGBREAK() __debugbreak()
#elif defined(SK_PLATFORM_LINUX)

#include <signal.h>

#define DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#else
#define DEBUGBREAK()
#endif

#define STINKY_BIND(function) std::bind(&function, this, std::placeholders::_1)

#ifdef ENABLE_ASSERTS
#define STINKY_LOG_ERROR_AND_BREAK(...)                                        \
  {                                                                            \
    STINKY_ERROR(__VA_ARGS__);                                                 \
    DEBUGBREAK();                                                              \
  }
#else
#define STINKY_LOG_ERROR_AND_BREAK(...)
#endif

#define AssertLogIf(x, ...)                                                    \
  {                                                                            \
    if ((x)) {                                                                 \
      STINKY_ERROR("Assertion Failed: {0}", __VA_ARGS__);                      \
    }                                                                          \
  }
#define AssertLogUnless(x, ...)                                                \
  {                                                                            \
    if (!(x)) {                                                                \
      STINKY_ERROR("Assertion Failed: {0}", __VA_ARGS__);                      \
    }                                                                          \
  }

#define ReturnIf(x, ...)                                                       \
  {                                                                            \
    if (x) {                                                                   \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  }
#define ReturnUnless(x, ...)                                                   \
  {                                                                            \
    if (!(x)) {                                                                \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  }

#define AssertReturnIf(x, ...)                                                 \
  {                                                                            \
    if (x) {                                                                   \
      STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__,    \
                                 __LINE__, __FUNCTION__);                      \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  }
#define AssertReturnUnless(x, ...)                                             \
  {                                                                            \
    if (!(x)) {                                                                \
      STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__,    \
                                 __LINE__, __FUNCTION__);                      \
      return __VA_ARGS__;                                                      \
    }                                                                          \
  }

#define ContinueIf(x)                                                          \
  {                                                                            \
    if (x) {                                                                   \
      continue;                                                                \
    }                                                                          \
  }
#define ContinueUnless(x)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      continue;                                                                \
    }                                                                          \
  }

#define BreakIf(x)                                                             \
  {                                                                            \
    if (x) {                                                                   \
      break;                                                                   \
    }                                                                          \
  }
#define BreakUnless(x)                                                         \
  {                                                                            \
    if (!(x)) {                                                                \
      break;                                                                   \
    }                                                                          \
  }

#define AssertBreakIf(x)                                                       \
  {                                                                            \
    if (x) {                                                                   \
      STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__,    \
                                 __LINE__, __FUNCTION__);                      \
      break;                                                                   \
    }                                                                          \
  }
#define AssertBreakUnless(x)                                                   \
  {                                                                            \
    if (!(x)) {                                                                \
      STINKY_LOG_ERROR_AND_BREAK("Assertion Failed: {0} {1} {2}", __FILE__,    \
                                 __LINE__, __FUNCTION__);                      \
      break;                                                                   \
    }                                                                          \
  }

#define DESERIALIZE(FIELD_NAME, PARENT_NODE, FIELD, TYPE, ...)                 \
  {                                                                            \
    YAML::Node node = PARENT_NODE[FIELD_NAME];                                 \
    ReturnUnless(node, __VA_ARGS__) FIELD = node.as<TYPE>();                   \
  }
