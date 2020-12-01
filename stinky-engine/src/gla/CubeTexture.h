#pragma once

#include <string>

#include "gla/Texture.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class CubeTexture : public Texture {
    private:
        typedef unsigned char byte;

        enum class InputImageFormat {
            RGB = 0,
            RGBA
        };
    public:
        explicit CubeTexture(std::string path);

        ~CubeTexture() override = default;

        void LoadFromSingleFile();

        void SetData(void *data) override;

        [[nodiscard]] int GetWidth() const override {
            return m_FaceWidth;
        }

        [[nodiscard]] int GetHeight() const override {
            return m_FaceHeight;
        }

    protected:
        byte *m_Left = nullptr;
        byte *m_Right = nullptr;
        byte *m_Top = nullptr;
        byte *m_Bottom = nullptr;
        byte *m_Back = nullptr;
        byte *m_Front = nullptr;

        uint32_t m_FaceHeight, m_FaceWidth;
        InputImageFormat m_InputFormat = InputImageFormat::RGB;
    private:
        std::string m_Path;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////