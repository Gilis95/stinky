
#include <glad/glad.h>

#include "stb_image.h"
#include "gla/platform/opengl/OpenGLTexture.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::OpenGLTexture(const std::string &path) {
        stbi_set_flip_vertically_on_load(1);
        int bpp;
        unsigned char *localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &bpp, 0);


        GLenum internalFormat = 0, dataFormat = 0;
        if (bpp == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (bpp == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE,
                            localBuffer);

        if (localBuffer) {
            stbi_image_free(localBuffer);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {
        GLenum internalFormat = GL_RGBA8;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::~OpenGLTexture() {
        glDeleteTextures(1, &m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTextureUnit(slot, m_RendererID);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::Unbind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::SetData(void *data) {
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE,
                            data);
    }
}