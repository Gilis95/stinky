//
// Created by christian on 19/10/2020.
//

#include "gla/CubeTexture.h"

#include <string>
#include <utility>
#include <stb_image.h>


namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    CubeTexture::CubeTexture(std::string path) : m_Path(std::move(path)) {
        LoadFromSingleFile();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void CubeTexture::LoadFromSingleFile() {
        int srcWidth, srcHeight, channelsCount;

        byte *cubeTextureData[6];

        byte *data = stbi_load(m_Path.c_str(), &srcWidth,
                               &srcHeight, &channelsCount, 0);

        // Colour channels contained into image.
        uint32_t stride = channelsCount;
        uint32_t face = 0;

        if (channelsCount == 4) {
            m_InputFormat = InputImageFormat::RGBA;
        } else if (channelsCount == 3) {
            m_InputFormat = InputImageFormat::RGB;
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
        // picture height consists of 3 pictures. To receive individual picture sizes we should divide whole
        // picture width by 4 and picture height by 3
        m_FaceWidth = srcWidth / 4;
        m_FaceHeight = srcHeight / 3;


        for (uint32_t cy = 0; cy < 3; cy++) {
            for (uint32_t cx = 0; cx < 4; cx++) {
                if (cy == 0 || cy == 2) {
                    if (cx != 1) {
                        continue;
                    }
                }

                cubeTextureData[face] = new byte[m_FaceWidth * m_FaceHeight * stride];

                // fill individual cube face
                for (uint32_t y = 0; y < m_FaceHeight; y++) {
                    uint32_t offset = y;

                    unsigned yp = cy * m_FaceHeight + offset;
                    for (unsigned x = 0; x < m_FaceWidth; x++) {
                        offset = x;
                        uint xp = cx * m_FaceWidth + offset;
                        cubeTextureData[face][(x + y * m_FaceWidth) * stride + 0] = data[(xp + yp * srcWidth) * stride +
                                                                                         0];
                        cubeTextureData[face][(x + y * m_FaceWidth) * stride + 1] = data[(xp + yp * srcWidth) * stride +
                                                                                         1];
                        cubeTextureData[face][(x + y * m_FaceWidth) * stride + 2] = data[(xp + yp * srcWidth) * stride +
                                                                                         2];
                        if (stride >= 4)
                            cubeTextureData[face][(x + y * m_FaceWidth) * stride + 3] = data[
                                    (xp + yp * srcWidth) * stride + 3];
                    }
                }
                face++;
            }
        }

        stbi_image_free(data);
        m_Top = cubeTextureData[0];
        m_Left = cubeTextureData[1];
        m_Front = cubeTextureData[2];
        m_Right = cubeTextureData[3];
        m_Back = cubeTextureData[4];
        m_Bottom = cubeTextureData[5];
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void CubeTexture::SetData(void *data) {
        // TODO:: implement
    }

}