//
// Created by christian on 09/02/2020.
//
#pragma once

#include "renderer/Texture.h"
#include "stinkypch.h"

namespace stinky
{
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(const std::string& path);
        ~OpenGLTexture();

        void Bind(unsigned int slot = 0) const override;

        void Unbind() const override;

        [[nodiscard]] int GetWidth() const override
        {
            return m_Width;
        };

        [[nodiscard]] int GetHeight() const override
        {
            return m_Height;
        };
    private:
        GLuint m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
    };
}