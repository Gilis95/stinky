//
// Created by christian on 09/02/2020.
//
#pragma once

#include "renderer/Texture.h"
#include "stinkypch.h"

namespace stinky {
    class OpenGLTexture : public Texture {
    public:
        OpenGLTexture(const std::string& path);
        ~OpenGLTexture();

        void bind(unsigned int slot = 0) const override;

        void unbind() const override;

        [[nodiscard]] int getWidth() const {
            return m_Width;
        };

        [[nodiscard]] int getHeight() const {
            return m_Height;
        };
    private:
        GLuint m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
    };
}