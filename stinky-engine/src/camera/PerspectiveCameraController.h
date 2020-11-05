//
// Created by christian on 29/08/2020.
//

#pragma once

#include "stinkypch.h"

#include "core/KeyboardCodes.h"
#include "event/Event.h"
#include "event/Timestep.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class PerspectiveCamera;

    class PerspectiveCameraController {
    public:
        PerspectiveCameraController();
        explicit PerspectiveCameraController(PerspectiveCamera *camera);

        ~PerspectiveCameraController();

        inline void SetCamera(PerspectiveCamera *camera) {
            m_Camera = camera;
        }

        //Camera Rotation
        void LookAt();
        void FPSLookAt(const Timestep &ts);

        // Camera move trough XYZ
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveNear();
        void MoveFar();

        void OnUpdate(const Timestep &ts);

        void OnKeyboardEvent(const Event &keyPressedEvent);

        void OnMousePressed(const Event &event);
        void OnMouseReleased(const Event &event);
        void OnMouseMoved(const Event &event);

        void OnWindowResize(const Event &event);
    private:
        PerspectiveCamera *m_Camera = nullptr;
        glm::vec2 m_OldMousePosition{1.0f, 1.0f};
        glm::vec2 m_NewMousePosition{1.0f, 1.0f};
        bool m_MousePressed = false;
        bool m_Rotate = false;

        glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
        float m_CameraSpeed = 1.0f;
        float m_RotationSpeed = 1.1f;

        std::unordered_map<KeyCode, std::function<void()>> m_CameraMoveFunctions;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////