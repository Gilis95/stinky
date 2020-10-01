//
// Created by christian on 1/26/20.
//
#pragma once

#include "stinkypch.h"

#include <glm/glm.hpp>

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual void SetInteger(const std::string &name, int i) = 0;

        virtual void SetFloat4(const std::string &name, float f0, float f1, float f2, float f3) = 0;

        virtual void SetMat4(const std::string &name, glm::mat4 matrix) = 0;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}