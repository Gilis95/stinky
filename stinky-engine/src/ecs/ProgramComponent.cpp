//
// Created by christian on 19/10/2020.
//

#include "ecs/ProgramComponent.h"

#include <utility>

#include "gla/Shader.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    ProgramComponent::ProgramComponent(Ref<Shader> program) : program(std::move(program)) {
    }
}