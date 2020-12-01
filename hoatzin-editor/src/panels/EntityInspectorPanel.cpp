//
// Created by christian on 05/11/2020.
//

#include <ecs/Entity.h>
#include <ecs/TransformComponent.h>
#include <imgui.h>
#include <Tracy.hpp>

#include "panels/EntityInspectorPanel.h"
#include "style/HoatzinImGui.h"

namespace stinky::hoatzin::EntityInspectorPanel {
    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(Entity &selectedEntt) {
        ZoneScopedN("EntityInspectionPanel")

        ImGui::Begin("Inspector");
        if (selectedEntt) {
            auto transform = selectedEntt.GetComponent<TransformComponent>();
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