//
// Created by christian on 1/19/20.
//
#pragma once

#include <vector>
#include "core/stinky_memory.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class vertex_array {
    public:
        virtual ~vertex_array() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        [[nodiscard]] virtual const std::vector<stinky::shared_ptr<vertex_buffer>>& get_vertex_buffers() const = 0;

        [[nodiscard]] virtual const stinky::shared_ptr<index_buffer>& get_index_buffer() const = 0;

        virtual void set_index_buffer(const stinky::shared_ptr<index_buffer>& indexBuffer) = 0;

        virtual void add_vertex_buffer(const stinky::shared_ptr<vertex_buffer>& vb) = 0;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////