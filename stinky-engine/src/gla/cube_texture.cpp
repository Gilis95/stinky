//
// Created by christian on 19/10/2020.
//

#include "gla/cube_texture.h"

#include <Tracy.hpp>
#include <stb_image.h>
#include <string>
#include <utility>

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
cube_texture::cube_texture(std::string path) : _M_path(std::move(path)) {
  LoadFromSingleFile();
}

/////////////////////////////////////////////////////////////////////////////////////////
void cube_texture::LoadFromSingleFile() {
  ZoneScopedN("CubeTextureFileRead") int srcWidth, srcHeight, channelsCount;

  byte *cubeTextureData[6];

  byte *data =
      stbi_load(_M_path.c_str(), &srcWidth, &srcHeight, &channelsCount, 0);

  // Colour channels contained into image.
  uint32_t stride = channelsCount;
  uint32_t face = 0;

  if (channelsCount == 4) {
    _M_input_format = InputImageFormat::RGBA;
  } else if (channelsCount == 3) {
    _M_input_format = InputImageFormat::RGB;
  }

  /**
   * --------------------------------------
   * |        |   Top  |        |        |
   * --------------------------------------
   * |  Left  |  Front |  Right |  Back  |
   * --------------------------------------
   * |        | Bottom |        |        |
   * --------------------------------------
   */

  // Viewing picture above we can see picture width consists of 4 pictures and
  // picture height consists of 3 pictures. To receive individual picture sizes
  // we should divide whole picture width by 4 and picture height by 3
  _M_face_width = srcWidth / 4;
  _M_face_height = srcHeight / 3;

  for (uint32_t cy = 0; cy < 3; cy++) {
    for (uint32_t cx = 0; cx < 4; cx++) {
      if (cy == 0 || cy == 2) {
        if (cx != 1) {
          continue;
        }
      }

      cubeTextureData[face] = new byte[_M_face_width * _M_face_height * stride];

      // fill individual cube face
      for (uint32_t y = 0; y < _M_face_height; y++) {
        uint32_t offset = y;

        unsigned yp = cy * _M_face_height + offset;
        for (unsigned x = 0; x < _M_face_width; x++) {
          offset = x;
          uint xp = cx * _M_face_width + offset;
          cubeTextureData[face][(x + y * _M_face_width) * stride + 0] =
              data[(xp + yp * srcWidth) * stride + 0];
          cubeTextureData[face][(x + y * _M_face_width) * stride + 1] =
              data[(xp + yp * srcWidth) * stride + 1];
          cubeTextureData[face][(x + y * _M_face_width) * stride + 2] =
              data[(xp + yp * srcWidth) * stride + 2];
          if (stride >= 4)
            cubeTextureData[face][(x + y * _M_face_width) * stride + 3] =
                data[(xp + yp * srcWidth) * stride + 3];
        }
      }
      face++;
    }
  }

  stbi_image_free(data);
  _M_top = cubeTextureData[0];
  _M_left = cubeTextureData[1];
  _M_front = cubeTextureData[2];
  _M_right = cubeTextureData[3];
  _M_back = cubeTextureData[4];
  _M_bottom = cubeTextureData[5];
}

/////////////////////////////////////////////////////////////////////////////////////////
void cube_texture::set_data(void *data) {
  // TODO:: implement
}

} // namespace stinky