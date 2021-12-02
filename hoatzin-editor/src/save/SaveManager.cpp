//
// Created by christian on 05/11/2020.
//
#include "SaveManager.h"
#include <asset/entity/stinky/asset_metadata.h>
#include <ecs/entity.h>
#include <ecs/material_component.h>
#include <ecs/mesh_components.h>
#include <ecs/program_component.h>
#include <ecs/tag_component.h>
#include <ecs/transform_component.h>
#include <gla/graphic_layer_abstraction_factory.h>
#include <gla/index_buffer.h>
#include <gla/shader.h>
#include <gla/vertex_array.h>
#include <gla/vertex_buffer.h>
#include <glm/glm.hpp>
#include <scene/scene.h>

namespace stinky::hoatzin {

namespace {
constexpr unsigned CUBE_VERTICES_COUNT = 32;
glm::vec4 cubeVertices[8] = {
    // Front Quad
    {-1.0f, -1.0f, -1.0, 1.0f}, // 0
    {1.0f, -1.0f, -1.0, 1.0f},  // 1
    {1.0f, 1.0f, -1.0, 1.0f},   // 2
    {-1.0f, 1.0f, -1.0, 1.0f},  // 3

    // Back Quad
    {1.0f, -1.0f, 1.0, 1.0f},  // 4
    {-1.0f, -1.0f, 1.0, 1.0f}, // 5
    {-1.0f, 1.0f, 1.0, 1.0f},  // 6
    {1.0f, 1.0f, 1.0, 1.0f}    // 7
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
    0, 1, 2, 2, 3, 0};

glm::vec4 quadVertices[4] = {
    {-1.0f, -1.0f, 1.0, 1.0f}, // 0
    {1.0f, -1.0f, 1.0, 1.0f},  // 1
    {1.0f, 1.0f, 1.0, 1.0f},   // 2
    {-1.0f, 1.0f, 1.0, 1.0f},  // 3
};

uint32_t quadIndices[6] = {
    // front side
    0, 1, 3, 1, 2, 3};
} // namespace

/////////////////////////////////////////////////////////////////////////////////////////
SaveManager::SaveManager(graphic_layer_abstraction_factory *glaFactory,
                         scene &scene)
    : m_GLAFactory(glaFactory), m_Scene(scene) {}

/////////////////////////////////////////////////////////////////////////////////////////
void SaveManager::SaveSceneToFile(const std::string &path) {
  // TODO:: Fill in implementation
}

/////////////////////////////////////////////////////////////////////////////////////////
void SaveManager::LoadSceneFromFile(std::string path) {

  //        //create array buffer, containing shape positions and bind it
  const auto cubeVertexBuffer = m_GLAFactory->CreateVertexBuffer(
      cubeVertices, CUBE_VERTICES_COUNT * sizeof(float),
      {{component_type::FLOAT, param_type::VEC4, "position"}});
  // Create index buffer, that will define shape vertex positions
  const auto cubeIndexBuffer =
      m_GLAFactory->create_index_buffer(cubeIndices, CUBE_INDICES_COUNT);

  auto cubeVertexArray = m_GLAFactory->CreateVertexArray();
  // bind currently bound array buffer to first element of currently bound
  // vertex array
  cubeVertexArray->add_vertex_buffer(cubeVertexBuffer);
  cubeVertexArray->set_index_buffer(cubeIndexBuffer);

  asset_metadata shaderMeta("/home/christian/workspace/stinky/hoatzin-editor/"
                            "assets/shaders/basic.shader");
  auto shader = m_GLAFactory->CreateShader(std::move(shaderMeta));

  shader->load();

  auto entity1 = m_Scene.CreateEntity();
  entity1.AddComponent<mesh_component>(cubeVertexArray);
  entity1.AddComponent<transform_component>(glm::vec3(0.0f, 0.0f, -30.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f),
                                            glm::vec3(0.0f, 0.0f, 0.0f));
  entity1.AddComponent<program_component>(shader);
  entity1.AddComponent<material_component>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  entity1.AddComponent<tag_component>("Cube");

  auto entity2 = m_Scene.CreateEntity();
  entity2.AddComponent<mesh_component>(cubeVertexArray);
  entity2.AddComponent<transform_component>(glm::vec3(10.0f, 0.0f, -20.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f),
                                            glm::vec3(0.0f, 0.0f, 0.0f));
  entity2.AddComponent<program_component>(shader);
  entity2.AddComponent<material_component>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  entity2.AddComponent<tag_component>("Cube1");

  auto entity3 = m_Scene.CreateEntity();
  entity3.AddComponent<mesh_component>(cubeVertexArray);
  entity3.AddComponent<transform_component>(glm::vec3(0.0f, 0.0f, -10.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f),
                                            glm::vec3(0.0f, 0.0f, 0.0f));
  entity3.AddComponent<program_component>(shader);
  entity3.AddComponent<material_component>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  entity3.AddComponent<tag_component>("Cube2");

  auto entity4 = m_Scene.CreateEntity();
  entity4.AddComponent<mesh_component>(cubeVertexArray);
  entity4.AddComponent<transform_component>(glm::vec3(-10.0f, 0.0f, -20.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f),
                                            glm::vec3(0.0f, 0.0f, 0.0f));
  entity4.AddComponent<program_component>(shader);
  entity4.AddComponent<material_component>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  entity4.AddComponent<tag_component>("Cube3");

  // create array buffer, containing shape positions and bind it
  const auto quadVertexBuffer = m_GLAFactory->CreateVertexBuffer(
      quadVertices, 16 * sizeof(float),
      {{component_type::FLOAT, param_type::VEC4, "position"}});
  // Create index buffer, that will define shape vertex positions
  const auto quadIndexBuffer =
      m_GLAFactory->create_index_buffer(quadIndices, 6);

  auto quadVertexArray = m_GLAFactory->CreateVertexArray();
  // bind currently bound array buffer to first element of currently bound
  // vertex array
  quadVertexArray->add_vertex_buffer(quadVertexBuffer);
  quadVertexArray->set_index_buffer(quadIndexBuffer);

  asset_metadata skybox_shader_meta(
      "/home/christian/workspace/stinky/hoatzin-editor/assets/shaders/"
      "skybox.glsl");
  auto skyboxShader = m_GLAFactory->CreateShader(std::move(skybox_shader_meta));
  skyboxShader->load();

  auto entity = m_Scene.CreateEntity();
  entity.AddComponent<mesh_component>(quadVertexArray);
  entity.AddComponent<transform_component>(glm::vec3(1.0f), glm::vec3(1.0f),
                                           glm::vec3(1.0f));
  entity.AddComponent<program_component>(skyboxShader);
  entity.AddComponent<material_component>(
      m_GLAFactory->CreateCubeTexture(
          "/home/christian/workspace/stinky/hoatzin-editor/assets/textures/"
          "daylight.png"),
      false);
  entity.AddComponent<tag_component>("Skybox");
}
} // namespace stinky::hoatzin