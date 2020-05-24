//
// Created by christian on 1/26/20.
//
#pragma once

#include <string>
#include <map>

struct ShaderElements {
    std::string vertex;
    std::string fragment;
};

class Shader {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::map<std::string, int> uniformLocationsCache;
public:
    Shader(std::string filePath);

    ~Shader();

    void bind() const;

    void unbind() const;

    int getUniformLocation(const std::string &name) const;

    void setUniform4f(const std::string &name, float f0, float f1, float f2, float f3);

    void setUniform1i(const std::string &name, int i);

private:
    ShaderElements parseShaders(const std::string &filePath);

    unsigned int compileShader(unsigned int type, std::string &shaderCode);


    unsigned int createProgram(ShaderElements &&shaders);
};
