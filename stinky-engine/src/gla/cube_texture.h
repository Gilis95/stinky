#pragma once

#include <string>

#include "gla/texture.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class cube_texture : public texture {
    private:
        typedef unsigned char byte;

        enum class InputImageFormat {
            RGB = 0,
            RGBA
        };
    public:
        explicit cube_texture(std::string path);

        ~cube_texture() override = default;

        void LoadFromSingleFile();

        void set_data(void *data) override;

        [[nodiscard]] uint32_t get_width() const override {
            return _M_face_width;
        }

        [[nodiscard]] uint32_t get_height() const override {
            return _M_face_height;
        }

    protected:
        byte *_M_left = nullptr;
        byte *_M_right = nullptr;
        byte *_M_top = nullptr;
        byte *_M_bottom = nullptr;
        byte *_M_back = nullptr;
        byte *_M_front = nullptr;

        uint32_t _M_face_height, _M_face_width;
        InputImageFormat _M_input_format = InputImageFormat::RGB;
    private:
        std::string _M_path;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////