#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <camera/fps_camera.h>
#include <ecs/camera_component.h>
#include <gla/frame_buffer.h>
#include <gla/graphic_layer_abstraction_factory.h>
#include <gla/vertex_buffer.h>
#include <GLFW/glfw3.h>
#include <scene/scene.h>
#include <Tracy.hpp>

#include "event/event_controller.h"
#include "panels/Workspace.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/EntityInspectorPanel.h"
#include "panels/ScenePanel.h"

#include "HoatzinEditorLayer.h"


namespace stinky::hoatzin {

    /////////////////////////////////////////////////////////////////////////////////////////
    HoatzinEditorLayer::HoatzinEditorLayer(graphic_layer_abstraction_factory *glaFactory,
                                           fps_camera *camera,
                                           event_controller &eventController,
                                           uint32_t width, uint32_t height)
            : layer("Hoatzin HoatzinEditorEditor Layer"), m_GLAFactory(glaFactory),
              m_Scene(glaFactory),
              m_SceneManager(glaFactory, m_Scene),
              m_FrameBuffer(glaFactory->create_frame_buffer({width, height})),
              m_Camera(camera),
              m_EventController(eventController) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnAttach() {
        entity entity(m_Scene.CreateEntity());
        entity.AddComponent<camera_component>(m_Camera, true);

        m_Camera->set_position(glm::vec3(0.0f, 0.0f, 0.0f));

        m_SceneManager.LoadSceneFromFile("default");
        m_EventController.RegisterEventHandler<window_close_event>(
                [this](const event &event) {
                    OnClose();
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnUpdate(const time_frame &ts) {
        {
            ZoneScopedN("FrameBufferSceneRender")
            const auto &frameBufferSpecification = m_FrameBuffer->get_specification();
            if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
                !(m_ViewportSize.x == frameBufferSpecification.width &&
                  m_ViewportSize.y == frameBufferSpecification.height)) {
                m_FrameBuffer->window_resize(m_ViewportSize.x, m_ViewportSize.y);
                m_Camera->on_window_resize(m_ViewportSize.x, m_ViewportSize.y);
            }
            /** Render current scene */
            m_FrameBuffer->bind();

            m_Camera->on_update(ts);
            m_Scene.Render();

            m_FrameBuffer->unbind();
            /** Render current scene */
        }

        {
            ZoneScopedN("ImGuiRender")
            /** Render editor */
            ImGuiBegin();
            ImGuiRender();
            ImGuiEnd();
            /** Render editor */
        }
    }

    void HoatzinEditorLayer::OnClose() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        m_FrameBuffer.reset();
        m_Scene.OnClose();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::ImGuiBegin() {
        ZoneScopedN("ImGuiFrameCreation")
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::ImGuiRender() {
        Workspace::Begin();

        SceneHierarchyPanel::Render(m_Scene, m_SelectedEntt);

        EntityInspectorPanel::Render(m_SelectedEntt);

        uint64_t textureID = m_FrameBuffer->get_color_attachment_renderer_id();
        ScenePanel::Render(textureID, m_ViewportSize);

        Workspace::End();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::ImGuiEnd() {
        ZoneScopedN("ImGuiDraw")
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(1024, 720);

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
