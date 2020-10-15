//
// Created by christian on 5/3/20.
//

#pragma once

#include <spdlog/spdlog.h>
#include "StinkyMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    bool GLLogCall(const char *functionName, const char *fileName, int line);

    /////////////////////////////////////////////////////////////////////////////////////////
    void GLClearError();

    /////////////////////////////////////////////////////////////////////////////////////////
    class Log {
    public:
        static void Init();

        static Ref<spdlog::logger> &getClientLogger() {
            return s_Logger;
        }

    private:
        Log() = default;;
        static Ref<spdlog::logger> s_Logger;
    };
}

#if defined(ENABLE_LOG)
#define STINKY_TRACE(...)         stinky::Log::getClientLogger()->trace(__VA_ARGS__)
#define STINKY_INFO(...)          stinky::Log::getClientLogger()->info(__VA_ARGS__)
#define STINKY_WARN(...)          stinky::Log::getClientLogger()->warn(__VA_ARGS__)
#define STINKY_ERROR(...)         stinky::Log::getClientLogger()->error(__VA_ARGS__)
#define STINKY_CRITICAL(...)      stinky::Log::getClientLogger()->critical(__VA_ARGS__)
#else
#define STINKY_TRACE(...)
#define STINKY_INFO(...)
#define STINKY_WARN(...)
#define STINKY_ERROR(...)
#define STINKY_CRITICAL(...)
#endif


#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__,__LINE__);
