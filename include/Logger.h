//
// Created by christian on 5/3/20.
//

#pragma once

#include <spdlog/spdlog.h>
#include "Macros.h"

bool GLLogCall(const char *functionName, const char *fileName, int line);


class Log {
public:
    static void init();

    static Ref<spdlog::logger> &getClientLogger(){
        return s_Logger;
    }

private:
    Log() = default;;
    static Ref<spdlog::logger> s_Logger;
};

#if defined(ENABLE_LOG)
#define TRACE(...)         Log::getClientLogger()->trace(__VA_ARGS__)
#define INFO(...)          Log::getClientLogger()->info(__VA_ARGS__)
#define WARN(...)          Log::getClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)         Log::getClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      Log::getClientLogger()->critical(__VA_ARGS__)


#else
#define TRACE(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define CRITICAL(...)

#endif


#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__,__LINE__);
