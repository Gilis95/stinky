//
// Created by christian on 13/10/2020.
//


//
// Created by christian on 13/10/2020.
//

#pragma once

#include "glm/glm.hpp"
#include "MeshComponents.h"


namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    MeshComponent::MeshComponent(unsigned verticesCount, glm::vec4 *vertices, unsigned indicesCount, unsigned *indices)
            : verticesCount(verticesCount), vertices(vertices), indicesCount(indicesCount), indices(indices) {
    }

}