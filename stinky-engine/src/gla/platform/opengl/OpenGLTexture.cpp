
#include <glad/glad.h>

#include "stb_image.h"
#include "gla/platform/opengl/OpenGLTexture.h"

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::OpenGLTexture(const std::string &path) {
        stbi_set_flip_vertically_on_load(1);
        int channelsCount;
        unsigned char *localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &channelsCount, 0);

        GLenum internalFormat = 0, dataFormat = 0;
        if (channelsCount == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (channelsCount == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        glGenTextures(1, &_M_renderer_id);
        glBindTexture(GL_TEXTURE_2D, _M_renderer_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, m_Width, m_Height, 0, internalFormat, GL_UNSIGNED_BYTE, localBuffer);

        if (localBuffer) {
            stbi_image_free(localBuffer);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {
        GLenum internalFormat = GL_RGBA8;

        glCreateTextures(GL_TEXTURE_2D, 1, &_M_renderer_id);
        glTextureStorage2D(_M_renderer_id, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(_M_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_M_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_M_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_M_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLTexture::~OpenGLTexture() {
        glDeleteTextures(1, &_M_renderer_id);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _M_renderer_id);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::unbind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLTexture::set_data(void *data) {
        glTextureSubImage2D(_M_renderer_id, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE,
                            data);
    }
}