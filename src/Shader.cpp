//
// Created by christian on 1/26/20.
//

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Shader.h"
#include "../include/Renderer.h"


Shader::Shader(std::string filePath) : m_FilePath(filePath) {
    m_RendererID = createProgram(parseShaders(filePath));
}

Shader::~Shader() {
    unbind();
    GLCall(glDeleteProgram(m_RendererID));
}


int Shader::getUniformLocation(const std::string &name) const {
    auto element = uniformLocationsCache.find(name);
    if (element != uniformLocationsCache.end()) {
        return element->second;
    }
    GLCall(int uniformLocation = glGetUniformLocation(m_RendererID, "u_Color"));

    return uniformLocation;
}

void Shader::bind() const {
    GLCall(glUseProgram(m_RendererID))
}

void Shader::unbind() const {
    GLCall(glUseProgram(0))
}


ShaderElements Shader::parseShaders(const std::string &filePath) {
    std::fstream shaderFileStream(filePath);

    std::string line;
    //element 0->vertexShader,1->fragmentShader
    std::stringstream shaderStrings[2];
    std::stringstream *currentShader = shaderStrings;

    while (getline(shaderFileStream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                currentShader = shaderStrings;
            } else {
                currentShader = shaderStrings + 1;
            }
        } else {
            (*currentShader) << line << '\n';
        }
    }

    return {shaderStrings[0].str(), shaderStrings[1].str()};
}

unsigned int Shader::createProgram(ShaderElements &&shaders) {
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, shaders.vertex);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, shaders.fragment);

    unsigned int programId = glCreateProgram();

    GLCall(glAttachShader(programId, vertexShaderId));
    GLCall(glAttachShader(programId, fragmentShaderId));

    GLCall(glLinkProgram(programId));
    GLCall(glValidateProgram(programId));

    GLCall(glDeleteShader(vertexShaderId));
    GLCall(glDeleteShader(fragmentShaderId));

    return programId;
}

unsigned int Shader::compileShader(unsigned int type, std::string &shaderCode) {
    unsigned int shaderId = glCreateShader(type);
    const char *shaderCStr = shaderCode.c_str();

    glShaderSource(shaderId, 1, &shaderCStr, nullptr);
    glCompileShader(shaderId);

    int compileResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);

    if (compileResult == GL_FALSE) {
        int length;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

        char *log;
        log = (char *) alloca(length * sizeof(char));

        glGetShaderInfoLog(shaderId, length, &length, log);
        std::cout << log << std::endl;
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

void Shader::setUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
    GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}
void Shader::setUniform1i(const std::string &name, int i) {
    GLCall(glUniform1i(getUniformLocation(name), i));
}

