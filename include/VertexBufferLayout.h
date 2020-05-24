//
// Created by christian on 1/19/20.
//
#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
        case GL_UNSIGNED_INT:
            return 4;
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 4;
        default:
            return 0;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<class BufferType>
    void push(unsigned int count) {
        std::cout << "ERROR: Should never enter here";
    }

    template<>
    void push<unsigned int>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += (count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT));
    }

    template<>
    void push<float>(unsigned int count) {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += (count * VertexBufferElement::getSizeOfType(GL_FLOAT));
    }

    template<>
    void push<unsigned char>(unsigned int count) {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += (count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE));
    }

    inline const unsigned int& getStride() const {
        return m_Stride;
    }

    inline const std::vector<VertexBufferElement>& getElements() const {
        return m_Elements;
    }
};
