//
// Created by christian on 05/11/2020.
//

#include <ecs/Entity.h>
#include <ecs/TransformComponent.h>
#include <imgui.h>

#include "panels/EntityInspectorPanel.h"
#include "style/HoatzinImGui.h"

namespace stinky::hoatzin::EntityInspectorPanel {
    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(Entity &selectedEntt) {
        ImGui::Begin("Inspector");
        if (selectedEntt) {
            auto transform = selectedEntt.GetComponent<TransformComponent>();
            if (transform.first) {
                if (ImGui::CollapsingHeader("Transformation")) {
                    HoatzinImGui::DrawVec3Control("Translation", transform.second.get().translation);
                    HoatzinImGui::DrawVec3Control("Scale", transform.second.get().scale);
                    HoatzinImGui::DrawVec3Control("Rotation", transform.second.get().rotation);
                }
            }
        }
        ImGui::End();
    }
}