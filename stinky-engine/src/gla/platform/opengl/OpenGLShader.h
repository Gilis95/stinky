//
// Created by christian on 1/26/20.
//
#pragma once

#include <unordered_map>

#include "gla/shader.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    class OpenGLShader : public shader {
    public:
        explicit OpenGLShader(const std::string &filePath);

        ~OpenGLShader() override;

        void bind() const override;

        void unbind() const override;

        void set_integer(const std::string &name, int i) override;

        void set_float4(const std::string &name, glm::vec4 vector) override;

        void set_mat4(const std::string &name, glm::mat4 matrix) override;

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