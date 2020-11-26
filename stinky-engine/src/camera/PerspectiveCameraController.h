//
// Created by christian on 29/08/2020.
//

#pragma once

#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "core/KeyboardCodes.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
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

        void OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent);

        void OnMousePressed(const MouseButtonPressedEvent &event);
        void OnMouseReleased(const MouseButtonReleasedEvent &event);
        void OnMouseMoved(const MouseMovedEvent &event);

        void OnWindowResize(const WindowResizeEvent &event);
        void OnWindowResize(uint32_t width, uint32_t height);
    private:
        PerspectiveCamera *m_Camera = nullptr;
        glm::vec2 m_OldMousePosition{1.0f, 1.0f};
        glm::vec2 m_NewMousePosition{1.0f, 1.0f};
        bool m_MousePressed = false;
        bool m_Rotate = false;

        glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
        float m_CameraSpeed = 60.0f;
        float m_RotationSpeed = 1.2f;

        std::unordered_map<KeyCode, std::function<void()>> m_CameraMoveFunctions;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////