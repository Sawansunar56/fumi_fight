#include "texture.h"
#include <glad/glad.h>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "types.h"

Texture2D::Texture2D() : isInitialized(false) {}

Texture2D::Texture2D(const std::string &name) { loadTexture(name); }

void Texture2D::loadTexture(const std::string &filename)
{
    i32 width, height, channels;
    std::filesystem::path texturePath(filename);
    std::string something = std::filesystem::absolute(texturePath).string();

    // stbi_set_flip_vertically_on_load(true);

    u8 *data = stbi_load(something.c_str(), &width, &height, &channels, 0);
    Assert(data, "failed to load image!");

    m_width  = width;
    m_height = height;

    if (channels == 4)
    {
        m_DataFormat     = GL_RGBA;
        m_InternalFormat = GL_RGBA8;
    }
    else if (channels == 3)
    {
        m_DataFormat     = GL_RGB;
        m_InternalFormat = GL_RGB8;
    }

    u32 textureId;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glTextureStorage2D(textureId, 1, m_InternalFormat, m_width, m_height);

    glTexParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(textureId, 0, 0, 0,
                        m_width, m_height, m_DataFormat,
                        GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    isInitialized = true;
    m_Id          = textureId;
}

void Texture2D::Bind(u32 slot) const { glBindTextureUnit(slot, m_Id); }
Texture2D::~Texture2D() { glDeleteTextures(1, &m_Id); }
