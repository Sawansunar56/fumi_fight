#include "types.h"
#include "push_render.h"
#include "window.h"
#include "texture.h"
#include "log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

// Colors specified here
constexpr v4 WHITE      = {1.0f, 1.0f, 1.0f, 1.0f};
constexpr v4 RED        = {1.0f, 0.0f, 0.0f, 1.0f};
constexpr v4 BLUE       = {0.0f, 0.0f, 1.0f, 1.0f};
constexpr v4 GREEN      = {0.0f, 1.0f, 0.0f, 1.0f};
constexpr v4 BLACK      = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr v4 CYAN       = {0.0f, 1.0f, 1.0f, 1.0f};
constexpr v4 YELLOW    =  {1.0f, 1.0f, 0.0f, 1.0f};
constexpr v4 PURPLE     = {1.0f, 0.0f, 1.0f, 1.0f};
constexpr v4 TEAL       = {0.0f, 0.502f, 0.502f, 1.0f};
constexpr v4 VIOLET     = {(128.0f / 255.0f), 0.0f, 1.0f, 1.0f};
constexpr v4 CRIMSON   = {0.863f, 0.078f, 0.235f, 1.0f};
constexpr v4 ROYAL_BLUE = {0.255f, 0.412f, 0.882f, 1.0f};

struct Entity
{
    u64 Id;

    v3 position;
    v3 velocity;
    v3 acceleration;

    Texture2D *entity_texture;
};

struct world_data
{
    f32 world_friction;
};

struct game_data
{
    Arena *main_arena;
    Arena *render_arena;

    Entity Player;

    Window *main_window;
    Texture2D *textureList;
    u32 textureListCount;

    event_list *EventList;

    b8 isInitialized;
    world_data *World;
};

// NOTE: THINK ABOUT HANDLING THIS. Probably I need a global hash for texture
// use.
enum TEXT_NAME_
{
    TEXT_NAME_USELESS,
    TEXT_NAME_SOMETHING,
    TEXT_NAME_PLAYER
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

void updateEntityMovement(world_data *World, Entity *entity, f32 dt)
{
    entity->velocity.x += entity->acceleration.x * dt;
    entity->velocity.x -= entity->velocity.x * World->world_friction * dt;
    if (abs(entity->velocity.x) < 0.01)
    {
        entity->velocity.x = 0.0f;
    }
    entity->position.x += entity->velocity.x * dt;
    LOG_INFO("%f what is dt %f\n", entity->velocity.x, dt);
}

global_var f32 timeCount = 0;

// TODO: Now you have everything in place. Just start making the damn game with
// the aseprite art. Gotta learn to make things bro.
internals void update_and_render(game_data *game_state, f32 dt)
{
    Arena *mainArena   = game_state->main_arena;
    Arena *renderArena = game_state->render_arena;

    if (!game_state->isInitialized)
    {
        constexpr u32 MAX_CAP_TEXTURES = 50;
        game_state->textureListCount   = 0;
        game_state->textureList =
            PushArray(mainArena, MAX_CAP_TEXTURES, Texture2D);

        game_state->World = PushStruct(mainArena, world_data);

        // Texture loadint should be in here
        Texture2D *textures = game_state->textureList;
        textures[TEXT_NAME_USELESS].loadTexture("./textures/grad_circle.png");
        textures[TEXT_NAME_SOMETHING].loadTexture("./textures/something.png");

        // NOTE: Maybe there should be a specifier to know if a texture is an
        // atlas or not and then have appropriate data related to it.
        textures[TEXT_NAME_PLAYER].loadTexture(
            "./textures/character_sheet/char_blue_1.png");

        Assert(game_state->textureListCount < MAX_CAP_TEXTURES,
               "maximum texture count reached, expand capacity");

        // opengl renderer init
        ren::Init(renderArena);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // GLint maxTextureSize;
        // glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
        // printf("Maximum texture size: %d", maxTextureSize);
        // GLint maxTextureLayers;
        // glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxTextureLayers);
        // printf("Maximum texture array size: %d", maxTextureLayers);
        // PLayer initialization

        game_state->Player.Id       = 0;
        game_state->Player.position = {10, 10, 0};
        game_state->Player.velocity = {};

        game_state->World->world_friction = 0.9f;
        game_state->isInitialized         = true;
    }
    v2 windowDim = game_state->main_window->GetWindowDimensions();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Entity *Player = &game_state->Player;

    f32 accelerationFactor = 100.0f;
    for (event_node *node = game_state->EventList->first; node != 0;
         node             = node->next)
    {
        if (node->v.Type == ET_PRESS)
        {
            if (node->v.keycode == GLFW_KEY_A)
            {
                Player->acceleration.x = -accelerationFactor;
                pop_events(game_state->EventList, node);
            }
            if (node->v.keycode == GLFW_KEY_D)
            {
                Player->acceleration.x = accelerationFactor;
                pop_events(game_state->EventList, node);
            }
        }
        else if (node->v.Type == ET_RELEASE)
        {
            if (node->v.keycode == GLFW_KEY_A)
            {
                Player->acceleration.x = 0.0f;
                pop_events(game_state->EventList, node);
            }
            if (node->v.keycode == GLFW_KEY_D)
            {
                Player->acceleration.x = 0.0f;
                pop_events(game_state->EventList, node);
            }
        }
    }

    updateEntityMovement(game_state->World, &game_state->Player, dt);

    Texture2D *textures = game_state->textureList;
    ren::begin();
    ren::quad({100, 100}, {200, 200}, TEAL);
    ren::end();

    ren::begin_texture_mode();
    ren::quad_texture({0, 0},
                      {windowDim.x, windowDim.y},
                      WHITE,
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      &textures[TEXT_NAME_USELESS]);
    ren::quad_texture({200, 200},
                      {100, 100},
                      WHITE,
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      &textures[TEXT_NAME_USELESS]);

    i32 atlasHeight = 616;
    i32 atlasWidth  = 448;
    i32 tileSize    = 56;

    s32 totalHorizontalTileCount = 6;
    s32 value                    = (s32)timeCount % totalHorizontalTileCount;
    s32 tileNum                  = value * tileSize;

    v4 uv = {};
    uv.x  = (f32)tileNum / atlasWidth;
    uv.y  = (f32)(3 * tileSize) / atlasHeight;
    uv.z  = uv.x + ((f32)tileSize / atlasWidth);
    uv.w  = uv.y + ((f32)tileSize / atlasHeight);

    ren::quad_texture(game_state->Player.position,
                      {100, 100},
                      {1.0f, 1.0f, 1.0f, 1.0f},
                      uv,
                      &textures[TEXT_NAME_PLAYER]);
    ren::end_texture_mode();
    timeCount += 0.03f;
    if (timeCount > 16)
        timeCount = 0;
}
