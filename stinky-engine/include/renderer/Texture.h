//
// Created by christian on 09/02/2020.
//
#pragma once

#include <string>

namespace stinky {
    class Texture {
    public:
        virtual ~Texture() = default;

        virtual void bind(unsigned int slot) const = 0;

        virtual void unbind() const = 0;

        [[nodiscard]] virtual int getWidth() const = 0;

        [[nodiscard]] virtual int getHeight() const = 0;
    };
}