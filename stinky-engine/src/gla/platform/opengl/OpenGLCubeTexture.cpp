//
// Created by christian on 19/10/2020.
//

#include "gla/platform/opengl/OpenGLCubeTexture.h"

#include <utility>
#include <glad/glad.h>
#include <stb_image_write.h>

namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    OpenGLCubeTexture::OpenGLCubeTexture(std::string path) : cube_texture(std::move(path)) {
        glGenTextures(1, &_M_renderer_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _M_renderer_id);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        int inputImageFormat = GL_RGB + static_cast<int>(_M_input_format);
        int dataFormat = GL_RGB + static_cast<int>(_M_input_format);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_right);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_left);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_top);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_bottom);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_front);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, dataFormat, _M_face_width, _M_face_height, 0, inputImageFormat,
                     GL_UNSIGNED_BYTE, _M_back);

        delete[] _M_right;
        delete[] _M_left;
        delete[] _M_top;
        delete[] _M_bottom;
        delete[] _M_front;
        delete[] _M_back;

        _M_right = nullptr;
        _M_left = nullptr;
        _M_top = nullptr;
        _M_bottom = nullptr;
        _M_front = nullptr;
        _M_back = nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLCubeTexture::bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _M_renderer_id);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OpenGLCubeTexture::unbind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}