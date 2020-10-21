//
// Created by christian on 19/10/2020.
//

#include "ecs/MaterialComponent.h"
#include "gla/Texture.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    MaterialComponent::MaterialComponent(Ref<Texture> material) : material(std::move(material)),
                                                                  type(MaterialType::TEXTURED) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    MaterialComponent::MaterialComponent(glm::vec4 colour) : colour(colour), type(MaterialType::SOLID) {
    }
}


