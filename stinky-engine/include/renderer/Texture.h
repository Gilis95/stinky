//
// Created by christian on 09/02/2020.
//
#pragma once

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void Bind(unsigned int slot) const = 0;

        virtual void Unbind() const = 0;

        [[nodiscard]] virtual int GetWidth() const = 0;

        [[nodiscard]] virtual int GetHeight() const = 0;
    };
}