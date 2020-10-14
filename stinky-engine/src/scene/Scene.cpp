//
// Created by christian on 05/10/2020.
//

#include "scene/Scene.h"

#include <entt/entt.hpp>

#include "camera/Camera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/MeshComponents.h"
#include "ecs/TransformationComponents.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    Scene::Scene(const GraphicLayerAbstractionFactory *rendererFactory) : m_Renderer(
            CreateScope<Renderer>(rendererFactory)) {

    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Entity Scene::CreateCubeEntity() {
        Entity result(m_Registry);
        static constexpr unsigned VERTICES_COUNT = 32;
        static glm::vec4 vertices[8] = {
                //Front Quad
                {-1.0f, -1.0f, -1.0, 1.0f}, //0
                {1.0f,  -1.0f, -1.0, 1.0f}, //1
                {1.0f,  1.0f,  -1.0, 1.0f}, //2
                {-1.0f, 1.0f,  -1.0, 1.0f}, //3

                // Back Quad
                {1.0f,  -1.0f, 1.0,  1.0f}, //4
                {-1.0f, -1.0f, 1.0,  1.0f}, //5
                {-1.0f, 1.0f,  1.0,  1.0f}, //6
                {1.0f,  1.0f,  1.0,  1.0f} //7
        };

        static constexpr unsigned int INDICES_COUNT = 36;

        static unsigned indices[INDICES_COUNT] = {
                // front side
                0, 1, 3, 1, 2, 3,

                // right side
                1, 4, 2, 4, 6, 2,

                // back side
                4, 5, 7, 5, 6, 7,

                // left side
                0, 5, 3, 5, 6, 3,

                // down side
                3, 2, 6, 2, 7, 6,

                // upper side
                0, 1, 2, 2, 3, 0
        };
        result.AddComponent<MeshVertexComponent>(VERTICES_COUNT, vertices);
        result.AddComponent<MeshIndexComponent>(INDICES_COUNT, indices);

        return result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Entity Scene::CreateCameraEntity() {
        return Entity(m_Registry);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Scene::OnUpdate() {
        auto camerasView = m_Registry
                .view<CameraComponent>();


        Camera *camera;

        for (auto cameraView:  camerasView) {
            auto &tmpCameraRef = camerasView.get<CameraComponent>(cameraView);
            ContinueUnless(tmpCameraRef.m_IsPrimary)
            camera = tmpCameraRef.m_Camera;
        }

        m_Renderer->Clear();
        auto meshesGroup = m_Registry.group<MeshVertexComponent, MeshIndexComponent, TranslateComponent, ScaleComponent>();
        m_Renderer->BeginScene(camera->GetViewProjectionMatrix());

        for (auto mesh : meshesGroup) {
            m_Renderer->Draw({
                                     meshesGroup.get<MeshVertexComponent>(mesh),
                                     meshesGroup.get<MeshIndexComponent>(mesh),
                                     meshesGroup.get<TranslateComponent>(mesh),
                                     meshesGroup.get<ScaleComponent>(mesh)
                             });
        }
    }
}