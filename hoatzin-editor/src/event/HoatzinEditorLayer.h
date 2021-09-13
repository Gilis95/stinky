#pragma once

#include <event/layer.h>
#include <scene/scene.h>
#include <StinkyPrerequisites.h>

#include "save/SaveManager.h"

namespace stinky::hoatzin {
    /////////////////////////////////////////////////////////////////////////////////////////
    class HoatzinEditorLayer : public layer {
    public:
        HoatzinEditorLayer(graphic_layer_abstraction_factory *glaFactory, fps_camera *camera,
                           event_controller &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnUpdate(const time_frame &ts) override;

        void OnClose();

        void ImGuiBegin();

        void ImGuiRender();

        void ImGuiEnd();

    private:
        graphic_layer_abstraction_factory *m_GLAFactory;
        scene m_Scene;
        SaveManager m_SceneManager;
        shared_ptr<frame_buffer> m_FrameBuffer;
        fps_camera *m_Camera;
        event_controller &m_EventController;

        entity m_SelectedEntt;
        glm::vec<2, uint32_t, glm::defaultp> m_ViewportSize{0, 0};
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
