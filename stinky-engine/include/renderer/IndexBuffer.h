//
// Created by christian on 1/19/20.
//

#pragma once

namespace stinky {
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual unsigned int getCount() const = 0;
    };
}