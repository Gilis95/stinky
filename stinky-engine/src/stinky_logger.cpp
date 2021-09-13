//
// Created by christian on 5/3/20.
//

#include "core/stinky_logger.h"
#include <iostream>
#include <glad/glad.h>

#include <sstream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace stinky {
    shared_ptr<spdlog::logger> Log::s_Logger;

    /////////////////////////////////////////////////////////////////////////////////////////
    void Log::Init() {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(
                std::make_shared<spdlog::sinks::basic_file_sink_mt>("Engine.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_Logger = std::make_shared<spdlog::logger>("Engine", begin(logSinks), end(logSinks));
        register_logger(s_Logger);
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->flush_on(spdlog::level::trace);

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    bool GLLogCall(const char *functionName, const char *fileName, int line) {
#if defined(ENABLE_LOG)
        while (GLenum err = glGetError()) {
            std::stringstream ss;
            ss << "[ OpenGL Error] (" << err << "): " <<
               functionName << " " << fileName << ":" << line;
            Log::getClientLogger()->error(ss.str());

            return false;
        }
#endif

        return true;
    }
}