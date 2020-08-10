//
// Created by christian on 06/08/2020.
//

#pragma once

#include "stinkypch.h"

#include "renderer/IndexBuffer.h"
#include "renderer/RendererApi.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
    class Renderer {
    public:
        struct SceneNode {
            Ref<VertexArray> vertexArray;
            Ref<Texture> texture;
            Ref<Shader> shader;
            glm::mat4 modelMatrix;
        };
        typedef std::vector<SceneNode> SceneNodes;
    public:
        Renderer(const Ref<RendererApi> &rendererApi);

        virtual ~Renderer();

        void BeginScene(glm::mat4 viewProjection);
        void EndScene();

        void Draw(const SceneNode& sceneNode) const;
    protected:
        Ref<RendererApi> m_RendererApi;
        glm::mat4 m_ViewProjection;
    };
/////////////////////////////////////////////////////////////////////////////////////////
}
