//
// Created by christian on 09/02/2020.
//
#pragma once

#include <string>
#include "gla/texture.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OpenGLTexture : public texture {
    public:
        explicit OpenGLTexture(const std::string &path);

        OpenGLTexture(uint32_t width, uint32_t height);

        ~OpenGLTexture() override;

        void bind(unsigned int slot = 0) const override;

        void unbind(uint32_t slot) const override;

        void set_data(void *data) override;

        [[nodiscard]] int GetWidth() const override {
            return m_Width;
        };

        [[nodiscard]] int GetHeight() const override {
            return m_Height;
        };
    private:
        int m_Width, m_Height;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////