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

    ~PerspectiveCameraController();


    //Camera Rotation
    virtual void Rotate(const Timestep &ts) = 0;
    virtual void Translate(const Timestep &ts) = 0;

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
        glm::vec2 m_OldMousePosition{1.0f, 1.0f};
        glm::vec2 m_NewMousePosition{1.0f, 1.0f};
        bool m_MousePressed = false;
        bool m_Rotate = false;

        glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
    private:
        std::unordered_map<KeyCode, std::function<void()>> m_CameraMoveFunctions;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////