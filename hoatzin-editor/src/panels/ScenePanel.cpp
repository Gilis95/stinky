//
// Created by christian on 05/11/2020.
//

#include <imgui.h>
#include <Tracy.hpp>
#include "panels/ScenePanel.h"

namespace stinky::hoatzin::ScenePanel {
    /////////////////////////////////////////////////////////////////////////////////////////
    void Render(uint32_t textureId, glm::vec<2, uint32_t, glm::defaultp> &outViewportSize) {
        {
            ZoneScopedN("ScenePanel")

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
            ImGui::Begin("Scene");


            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            outViewportSize = {viewportPanelSize.x, viewportPanelSize.y};


            ImGui::Image(reinterpret_cast<void *>(textureId), ImVec2{static_cast<float>(outViewportSize.x), static_cast<float>(outViewportSize.y)},
                         ImVec2{0, 1},
                         ImVec2{1, 0});
            ImGui::End();
            ImGui::PopStyleVar();
        }
    }
}