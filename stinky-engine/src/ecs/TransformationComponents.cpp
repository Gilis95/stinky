//
// Created by christian on 14/10/2020.
//
#include "ecs/TransformationComponents.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    TranslateComponent::TranslateComponent(glm::vec3 &translation) : translation(translation) {
    }

    TranslateComponent::TranslateComponent(glm::vec3 &&translation) : translation(
            std::forward<glm::vec3>(translation)) {
    }

    ScaleComponent::ScaleComponent(glm::vec3 &amount) : scale(amount) {
    }

    ScaleComponent::ScaleComponent(glm::vec3 &&amount) : scale(std::forward<glm::vec3>(amount)) {
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////