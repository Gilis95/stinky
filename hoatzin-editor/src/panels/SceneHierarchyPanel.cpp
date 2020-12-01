//
// Created by christian on 05/11/2020.
//
#include <scene/Scene.h>
#include <ecs/Entity.h>
#include <imgui.h>
#include <ecs/TagComponent.h>
#include <Tracy.hpp>

#include "panels/SceneHierarchyPanel.h"

namespace stinky::hoatzin::SceneHierarchyPanel {

    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(Scene &scene, Entity &outSelectedEntt) {
        ZoneScopedN("SceneHierarchyPanel")

        ImGui::Begin("Hierarchy");
        scene.each([&outSelectedEntt](Entity &entt) {
            auto tag = entt.GetComponent<TagComponent>();
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