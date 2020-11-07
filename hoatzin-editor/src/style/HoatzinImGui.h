//
// Created by christian on 04/11/2020.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky::hoatzin::HoatzinImGui {
    void
    DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float columnWidth = 100.0f);

    void OverrideImGuiColours();
}
