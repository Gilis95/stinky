//
// Created by christian on 19/10/2020.
//

#include "ecs/MaterialComponent.h"
#include "gla/Texture.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    MaterialComponent::MaterialComponent(Ref<Texture> material, bool depthTest) : material(std::move(material)),
                                                                  type(MaterialType::TEXTURED) {
        flags.emplace(MaterialFlag::DepthTest, depthTest);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    MaterialComponent::MaterialComponent(glm::vec4 colour, bool depthTest) : colour(colour), type(MaterialType::SOLID) {
        flags.emplace(MaterialFlag::DepthTest, depthTest);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool MaterialComponent::GetFlag(MaterialFlag flag) const {
        auto res = flags.find(flag);
        return res != flags.end() && res->second;
    }
}