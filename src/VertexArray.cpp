//
// Created by christian on 1/19/20.
//
#include "VertexArray.h"

#include "Logger.h"
#include "Renderer.h"
#include "glad/glad.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
    bind();
}

VertexArray::~VertexArray() {
    unbind();
}


void VertexArray::bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    vb.bind();

    auto layoutElements = layout.getElements();

    for (unsigned int i = 0, offset = 0; i < layoutElements.size(); i++) {
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, layoutElements[i].count, layoutElements[i].type, layoutElements[i].normalized,
                                     layout.getStride(), nullptr));
        offset += layoutElements[i].count * VertexBufferElement::getSizeOfType(layoutElements[i].type);
    }
}
