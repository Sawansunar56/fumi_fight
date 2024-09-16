#pragma once
#include "types.h"
#include <string>

class Texture2D
{
  public:
    Texture2D();
    Texture2D(const std::string &filename);
    ~Texture2D();
    void Bind(u32) const;
    void loadTexture(const std::string &filename);
    u32 m_Id;

  private:
  private:
    s32 m_width, m_height, m_DataFormat, m_InternalFormat;
    b8 isInitialized;
};

internals void TextureInit();
internals u32 loadTexture(const char *filename);
