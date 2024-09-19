#include "types.h"
#include "push_render.h"
#include "window.h"
#include "texture.h"
#include <glad/glad.h>
#include <vector>

struct game_data
{
    Arena *main_arena;
    Arena *render_arena;

    Window *main_window;
    Texture2D *textureList;
    u32 textureListCount;

    b8 isInitialized;
};

struct Frame
{
    f32 u, v, width, height;
};

std::vector<Frame>
loadFrames(s32 frameWidth, s32 frameHeight, s32 atlasWidth, s32 atlasHeight)
{
    std::vector<Frame> Result;

    for (i32 y = 0; y < atlasHeight; y += frameWidth)
    {
        for (i32 x = 0; x < atlasWidth; x += frameHeight)
        {
            Result.push_back({(f32)x / atlasWidth,
                              (f32)y / atlasHeight,
                              (f32)frameWidth / atlasWidth,
                              (f32)frameHeight / atlasHeight});
        }
    }

    return Result;
}

global_var f32 timeCount = 0;

// TODO: Now you have everything in place. Just start making the damn game with
// the aseprite art. Gotta learn to make things bro.
internals void update_and_render(game_data *game_state)
{
    Arena *mainArena   = game_state->main_arena;
    Arena *renderArena = game_state->render_arena;

    if (!game_state->isInitialized)
    {
        constexpr u32 MAX_CAP_TEXTURES = 50;
        game_state->textureListCount   = 0;
        game_state->textureList =
            PushArray(mainArena, MAX_CAP_TEXTURES, Texture2D);

        // opengl renderer init
        ren::Init(renderArena);

        // Texture loadint should be in here
        Texture2D *textures = game_state->textureList;
        textures->loadTexture("./textures/grad_circle.png");
        (textures + 1)->loadTexture("./textures/something.png");

        // NOTE: Maybe there should be a specifier to know if a texture is an
        // atlas or not and then have appropriate data related to it.
        (textures + 2)
            ->loadTexture("./textures/character_sheet/char_blue_1.png");

        Assert(game_state->textureListCount < MAX_CAP_TEXTURES,
               "maximum texture count reached, expand capacity");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        game_state->isInitialized = true;

        // GLint maxTextureSize;
        // glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        // printf("Maximum texture size: %d", maxTextureSize);
        // GLint maxTextureLayers;
        // glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxTextureLayers);
        // printf("Maximum texture array size: %d", maxTextureLayers);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Texture2D *textures = game_state->textureList;
    ren::begin();
    ren::quad({100, 100}, {200, 200}, {0.23f, 0.54f, 0.233f, 1.0f});
    ren::end();

    ren::begin_texture_mode();
    ren::quad_texture({200, 200},
                      {100, 100},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      textures);

    i32 atlasHeight = 616;
    i32 atlasWidth  = 448;
    i32 tileSize    = 56;

    s32 totalHorizontalTileCount = 6;
    s32 value                    = (s32)timeCount % totalHorizontalTileCount;
    s32 tileNum                  = value * tileSize;
    v4 uv                        = {};
    uv.x                         = (f32)tileNum / atlasWidth;
    uv.y                         = (f32)(2 * tileSize) / atlasHeight;
    uv.z                         = uv.x + ((f32)tileSize / atlasWidth);
    uv.w                         = uv.y + ((f32)tileSize / atlasHeight);
    ren::quad_texture({10, 10},
                      {100, 100},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      uv,
                      textures + 2);
    ren::end_texture_mode();
    timeCount += 0.03f;
    if (timeCount > 16)
        timeCount = 0;
}
