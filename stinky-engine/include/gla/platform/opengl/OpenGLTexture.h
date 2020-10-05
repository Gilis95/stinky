//
// Created by christian on 09/02/2020.
//
#pragma once

#include "stinkypch.h"
#include "gla/Texture.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLTexture : public Texture {
    public:
        explicit OpenGLTexture(const std::string &path);

        OpenGLTexture(uint32_t width, uint32_t height);

        ~OpenGLTexture() override;

        void Bind(unsigned int slot = 0) const override;

        void Unbind() const override;

        void SetData(void *data) override;

        [[nodiscard]] int GetWidth() const override {
            return m_Width;
        };

        [[nodiscard]] int GetHeight() const override {
            return m_Height;
        };
    private:
        GLuint m_RendererID;
        int m_Width, m_Height;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////