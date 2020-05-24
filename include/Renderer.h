//
// Created by christian on 1/19/20.
//
#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__,__LINE__);

void GLClearError();


bool GLLogCall(const char *functionName, const char *fileName, int line);


class Renderer{
public:
    void clear() const ;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const ;
};
