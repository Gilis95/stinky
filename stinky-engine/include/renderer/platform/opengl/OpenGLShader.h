//
// Created by christian on 1/26/20.
//
#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include "renderer/Shader.h"

namespace stinky {
    struct ShaderElements {
        std::string vertex;
        std::string fragment;
    };

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& filePath);

        ~OpenGLShader();

        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        void setInteger(const std::string& name, int i);

        void setFloat4(const std::string& name, float f0, float f1, float f2, float f3);

    private:
        GLuint m_RendererID;
        std::string m_FilePath;
        std::unordered_map<GLenum, std::string> m_ShaderSources;
        std::unordered_map<std::string, int> m_UniformLocationsCache;

        void createProgram();

        void parseShaders(const std::string& source);

        int getUniformLocation(const std::string& name);

        static GLuint compileShader(GLenum type, const std::string& shaderCode);

    };
}