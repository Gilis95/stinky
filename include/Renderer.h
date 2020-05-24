//
// Created by christian on 1/19/20.
//
#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer{
public:
    void clear() const ;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const ;
};
