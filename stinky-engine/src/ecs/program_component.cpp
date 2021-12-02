//
// Created by christian on 19/10/2020.
//

#include "ecs/program_component.h"

#include <utility>

#include "gla/shader.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
program_component::program_component(shared_ptr<shader> program)
    : program(std::move(program)) {}
} // namespace stinky