#include "types.h"
#include "push_render.h"
#include "window.h"
#include "texture.h"
#include <glad/glad.h>

struct game_data
{
    Arena *main_arena;
    Arena *render_arena;

    Window *main_window;
    Texture2D *textureList;
    u32 textureListCount;

    b8 isInitialized;
};

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

        Assert(game_state->textureListCount < MAX_CAP_TEXTURES,
               "maximum texture count reached, expand capacity");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        game_state->isInitialized = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Texture2D *textures = game_state->textureList;
    ren::begin();
    ren::quad({100, 100}, {200, 200}, {0.23f, 0.54f, 0.233f, 1.0f});
    ren::end();

    ren::begin_texture_mode();
    // min, max, texture coords
    ren::quad_texture({200, 200},
                      {100, 100},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      textures);
    ren::quad_texture({50, 500},
                      {50, 50},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      textures + 1);
    ren::end_texture_mode();
}
