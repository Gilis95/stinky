//
// Created by christian on 1/19/20.
//

#pragma once

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual unsigned int GetCount() const = 0;
    };
}