//
// Created by christian on 05/11/2020.
//

#include <ecs/entity.h>
#include <ecs/transform_component.h>
#include <imgui.h>
#include <Tracy.hpp>

#include "panels/EntityInspectorPanel.h"
#include "style/HoatzinImGui.h"

namespace stinky::hoatzin::EntityInspectorPanel {
    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(entity &selectedEntt) {
        ZoneScopedN("EntityInspectionPanel")

        ImGui::Begin("Inspector");
        if (selectedEntt) {
            auto transform = selectedEntt.get_component<transform_component>();
            if (transform.has_value()) {
                if (ImGui::CollapsingHeader("Transformation")) {
                    HoatzinImGui::DrawVec3Control("Translation", transform.value().get().translation);
                    HoatzinImGui::DrawVec3Control("Scale", transform.value().get().scale);
                    HoatzinImGui::DrawVec3Control("Rotation", transform.value().get().rotation);
                }
            }
        }
        ImGui::End();
    }
}