//
// Created by christian on 05/11/2020.
//
#include <ecs/Entity.h>
#include <ecs/MaterialComponent.h>
#include <ecs/MeshComponents.h>
#include <ecs/ProgramComponent.h>
#include <ecs/TagComponent.h>
#include <ecs/TransformComponent.h>
#include "gla/GraphicLayerAbstractionFactory.h"
#include <glm/glm.hpp>
#include <scene/Scene.h>
#include "SaveManager.h"

namespace stinky::hoatzin {

    namespace {
        constexpr unsigned CUBE_VERTICES_COUNT = 32;
        glm::vec4 cubeVertices[8] = {
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

        constexpr unsigned int CUBE_INDICES_COUNT = 36;

        uint32_t cubeIndices[CUBE_INDICES_COUNT] = {
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

        glm::vec4 quadVertices[4] = {
                {-1.0f, -1.0f, 1.0, 1.0f}, //0
                {1.0f,  -1.0f, 1.0, 1.0f}, //1
                {1.0f,  1.0f,  1.0, 1.0f}, //2
                {-1.0f, 1.0f,  1.0, 1.0f}, //3
        };

        uint32_t quadIndices[6] = {
                // front side
                0, 1, 3, 1, 2, 3
        };
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    SaveManager::SaveManager(GraphicLayerAbstractionFactory *glaFactory, Scene &scene) : m_GLAFactory(glaFactory),
                                                                                         m_Scene(scene) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    void SaveManager::SaveSceneToFile(std::string path) {
        //TODO:: Fill in implementation
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void SaveManager::LoadSceneFromFile(std::string path) {
        auto entity = m_Scene.CreateEntity();
        entity.AddComponent<MeshComponent>(16, quadVertices, 6, quadIndices);
        entity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(2.0f, 2.0f, 2.0f),
                                                glm::vec3(0.0f, 0.0f, 0.0f));
        entity.AddComponent<ProgramComponent>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/skybox.glsl"));
        entity.AddComponent<MaterialComponent>(m_GLAFactory->CreateCubeTexture(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/skybox.png"));
        entity.AddComponent<TagComponent>("Skybox");

        auto entity1 = m_Scene.CreateEntity();
        entity1.AddComponent<MeshComponent>(CUBE_VERTICES_COUNT, cubeVertices, CUBE_INDICES_COUNT, cubeIndices);
        entity1.AddComponent<TransformComponent>(glm::vec3(0.8f, 0.0f, -2.0f), glm::vec3(0.5f, 0.5f, 0.5f),
                                                 glm::vec3(0.0f, 0.0f, 0.0f));
        entity1.AddComponent<ProgramComponent>(m_GLAFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/basic.shader"));
        entity1.AddComponent<MaterialComponent>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        entity1.AddComponent<TagComponent>("Cube");
    }
}