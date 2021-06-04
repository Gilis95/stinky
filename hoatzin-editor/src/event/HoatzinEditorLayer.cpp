#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <camera/FPSCamera.h>
#include <ecs/CameraComponent.h>
#include <gla/FrameBuffer.h>
#include <gla/GraphicLayerAbstractionFactory.h>
#include <gla/VertexBuffer.h>
#include <GLFW/glfw3.h>
#include <scene/Scene.h>
#include <Tracy.hpp>

#include "event/EventController.h"
#include "panels/Workspace.h"
#include "panels/SceneHierarchyPanel.h"
#include "panels/EntityInspectorPanel.h"
#include "panels/ScenePanel.h"

#include "HoatzinEditorLayer.h"


namespace stinky::hoatzin {

    /////////////////////////////////////////////////////////////////////////////////////////
    HoatzinEditorLayer::HoatzinEditorLayer(GraphicLayerAbstractionFactory *glaFactory,
                                           FPSCamera *camera,
                                           EventController &eventController,
                                           uint32_t width, uint32_t height)
            : Layer("Hoatzin HoatzinEditorEditor Layer"), m_GLAFactory(glaFactory),
              m_Scene(glaFactory),
              m_SceneManager(glaFactory, m_Scene),
              m_FrameBuffer(glaFactory->CreateFrameBuffer({width, height})),
              m_Camera(camera),
              m_EventController(eventController) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnAttach() {
        Entity entity(m_Scene.CreateEntity());
        entity.AddComponent<CameraComponent>(m_Camera, true);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        m_SceneManager.LoadSceneFromFile("default");
        m_EventController.RegisterEventHandler<WindowCloseEvent>(
                [this](const Event &event) {
                    OnClose();
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnUpdate(const TimeFrame &ts) {
        {
            ZoneScopedN("FrameBufferSceneRender")
            const auto &frameBufferSpecification = m_FrameBuffer->GetSpecification();
            if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
                !(m_ViewportSize.x == frameBufferSpecification.Width &&
                  m_ViewportSize.y == frameBufferSpecification.Height)) {
                m_FrameBuffer->WindowResize(m_ViewportSize.x, m_ViewportSize.y);
                m_Camera->OnWindowResize(m_ViewportSize.x, m_ViewportSize.y);
            }
            /** Render current scene */
            m_FrameBuffer->Bind();

            m_Camera->OnUpdate(ts);
            m_Scene.Render();

            m_FrameBuffer->Unbind();
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

        uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
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
