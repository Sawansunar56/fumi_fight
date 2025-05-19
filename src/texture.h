#pragma once
#include "types.h"
#include "my_maths.h"
#include <string>

class Texture2D
{
  public:
    Texture2D();
    Texture2D(const std::string &filename);
    ~Texture2D();
    void Bind(u32) const;
    void loadTexture(const std::string &filename);
    inline v2i32 getDim() { return v2i32{m_width, m_height}; };
    u32 m_Id;

  private:
    s32 m_width, m_height, m_DataFormat, m_InternalFormat;
    b8 isInitialized;
};

function void TextureInit();
function u32 loadTexture(const char *filename);
