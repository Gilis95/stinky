//
// Created by christian on 19/10/2020.
//

#include "gla/platform/opengl/OpenGLCubeTexture.h"

#include <utility>
#include <glad/glad.h>
#include <stb_image_write.h>

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLCubeTexture::OpenGLCubeTexture(std::string path) : CubeTexture(std::move(path)) {
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        int inputImageFormat = GL_RGB + static_cast<int>(m_InputFormat);
        int dataFormat = GL_RGB + static_cast<int>(m_InputFormat);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Right);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Left);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Top);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Bottom);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Front);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, dataFormat, m_FaceWidth, m_FaceHeight, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, m_Back);

        delete[] m_Right;
        delete[] m_Left;
        delete[] m_Top;
        delete[] m_Bottom;
        delete[] m_Front;
        delete[] m_Back;

        m_Right = nullptr;
        m_Left = nullptr;
        m_Top = nullptr;
        m_Bottom = nullptr;
        m_Front = nullptr;
        m_Back = nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLCubeTexture::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLCubeTexture::Unbind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}