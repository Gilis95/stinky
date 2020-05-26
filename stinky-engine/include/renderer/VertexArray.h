//
// Created by christian on 1/19/20.
//
#pragma once

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"


namespace stinky {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        [[nodiscard]] virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
        virtual void addVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
    };
}