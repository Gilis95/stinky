//
// Created by christian on 1/26/20.
//
#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

struct ShaderElements {
    std::string vertex;
    std::string fragment;
};

class Shader {
private:
    GLuint m_RendererID;
    std::string m_FilePath;
    std::unordered_map<GLenum, std::string> m_ShaderSources;
    std::unordered_map<std::string, int> m_UniformLocationsCache;
public:
    Shader(const std::string& filePath);

    ~Shader();

    void bind() const;

    void unbind() const;

    int getUniformLocation(const std::string& name);

    void setUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

    void setUniform1i(const std::string& name, int i);

private:
    void parseShaders(const std::string& source);

    static GLuint compileShader(GLenum type, const std::string& shaderCode);

    void createProgram();
};
