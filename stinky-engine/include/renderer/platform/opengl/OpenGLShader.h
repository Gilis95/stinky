//
// Created by christian on 1/26/20.
//
#pragma once

#include <glad/glad.h>

#include "renderer/Shader.h"
#include "stinkypch.h"

namespace stinky {
    struct ShaderElements {
        std::string vertex;
        std::string fragment;
    };

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filePath);

        ~OpenGLShader();

        void bind() const override;

        void unbind() const override;

        void setInteger(const std::string& name, int i) override;

        void setFloat4(const std::string& name, float f0, float f1, float f2, float f3) override;

    private:
        GLuint m_RendererID;
        std::unordered_map<GLenum, std::string> m_ShaderSources;
        std::unordered_map<std::string, int> m_UniformLocationsCache;

        void createProgram();

        void parseShaders(const std::string& source);

        int getUniformLocation(const std::string& name);

        static GLuint compileShader(GLenum type, const std::string& shaderCode);

    };
}