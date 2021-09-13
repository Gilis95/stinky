//
// Created by christian on 04/11/2020.
//

#pragma once

#include <string>

namespace stinky {
    class tag_component {
    public:
        explicit tag_component() = default;

        explicit tag_component(std::string name) : name(std::move(name)) {}

        ~tag_component() = default;

        std::string name;
    };
}