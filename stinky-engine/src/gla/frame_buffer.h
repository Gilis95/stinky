//
// Created by christian on 10/08/2020.
//
#pragma once


#include <cstdint>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    struct frame_buffer_specification {
        uint32_t width, height;
        uint32_t samples = 1;

        bool swap_chain_target = false;
    };

    class frame_buffer {
    public:
        explicit frame_buffer(const frame_buffer_specification &spec) : _M_specification(spec) {
        }

        virtual ~frame_buffer() = default;

        virtual void bind() = 0;

        virtual void unbind() = 0;

        virtual void window_resize(uint32_t width, uint32_t height) = 0;

        [[nodiscard]] virtual uint32_t get_color_attachment_renderer_id() const = 0;

        [[nodiscard]] const frame_buffer_specification &get_specification() const {
            return _M_specification;
        }

    protected:
        frame_buffer_specification _M_specification;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////