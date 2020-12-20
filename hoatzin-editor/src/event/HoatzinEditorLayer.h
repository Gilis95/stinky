#pragma once

#include <event/Layer.h>
#include <scene/Scene.h>
#include <StinkyPrerequisites.h>

#include "save/SaveManager.h"

namespace stinky::hoatzin {
    /////////////////////////////////////////////////////////////////////////////////////////
    class HoatzinEditorLayer : public Layer {
    public:
        HoatzinEditorLayer(GraphicLayerAbstractionFactory *glaFactory, FPSCamera *camera,
                           EventController &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnUpdate(const TimeFrame &ts) override;

        void OnClose();

        void ImGuiBegin();

        void ImGuiRender();

        void ImGuiEnd();

    private:
        GraphicLayerAbstractionFactory *m_GLAFactory;
        Scene m_Scene;
        SaveManager m_SceneManager;
        Ref<FrameBuffer> m_FrameBuffer;
        FPSCamera *m_Camera;
        EventController &m_EventController;

        Entity m_SelectedEntt;
        glm::vec2 m_ViewportSize{0, 0};
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
