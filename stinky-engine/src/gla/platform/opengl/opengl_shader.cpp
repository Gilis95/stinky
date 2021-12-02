//
// Created by christian on 1/26/20.
//

#include <Tracy.hpp>
#include <fstream>
#include <glad/glad.h>
#include <glm/ext.hpp>

#include "core/stinky_macros.h"
#include "gla/platform/opengl/opengl_shader.h"
#include "stinkypch.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] static GLenum ShaderTypeFromString(const std::string &type) {
  if (type == "vertex") {
    return GL_VERTEX_SHADER;
  }
  if (type == "fragment" || type == "pixel") {
    return GL_FRAGMENT_SHADER;
  } else {
    STINKY_LOG_ERROR_AND_BREAK("Unknown shader type!");
    return 0;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] static std::string readFile(const std::string &filepath) {
  ZoneScopedN("ShaderFileRead") std::string result;
  std::ifstream in(filepath, std::ios::in | std::ios::binary);
  AssertReturnUnless(in, result);

  in.seekg(0, std::ios::end);
  size_t size = in.tellg();

  AssertReturnIf(size == -1, result);
  result.resize(size);
  in.seekg(0, std::ios::beg);
  in.read(&result[0], size);
  in.close();

  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
opengl_shader::opengl_shader(asset_metadata &&_asset_metadata)
    : m_RendererID(0), _M_asset_metadata(std::forward<asset_metadata>(_asset_metadata)){}

/////////////////////////////////////////////////////////////////////////////////////////
opengl_shader::~opengl_shader() { glDeleteProgram(m_RendererID); }

/////////////////////////////////////////////////////////////////////////////////////////
int opengl_shader::get_uniform_location(const std::string &name) {
  if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end()) {
    return m_UniformLocationsCache[name];
  }

  const int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
  m_UniformLocationsCache[name] = uniformLocation;

  return uniformLocation;
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::bind() const { glUseProgram(m_RendererID); }

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::unbind() const { glUseProgram(0); }

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::set_integer(const std::string &name, int i) {
  glUniform1i(get_uniform_location(name), i);
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::set_float4(const std::string &name, glm::vec4 vector) {
  glUniform4f(get_uniform_location(name), vector.x, vector.y, vector.z,
              vector.w);
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::set_mat4(const std::string &name, glm::mat4 matrix) {
  glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::load() {
  parse_shaders(readFile(_M_asset_metadata.asset_path));
  create_program();
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::parse_shaders(const std::string &source) {
  ZoneScopedN("ShaderParse") const char *typeToken = "#type";
  size_t typeTokenLength = strlen(typeToken);
  size_t pos =
      source.find(typeToken, 0); // Start of shader type declaration line

  while (pos != std::string::npos) {
    size_t eol = source.find_first_of(
        "\r\n", pos); // End of shader type declaration line
    // Syntax error
    AssertReturnIf(eol == std::string::npos);
    size_t begin = pos + typeTokenLength +
                   1; // Start of shader type name (after "#type " keyword)
    std::string shaderTypeStr = source.substr(begin, eol - begin);
    GLenum shaderTypeEnum = ShaderTypeFromString(shaderTypeStr);
    // Invalid shader type specified
    AssertReturnUnless(shaderTypeEnum);

    // Start of shader code after shader type declaration line
    size_t nextLinePos = source.find_first_not_of("\r\n", eol);

    // Syntax error
    AssertReturnIf(nextLinePos == std::string::npos);
    pos = source.find(
        typeToken, nextLinePos); // Start of next shader type declaration line

    m_ShaderSources[shaderTypeEnum] =
        (pos == std::string::npos)
            ? source.substr(nextLinePos)
            : source.substr(nextLinePos, pos - nextLinePos);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void opengl_shader::create_program() {
  ZoneScopedN("ShaderBind") m_RendererID = glCreateProgram();
  std::array<GLenum, 2> glShaderIDs{};
  int glShaderIDIndex = 0;

  for (auto &kv : m_ShaderSources) {
    GLuint shaderId = compile_shader(kv.first, kv.second);
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
    GLchar *log;
    log = (GLchar *)alloca(maxLength * sizeof(GLchar));

    glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, log);

    // We don't need the program anymore.
    glDeleteProgram(m_RendererID);

    for (auto id : glShaderIDs)
      glDeleteShader(id);

    STINKY_ERROR("{0}", log);
    STINKY_LOG_ERROR_AND_BREAK("Shader link failure!");
    return;
  }

  for (auto &id : glShaderIDs) {
    glDetachShader(m_RendererID, id);
    glDeleteShader(id);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
GLuint opengl_shader::compile_shader(GLenum type,
                                     const std::string &shaderCode) {
  ZoneScopedN("ShaderCompile") unsigned int shaderId = glCreateShader(type);
  const char *shaderCStr = shaderCode.c_str();

  glShaderSource(shaderId, 1, &shaderCStr, nullptr);
  glCompileShader(shaderId);

  int compileResult;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);

  if (compileResult == GL_FALSE) {
    int length;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

    char *log;
    log = (char *)alloca(length * sizeof(char));

    glGetShaderInfoLog(shaderId, length, &length, log);
    glDeleteShader(shaderId);

    STINKY_ERROR("{0}", log);
    STINKY_LOG_ERROR_AND_BREAK("Shader compilation failure!");

    return 0;
  }

  return shaderId;
}

} // namespace stinky