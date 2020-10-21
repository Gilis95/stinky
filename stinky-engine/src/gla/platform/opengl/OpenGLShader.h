//
// Created by christian on 1/26/20.
//
#pragma once

#include "stinkypch.h"

#include "gla/Shader.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    struct ShaderElements {
        std::string vertex;
        std::string fragment;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &filePath);

        ~OpenGLShader();

        void Bind() const override;

        void Unbind() const override;

        void SetInteger(const std::string &name, int i) override;

        void SetFloat4(const std::string &name, glm::vec4 vector) override;

        void SetMat4(const std::string &name, glm::mat4 matrix) override;
    private:
        uint32_t m_RendererID;
        std::unordered_map<uint32_t, std::string> m_ShaderSources;
        std::unordered_map<std::string, int> m_UniformLocationsCache;

        void CreateProgram();

        void ParseShaders(const std::string &source);

        int GetUniformLocation(const std::string &name);

        static uint32_t CompileShader(uint32_t type, const std::string &shaderCode);

    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////