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
        PerspectiveCameraController(float translationSpeed, float rotationSpeed);

        ~PerspectiveCameraController();

    public:
        //Camera Rotation
        virtual void Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const Timestep &ts) = 0;

        // Translate the camera by some amount. If local is TRUE (default) then the translation should
        // be applied in the local-space of the camera. If local is FALSE, then the translation is
        // applied in world-space.
        virtual void Translate(const glm::vec3 &delta, bool local = false) = 0;

    public:
        // Camera move trough XYZ
        void MoveLeft();

        void MoveRight();

        void MoveUp();

        void MoveDown();

        void MoveNear();

        void MoveFar();

        void OnUpdate(const Timestep &ts);

        void OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent);

        void OnMouseScrolled(const MouseScrolledEvent &event);

        void OnMousePressed(const MouseButtonPressedEvent &event);

        void OnMouseReleased(const MouseButtonReleasedEvent &event);

        void OnMouseMoved(const MouseMovedEvent &event);

        void OnWindowResize(const WindowResizeEvent &event);

        virtual void OnWindowResize(uint32_t width, uint32_t height) = 0;

    protected:
        float m_TranslationSpeed = 300.0f;
        float m_RotationSpeed;
    private:
        glm::vec3 m_OldMousePosition{1.0f, 1.0f, 0.0f};
        glm::vec3 m_NewMousePosition{1.0f, 1.0f, 0.0f};
        bool m_MousePressed = false;
        bool m_Rotate = false;

        glm::vec3 m_TranslationVec{0.0f, 0.0f, 0.0f};
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////