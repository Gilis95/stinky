//
// Created by christian on 13/10/2020.
//

#pragma once

#include "glm/glm.hpp"
#include "StinkyPrerequisites.h"
#include "core/StinkyMemory.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class MeshComponent {
    public:
        MeshComponent() = default;
        explicit MeshComponent(Ref<VertexArray> vertexArray);
        MeshComponent(MeshComponent &&) = default;
        virtual ~MeshComponent() = default;

        MeshComponent &operator=(MeshComponent &&copy) noexcept {
            vertexArray = copy.vertexArray;

            return *this;
        }

        Ref<VertexArray> vertexArray;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
