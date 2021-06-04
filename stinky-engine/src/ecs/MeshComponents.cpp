//
// Created by christian on 13/10/2020.
//

#include "glm/glm.hpp"
#include "MeshComponents.h"

#include <utility>
#include "gla/VertexArray.h"


namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    MeshComponent::MeshComponent(Ref<VertexArray> vertexArray)
            : vertexArray(std::move(vertexArray)) {
    }

}