#pragma once

#include <glm/glm.hpp>

#include "event/event_controller.h"
#include "event/layer.h"
#include "scene/scene.h"
#include "StinkyPrerequisites.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    class StinkyLayer : public layer {
    public:
        explicit StinkyLayer(graphic_layer_abstraction_factory *glaFactory, track_ball_camera *cameraController,
                             event_controller &eventController, unsigned width, unsigned height);

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(const time_frame &ts) override;

    private:
        graphic_layer_abstraction_factory *m_GLAFactory;
        scene m_Scene;
        shared_ptr<frame_buffer> m_FrameBuffer;
        track_ball_camera *m_Camera;
    };
    /////////////////////////////////////////////////////////////////////////////////////////
}
