//
// Created by christian on 19/10/2020.
//

#include "ecs/material_component.h"
#include "gla/texture.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    material_component::material_component(shared_ptr<texture> material, bool depthTest) : material(std::move(material)),
                                                                                           type(material_type::TEXTURED) {
        flags.emplace(material_flag::DepthTest, depthTest);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    material_component::material_component(glm::vec4 colour, bool depthTest) : colour(colour), type(material_type::SOLID) {
        flags.emplace(material_flag::DepthTest, depthTest);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool material_component::get_flag(material_flag flag) const {
        auto res = flags.find(flag);
        return res != flags.end() && res->second;
    }
}