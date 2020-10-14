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
/** ####################################### Mesh Component Interfaces #######################################*/
    MeshVertexComponent::MeshVertexComponent(unsigned verticesCount, glm::vec4 *vertices) : verticesCount(
            verticesCount), vertices(vertices) {
    }

    MeshIndexComponent::MeshIndexComponent(unsigned indicesCount, unsigned *indices) : indicesCount(indicesCount),
                                                                                       indices(indices) {
    }
/** ####################################### Mesh Component Interfaces #######################################*/
}