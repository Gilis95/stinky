//
// Created by christian on 14/10/2020.
//
#include "ecs/TransformComponent.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    TransformComponent::TransformComponent(glm::vec3 &translation, glm::vec3 &scale, glm::vec3 &rotation)
        : translation(translation)
        , scale(scale)
        , rotation(rotation){
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    TransformComponent::TransformComponent(glm::vec3 &&translation, glm::vec3 &&scale, glm::vec3 &&rotation)
            : translation(std::forward<glm::vec3>(translation))
            , scale(std::forward<glm::vec3>(scale))
            , rotation(std::forward<glm::vec3>(rotation)) {
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////