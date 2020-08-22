//
// Created by christian on 1/19/20.
//
#pragma once

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"


namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;

        [[nodiscard]] virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;

        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vb) = 0;
    };
}