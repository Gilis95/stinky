//
// Created by christian on 05/11/2020.
//
#include <scene/scene.h>
#include <ecs/entity.h>
#include <imgui.h>
#include <ecs/tag_component.h>
#include <Tracy.hpp>

#include "panels/SceneHierarchyPanel.h"

namespace stinky::hoatzin::SceneHierarchyPanel {

    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(scene &scene, entity &outSelectedEntt) {
        ZoneScopedN("SceneHierarchyPanel")

        ImGui::Begin("Hierarchy");
        scene.each([&outSelectedEntt](entity &entt) {
            auto tag = entt.get_component<tag_component>();
            if (tag.has_value()) {
                if (ImGui::Selectable(tag.value().get().name.c_str(), outSelectedEntt == entt)) {
                    outSelectedEntt = entt;
                }
            }
        });

        ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}