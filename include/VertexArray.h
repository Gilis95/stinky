//
// Created by christian on 1/19/20.
//
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_RendererID;
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void addBuffer(const VertexBuffer &vg, const VertexBufferLayout &layout);
};
