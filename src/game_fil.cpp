#include "types.h"
#include "push_render.h"
#include "window.h"
#include "texture.h"
#include "log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// function declarations

// fill this function
void updateAnimations();

enum PlayerAnimations_
{
    PlayerAnimations_Idle,
    PlayerAnimations_Attack,
    PlayerAnimations_Run,
    PlayerAnimations_Jump,
    PlayerAnimations_Fall,
    PlayerAnimations_Hit,
    PlayerAnimations_Perish,
    PlayerAnimations_DeathIdle,
    PlayerAnimations_EnergyGenerate,
    PlayerAnimations_Crouch,
    PlayerAnimations_Dodge,
    PlayerAnimations_FINAL
};

// NOTE: I might need a higher structure which shifts between flipbooks.
struct SpriteFlipbook
{
    Texture2D *spriteAtlas;
    v4 *uv;
    u32 spriteCount;
    f32 frame_duration;
    u32 current_frame;
    f32 animation_time;
};

struct EntityAnimations
{
    SpriteFlipbook *animations;
    u32 animationCount;
};

// There has been a discrepency. An object shouldn't be a static and a ridid
// body at the same time. but this system allows it, I gotta change or redefine
// some things.
enum EntityFeatureFlags_
{
    ENTITY_NONE        = 0,
    ENTITY_RENDERABLE  = (1 << 0),
    ENTITY_STATIC_BODY = (1 << 1),
    ENTITY_RIGID_BODY  = (1 << 2),
};
typedef u32 EntityFeatureFlags;

struct Entity
{
    u64 Id;

    v3 position;
    v3 velocity;
    v3 acceleration;

    EntityFeatureFlags componentFlags;

    Texture2D *SpriteAtlas;
    EntityAnimations entityAnimation;
};

struct world_data
{
    f32 world_friction;
};

constexpr u16 MAX_ENTITY_COUNT = 10000;

struct EntityList
{
    Entity *entities;
    u32 cur;
    u32 cap;
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
    EntityList entityList;

    b8 isInitialized;
    world_data *World;
};

// NOTE: THINK ABOUT HANDLING THIS. Probably I need a global hash for texture
// use.
enum TEXTURE_LABEL
{
    TEXTURE_TEST,
    TEXTURE_SOMETHING,
    TEXTURE_PLAYER,
    TEXTURE_BACKGROUND, // there might be multiple levels so why only a single
                        // background?
};

EntityAnimations loadPlayerTextureToFlipbooks(Arena *arena, Entity *Player)
{
    // TODO: Need to load all animations and make a flipbook
    // FIX: This should be somewhere else and way more modular
    constexpr s32 atlasHeight = 616;
    constexpr s32 atlasWidth  = 448;
    constexpr s32 tileSize    = 56;

    EntityAnimations playerAnimations = {};
    playerAnimations.animationCount   = PlayerAnimations_FINAL;
    playerAnimations.animations =
        PushArray(arena, playerAnimations.animationCount, SpriteFlipbook);

    for (i32 currentAnimation = 0; currentAnimation < PlayerAnimations_FINAL;
         ++currentAnimation)
    {
        SpriteFlipbook *currentFlipbook =
            &playerAnimations.animations[currentAnimation];
        currentFlipbook->spriteAtlas    = Player->SpriteAtlas;
        currentFlipbook->frame_duration = 0.1f;

        switch (currentAnimation)
        {
        case PlayerAnimations_Idle: {
            currentFlipbook->spriteCount = 6;
        }
        break;
        case PlayerAnimations_Attack:
        case PlayerAnimations_Run:
        case PlayerAnimations_Jump:
        case PlayerAnimations_Fall:
        case PlayerAnimations_Perish:
        case PlayerAnimations_EnergyGenerate: {
            currentFlipbook->spriteCount = 8;
        }
        break;
        case PlayerAnimations_Hit:
        case PlayerAnimations_DeathIdle: {
            currentFlipbook->spriteCount = 4;
        }
        break;
        case PlayerAnimations_Crouch:
        case PlayerAnimations_Dodge: {
            currentFlipbook->spriteCount = 3;
        }
        break;
        default: {
            currentFlipbook->spriteCount = 0;
        }
        break;
        }

        // You have to initialize the amount of sprites you have for that
        // animation
        currentFlipbook->uv =
            PushArray(arena, currentFlipbook->spriteCount, v4);
        for (i32 currentSprite = 0;
             currentSprite < currentFlipbook->spriteCount;
             ++currentSprite)
        {
            s32 tileNum                          = currentSprite * tileSize;
            currentFlipbook->uv[currentSprite].x = (f32)tileNum / atlasWidth;
            currentFlipbook->uv[currentSprite].y =
                (f32)(currentAnimation * tileSize) / atlasHeight;
            currentFlipbook->uv[currentSprite].z =
                currentFlipbook->uv[currentSprite].x +
                ((f32)tileSize / atlasWidth);
            currentFlipbook->uv[currentSprite].w =
                currentFlipbook->uv[currentSprite].y +
                ((f32)tileSize / atlasHeight);
        }
    }
    return playerAnimations;
}

internals void updateEntityMovement(world_data *World, Entity *entity, f32 dt)
{
    entity->velocity.x += entity->acceleration.x * dt;
    entity->velocity.x -= entity->velocity.x * World->world_friction * dt;
    if (abs(entity->velocity.x) < 0.01)
    {
        entity->velocity.x = 0.0f;
    }
    entity->position.x += entity->velocity.x * dt;
    // LOG_INFO("%f what is dt %f\n", entity->velocity.x, dt);
}

internals Entity *AddEntity(const EntityList &entity_list)
{
    Entity *Result = &entity_list.entities[entity_list.cur];
    return Result;
}

// NOTE: This is a risky game I feel. Can't really remove it willy-nilly because
// position is mighty important. Maybe some sort of block clear?
internals void RemoveEntity(EntityList *entity_list, u32 count)
{
    u32 old_pos = entity_list->cur;
    u32 new_pos = entity_list->cur - count;
    if (new_pos < 0)
    {
        LOG_INFO("[ERROR] You are trying to remove more entities than what is "
                 "inside");
        new_pos = old_pos;
    }
    entity_list->cur = new_pos;
}

// TODO: gravity system
internals void gravitySystem() {}

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
        textures[TEXTURE_TEST].loadTexture("./textures/grad_circle.png");
        textures[TEXTURE_SOMETHING].loadTexture("./textures/something.png");

        // NOTE: Maybe there should be a specifier to know if a texture is an
        // atlas or not and then have appropriate data related to it.
        textures[TEXTURE_PLAYER].loadTexture(
            "./textures/character_sheet/char_blue_1.png");

        textures[TEXTURE_BACKGROUND].loadTexture(
            "./textures/gradient-background.jpg");

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
        game_state->Player.componentFlags |= ENTITY_RENDERABLE;
        game_state->Player.SpriteAtlas = &textures[TEXTURE_PLAYER];
        game_state->Player.entityAnimation =
            loadPlayerTextureToFlipbooks(mainArena, &game_state->Player);

        game_state->World->world_friction = 0.9f;

        game_state->entityList.cur = 0;
        game_state->entityList.cap = MAX_ENTITY_COUNT;
        game_state->entityList.entities =
            PushArray(mainArena, game_state->entityList.cap, Entity);

        game_state->isInitialized = true;

        EntityList *entityList = &game_state->entityList;

        // Maybe add an enemy
    }
    v2 windowDim = game_state->main_window->GetWindowDimensions();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Entity *Player = &game_state->Player;

    f32 playerAccFactor              = 100.0f;
    local_persist b8 playerDirection = true;
    for (event_node *node = game_state->EventList->first; node != 0;
         node             = node->next)
    {
        if (node->v.Type == ET_PRESS)
        {
            if (node->v.keycode == GLFW_KEY_A)
            {
                Player->acceleration.x = -playerAccFactor;
                pop_events(game_state->EventList, node);
            }
            if (node->v.keycode == GLFW_KEY_D)
            {
                Player->acceleration.x = playerAccFactor;
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

    b32 runPress    = false;
    b32 attackPress = false;
    updateEntityMovement(game_state->World, &game_state->Player, dt);

    // FIX: This should be placed somewhere with other animation state
    // transition.
    if (abs(game_state->Player.velocity.x) > 20.0f)
    {
        runPress = true;
        if(game_state->Player.velocity.x > 0.0f)
        {
            playerDirection = true;
        }
        else {
            playerDirection = false;
        }
    }
    gravitySystem();

    // RENDERING PART

    Texture2D *textures = game_state->textureList;

    ren::begin_texture_mode();
    ren::quad_texture({0, 0},
                      {windowDim.x, windowDim.y},
                      CLR_WHITE,
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      &textures[TEXTURE_BACKGROUND]);
    ren::quad_texture({200, 200},
                      {100, 100},
                      CLR_WHITE,
                      {0.0f, 0.0f, 1.0f, 1.0f},
                      &textures[TEXTURE_TEST]);

    // SpriteFlipbook *currentPlayerAnimation = &playerIdle;
    SpriteFlipbook *currentAnimation =
        &Player->entityAnimation.animations[PlayerAnimations_Idle];

    if (runPress)
    {
        currentAnimation =
            &Player->entityAnimation.animations[PlayerAnimations_Run];
    }
    v4 currentFrameUV = {};
    Texture2D *currentFrameTexture = currentAnimation->spriteAtlas;
    if (playerDirection)
    {
        currentFrameUV = currentAnimation->uv[currentAnimation->current_frame];
    }
    else
    {
        currentFrameUV.x = currentAnimation->uv[currentAnimation->current_frame].z;
        currentFrameUV.y = currentAnimation->uv[currentAnimation->current_frame].y;
        currentFrameUV.z = currentAnimation->uv[currentAnimation->current_frame].x;
        currentFrameUV.w = currentAnimation->uv[currentAnimation->current_frame].w;
    }
    ren::quad_texture(game_state->Player.position,
                      {100, 100},
                      CLR_WHITE,
                      currentFrameUV,
                      currentFrameTexture);
    ren::end_texture_mode();

    currentAnimation->animation_time += dt;
    if (currentAnimation->animation_time >= currentAnimation->frame_duration)
    {
        currentAnimation->current_frame =
            (currentAnimation->current_frame + 1) %
            currentAnimation->spriteCount;

        currentAnimation->animation_time = 0.0f;
    }
    ren::begin();
    ren::quad({100, 100}, {200, 200}, CLR_EMERALD_GREEN);
    ren::end();
}

void updateAnimations() {}
