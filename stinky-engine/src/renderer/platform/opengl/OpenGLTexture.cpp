
#include <glad/glad.h>

#include "stb_image.h"
#include "renderer/platform/opengl/OpenGLTexture.h"

namespace stinky
{

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::OpenGLTexture(const std::string& path) : m_FilePath(path)
    {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);


        GLenum internalFormat = 0, dataFormat = 0;
        if (m_BPP == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (m_BPP == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);


        if (m_LocalBuffer)
        {
            stbi_image_free(m_LocalBuffer);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::Bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}