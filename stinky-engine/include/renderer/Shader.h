//
// Created by christian on 1/26/20.
//
#pragma once

#include <string>

namespace stinky {
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual void setInteger(const std::string& name, int i) = 0;

        virtual void setFloat4(const std::string& name, float f0, float f1, float f2, float f3) = 0;
    };
}