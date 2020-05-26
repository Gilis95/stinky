//
// Created by christian on 5/3/20.
//

#pragma once

#include <spdlog/spdlog.h>
#include "Macros.h"

namespace stinky {

    bool GLLogCall(const char* functionName, const char* fileName, int line);

    void GLClearError();

    class Log {
    public:
        static void init();

        static Ref<spdlog::logger>& getClientLogger() {
            return s_Logger;
        }

    private:
        Log() = default;;
        static Ref<spdlog::logger> s_Logger;
    };
}

#if defined(ENABLE_LOG)
#define TRACE(...)         stinky::Log::getClientLogger()->trace(__VA_ARGS__)
#define INFO(...)          stinky::Log::getClientLogger()->info(__VA_ARGS__)
#define WARN(...)          stinky::Log::getClientLogger()->warn(__VA_ARGS__)
#define ERROR(...)         stinky::Log::getClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...)      stinky::Log::getClientLogger()->critical(__VA_ARGS__)


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
