//
// Created by christian on 1/26/20.
//


#include <glad/glad.h>
#include <fstream>

#include "StinkyMacros.h"
#include "renderer/platform/opengl/OpenGLShader.h"
#include "stinkypch.h"

namespace stinky {

    static GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        ASSERT(false, "Unknown shader type!");
        return 0;
    }

    static std::string readFile(const std::string& filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1) {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                in.close();
            }
            else {
                STINKY_ERROR("Could not read from file {0}", filepath);
            }
        }
        else {
            STINKY_ERROR("Could not open file {0}", filepath);
        }

        return result;
    }

    OpenGLShader::OpenGLShader(const std::string& filePath) {
        parseShaders(readFile(filePath));
        createProgram();
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }


    int OpenGLShader::getUniformLocation(const std::string& name) {
        if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end()) {
            return m_UniformLocationsCache[name];
        }

        const int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
        m_UniformLocationsCache[name] = uniformLocation;

        return uniformLocation;
    }

    void OpenGLShader::bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::unbind() const {
        glUseProgram(0);
    }


    void OpenGLShader::parseShaders(const std::string& source) {
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line

        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n",
                eol); //Start of shader code after shader type declaration line
            ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

            m_ShaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos)
                : source.substr(nextLinePos,
                    pos - nextLinePos);
        }
    }

    void OpenGLShader::createProgram() {
        m_RendererID = glCreateProgram();
        std::array<GLenum, 2> glShaderIDs{};
        int glShaderIDIndex = 0;

        for (auto& kv : m_ShaderSources) {
            GLuint shaderId = compileShader(kv.first, kv.second);
            if (shaderId == 0) {
                break;
            }

            glAttachShader(m_RendererID, shaderId);
            glShaderIDs[glShaderIDIndex++] = shaderId;
        }

        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            GLchar* log;
            log = (GLchar*)alloca(maxLength * sizeof(GLchar));

            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, log);

            // We don't need the program anymore.
            glDeleteProgram(m_RendererID);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            STINKY_ERROR("{0}", log);
            ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto& id : glShaderIDs) {
            glDetachShader(m_RendererID, id);
            glDeleteShader(id);
        }
    }

    GLuint OpenGLShader::compileShader(GLenum type, const std::string& shaderCode) {
        unsigned int shaderId = glCreateShader(type);
        const char* shaderCStr = shaderCode.c_str();

        glShaderSource(shaderId, 1, &shaderCStr, nullptr);
        glCompileShader(shaderId);

        int compileResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);

        if (compileResult == GL_FALSE) {
            int length;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

            char* log;
            log = (char*)alloca(length * sizeof(char));

            glGetShaderInfoLog(shaderId, length, &length, log);
            glDeleteShader(shaderId);

            STINKY_ERROR("{0}", log);
            ASSERT(false, "Shader compilation failure!");

            return 0;
        }

        return shaderId;
    }


    void OpenGLShader::setInteger(const std::string& name, int i)
    {
        glUniform1i(getUniformLocation(name), i);
    }

    void OpenGLShader::setFloat4(const std::string& name, float f0, float f1, float f2, float f3) {
        glUniform4f(getUniformLocation(name), f0, f1, f2, f3);
    }
}