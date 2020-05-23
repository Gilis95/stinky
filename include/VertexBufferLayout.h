//
// Created by christian on 1/19/20.
//

#pragma once
#include <GL/glew.h>
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

    inline const unsigned int &getStride() const {
        return m_Stride;
    }

    inline const std::vector<VertexBufferElement> &getElements() const {
        return m_Elements;
    }
};