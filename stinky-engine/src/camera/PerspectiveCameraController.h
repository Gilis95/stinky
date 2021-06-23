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
        virtual void
        Pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) = 0;

        //Camera Rotation
        virtual void
        Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition, const TimeFrame &ts) = 0;
        virtual void Translate(const glm::vec3 &delta) = 0;

        virtual void OnWindowResize(uint32_t width, uint32_t height) = 0;

    public:
        // Camera move trough XYZ
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void MoveNear();
        void MoveFar();

        void OnUpdate(const TimeFrame &ts);

        void OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent);

        void OnMouseScrolled(const MouseScrolledEvent &event);
        void OnMousePressed(const MouseButtonPressedEvent &event);
        void OnMouseReleased(const MouseButtonReleasedEvent &event);
        void OnMouseMoved(const MouseMovedEvent &event);

        void OnWindowResize(const WindowResizeEvent &event);
    protected:
        float m_TranslationSpeed;
        float m_RotationSpeed;
    private:
        glm::vec3 m_OldMousePosition, m_NewMousePosition;
        bool m_LeftMouseButtonPressed, m_MiddleMouseButtonPressed, m_Rotate, m_Pan;

        glm::vec3 m_TranslationVec;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////