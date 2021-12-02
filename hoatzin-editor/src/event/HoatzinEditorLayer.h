#pragma once

#include <event/layer.h>
#include <scene/scene.h>
#include <stinky_prerequisites.h>

#include "save/SaveManager.h"

namespace stinky::hoatzin {
    /////////////////////////////////////////////////////////////////////////////////////////
    class HoatzinEditorLayer : public layer {
    public:
        HoatzinEditorLayer(graphic_layer_abstraction_factory *glaFactory, fps_camera *camera,
                           event_controller &eventController, unsigned width, unsigned height);

        void on_attach() override;

        void on_update(const time_frame &ts) override;

        void on_close();

        void im_gui_begin();

        void im_gui_render();

        void im_gui_end();

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
