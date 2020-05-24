//
// Created by christian on 5/4/20.
//

#ifndef ENGINE_ASSERT_H
#define ENGINE_ASSERT_H
#include "Macros.h"
#include "Logger.h"

#ifdef ENABLE_ASSERTS
#define ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUGBREAK(); } }
#else
#define ASSERT(x, ...)
#endif

#endif //ENGINE_ASSERT_H
