#include "types.h"
#include "push_render.h"
#include "window.h"
#include "texture.h"
#include "log.h"
#include "base_str.h"
#include <arena.h>
#include <glad/glad.h>
#include <event_things.h>
#include <GLFW/glfw3.h>

#include <ren_types.h>
#include <source_location>

// defines
constexpr u16 MAX_ENTITY_COUNT = 10000;
constexpr f32 GRAVITY          = -9.8;

// globals
glob Arena *game_scratch   = {0};
glob Arena *permastr_arena = {0};

// function declarations

// WARN: This should be ordered exactly as how the entity are
// spawned in the initialization code.
enum EntityCreated
{
 // EC_PLAYER_CHAR,
 EC_ENEMY_ONE,
 EC_GROUND_ONE,
 EC_COUNT
};

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

enum PlayerStateKind
{
 PState_None = 0,
 PState_Attack,
 PState_Run,
};

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
 u32 count;
 u32 cap;
};

// There has been a discrepency. An object shouldn't be a static and a ridid
// body at the same time. but this system allows it, I gotta change or redefine
// some things.
typedef u32 EntityFeatureFlags;
enum EntityFeatureFlags_
{
 ENTITY_NONE         = 0,
 ENTITY_RENDERABLE   = (1 << 0),
 ENTITY_STATIC_BODY  = (1 << 1),
 ENTITY_RIGID_BODY   = (1 << 2),
 ENTITY_COLOR_BODY   = (1 << 3),
 ENTITY_TEXTURE_BODY = (1 << 4),
};

struct Entity
{
 Str8 Id;

 v4 color;

 v3 position;
 v3 size;
 v3 velocity;
 v3 acceleration;

 EntityAnimations entityAnimation;
 EntityFeatureFlags componentFlags;
};

struct Player : public Entity
{
 PlayerStateKind current_state;
 b32 isRight;
};

struct world_data
{
 f32 world_friction;
};

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
 Arena *permastr_arena;

 Player Player;

 Window *main_window;
 Texture2D *textureList;
 u32 textureListCount;

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
 TEXTURE_FROG_IDLE,
 TEXTURE_FROG_JUMP,
};

// TODO: Make this function more modular.
EntityAnimations loadPlayerTextureToFlipbooks(Arena *arena,
                                              Entity *Player,
                                              Texture2D *spriteAtlas)
{
 // TODO: Need to load all animations and make a flipbook
 // FIX: This should be somewhere else and way more modular

 // const s32 atlasHeight = 616;
 // const s32 atlasWidth  = 448;
 v2i32 textureDim       = spriteAtlas->getDim();
 const s32 atlasHeight  = textureDim.y;
 const s32 atlasWidth   = textureDim.x;
 constexpr s32 tileSize = 56;

 EntityAnimations playerAnimations = {};
 playerAnimations.count            = PlayerAnimations_FINAL;
 playerAnimations.animations =
     PushArray(arena, playerAnimations.count, SpriteFlipbook);

 for (i32 currentAnimation = 0; currentAnimation < PlayerAnimations_FINAL;
      ++currentAnimation)
 {
  SpriteFlipbook *currentFlipbook =
      &playerAnimations.animations[currentAnimation];
  currentFlipbook->spriteAtlas    = spriteAtlas;
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
  currentFlipbook->uv = PushArray(arena, currentFlipbook->spriteCount, v4);
  for (i32 currentSprite = 0; currentSprite < currentFlipbook->spriteCount;
       ++currentSprite)
  {
   s32 tileNum                          = currentSprite * tileSize;
   currentFlipbook->uv[currentSprite].x = (f32)tileNum / atlasWidth;
   currentFlipbook->uv[currentSprite].y =
       (f32)(currentAnimation * tileSize) / atlasHeight;
   currentFlipbook->uv[currentSprite].z =
       currentFlipbook->uv[currentSprite].x + ((f32)tileSize / atlasWidth);
   currentFlipbook->uv[currentSprite].w =
       currentFlipbook->uv[currentSprite].y + ((f32)tileSize / atlasHeight);
  }
 }
 return playerAnimations;
}

// TODO: Need to set a standard or make a better system.
EntityAnimations
loadTextureForFlipbooks(Arena *arena, Entity *entity, Texture2D *spriteAtlas)
{
 EntityAnimations Result = {};
 return Result;
}

function void updateEntityMovement(world_data *World, Entity *entity, f32 dt)
{
 entity->velocity.x += entity->acceleration.x * dt;
 entity->velocity.y += entity->acceleration.y * dt;

 entity->velocity.x -= entity->velocity.x * World->world_friction * dt;
 if (abs(entity->velocity.x) < 0.1)
 {
  entity->velocity.x = 0.0f;
 }
 entity->position.x += entity->velocity.x * dt;
 entity->position.y += entity->velocity.y * dt;
 // LOG_INFO("%f what is dt %f\n", entity->velocity.x, dt);
}

// FIX: This is not good I am having it so that entityID is always aligned to
// array index which is not very good.

// function Entity *GetEntity(EntityList *entity_list, u64 entityId)
// {
//   Assert((entityId >= 0) && (entityId < entity_list->cap),
//          "entity id outside bounds");
//   Entity *Result = &entity_list->entities[entityId];
//   return Result;
// }

function Entity *InsertEntity_(EntityList *entity_list, Str8 id)
{
 if (entity_list->cur >= entity_list->cap)
 {
  LOG_INFO("You have reached the maximum entity count");
  return nullptr;
 }

 Entity *Result = &entity_list->entities[entity_list->cur++];
 Result->Id     = id; // using an incremented id because 0 is set
                      // to player entity in the game state.
 return Result;
}

// NOTE: Id are closely packed and no null terminator are used for their id
// which run in a consequetive pattern.
function Str8 createEntityId(s32 x, s32 y)
{
 Str8 sec_one = make_str8_from_s32(game_scratch, x);
 Str8 sec_two = make_str8_from_s32(game_scratch, y);

 Str8 id = concate_str8(permastr_arena, sec_one, sec_two);
 return id;
}

function Str8 getEntityId(Entity *entity) { return entity->Id; }

function Entity *
AddEntity(EntityList *entity_list,
          s32 iteration                  = 0,
          const std::source_location loc = std::source_location::current())
{
 int num = loc.line();
 return InsertEntity_(entity_list, createEntityId(num, iteration));
}

// NOTE: This is a risky game I feel. Can't really remove it willy-nilly because
// position is mighty important. Maybe some sort of block clear?
// internals void RemoveEntity(EntityList *entity_list, u32 count)
// {
//     u32 old_pos = entity_list->cur;
//     u32 new_pos = entity_list->cur - count;
//     if (new_pos < 0)
//     {
//         LOG_INFO("[ERROR] You are trying to remove more entities than what is
//         "
//                  "inside");
//         new_pos = old_pos;
//     }
//     entity_list->cur = new_pos;
// }

// TODO: gravity system
function void gravitySystem(Player *player, f32 dt)
{
 player->velocity.y -= GRAVITY * dt;
}

// NOTE: Need to think about this. The collision handling and what not.
b8 isEntityColliding(Entity *entity, Entity *player)
{
 if ((player->position.x + player->size.x) > entity->position.x &&
     player->position.x < (entity->position.x + entity->size.x) &&
     (player->position.y + player->size.y) > entity->position.y &&
     player->position.y < (entity->position.y + entity->size.y))
 {
  return true;
 }
 return false;
}

function void collisionCheckSystem(EntityList *entity_list, Entity *player)
{
 for (i32 i = 0; i < entity_list->cur; i++)
 {
  Entity *cur_entity = entity_list->entities + i;
  if ((cur_entity->componentFlags & ENTITY_STATIC_BODY) &&
      isEntityColliding(cur_entity, player))
  {
   player->velocity = {0, 0, 0};
  }
 }
}

function void PlayerAnimate(Player *Player, f32 dt)
{
 SpriteFlipbook *currentAnimation =
     &Player->entityAnimation.animations[PlayerAnimations_Idle];

 // maybe make this a flag instead of a cluster of if else
 // if (runPress)
 switch (Player->current_state)
 {
 case PState_Run: {
  currentAnimation = &Player->entityAnimation.animations[PlayerAnimations_Run];
 }
 break;
 case PState_Attack: {
  currentAnimation =
      &Player->entityAnimation.animations[PlayerAnimations_Attack];
 }
 break;
 case PState_None:
 default: {
  currentAnimation = &Player->entityAnimation.animations[PlayerAnimations_Idle];
 }
 break;
 }

 v4 currentFrameUV              = {};
 Texture2D *currentFrameTexture = currentAnimation->spriteAtlas;

 // if (playerDirection)
 if (Player->isRight)
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

 ren::begin();
 ren::quad(Player->position, Player->size, CLR_BLUE);
 ren::end();
 ren::begin_texture_mode();
 ren::quad_texture(Player->position,
                   Player->size,
                   CLR_RED,
                   currentFrameUV,
                   currentFrameTexture);
 ren::end_texture_mode();

 currentAnimation->animation_time += dt;
 if (currentAnimation->animation_time >= currentAnimation->frame_duration)
 {
  currentAnimation->current_frame =
      (currentAnimation->current_frame + 1) % currentAnimation->spriteCount;

  currentAnimation->animation_time = 0.0f;
 }
}

function void HandleInput(event_list *EventList, Player *player)
{
 f32 playerAccFactor = 100.0f;
 for (event_node *node = EventList->first; node != 0; node = node->next)
 {
  b8 event_handled = false;
  if (node->v.Type == ET_PRESS)
  {
   switch (node->v.keycode)
   {
   case GLFW_KEY_A: {
    player->acceleration.x = -playerAccFactor;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_D: {
    player->acceleration.x = playerAccFactor;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_S: {
    player->acceleration.y = playerAccFactor;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_W: {
    player->acceleration.y = -playerAccFactor;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_K: {
    player->current_state = PState_Attack;
    event_handled         = true;
   }
   break;
   }
  }
  else if (node->v.Type == ET_RELEASE)
  {
   switch (node->v.keycode)
   {
   case GLFW_KEY_A:
   case GLFW_KEY_D: {
    player->acceleration.x = 0.0f;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_S:
   case GLFW_KEY_W: {
    player->acceleration.y = 0.0f;
    event_handled          = true;
   }
   break;
   case GLFW_KEY_K: {
    player->current_state = PState_None;
    event_handled         = true;
   }
   break;
   }
  }

  if (event_handled)
  {
   pop_events(EventList, node);
  }
 }
}

function void InitGame(game_data *game_state)
{
 Arena *mainArena   = game_state->main_arena;
 Arena *renderArena = game_state->render_arena;
 permastr_arena     = game_state->permastr_arena;
 game_scratch       = ArenaAlloc(MB(10));

 constexpr u32 MAX_CAP_TEXTURES = 50;
 game_state->textureListCount   = 0;
 game_state->textureList = PushArray(mainArena, MAX_CAP_TEXTURES, Texture2D);

 game_state->World = PushStruct(mainArena, world_data);

 // Texture loadint should be in here
 Texture2D *textures = game_state->textureList;
 textures[TEXTURE_TEST].loadTexture("./textures/grad_circle.png");
 textures[TEXTURE_SOMETHING].loadTexture("./textures/something.png");

 // NOTE: Maybe there should be a specifier to know if a texture is an
 // atlas or not and then have appropriate data related to it.
 textures[TEXTURE_PLAYER].loadTexture(
     "./textures/character_sheet/char_blue_1.png");

 textures[TEXTURE_FROG_IDLE].loadTexture(
     "./textures/character_sheet/frog-idle.png");
 textures[TEXTURE_FROG_JUMP].loadTexture(
     "./textures/character_sheet/frog-jump.png");

 textures[TEXTURE_BACKGROUND].loadTexture("./textures/gradient-background.jpg");

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

 Player *player         = &game_state->Player;
 player->Id             = createEntityId(32, 0);
 player->position       = {600, 10, 0};
 player->size           = {100, 100, 0};
 player->velocity       = {};
 player->componentFlags = ENTITY_RENDERABLE;
 player->current_state  = PState_None;
 player->isRight        = true;
 player->entityAnimation =
     loadPlayerTextureToFlipbooks(mainArena,
                                  &game_state->Player,
                                  &textures[TEXTURE_PLAYER]);

 game_state->World->world_friction = 0.9f;

 game_state->entityList.cur = 0;
 game_state->entityList.cap = MAX_ENTITY_COUNT;
 game_state->entityList.entities =
     PushArray(mainArena, game_state->entityList.cap, Entity);

 game_state->isInitialized = true;

 // NOTE: Id are closely packed and no null terminator are used for their id
 // which run in a consequetive pattern.
 EntityList *entityList    = &game_state->entityList;
 Entity *enemy_one         = AddEntity(entityList);
 enemy_one->position       = {200, 10, 0};
 enemy_one->size           = {100, 100, 0};
 enemy_one->velocity       = {0};
 enemy_one->componentFlags = ENTITY_COLOR_BODY;
 enemy_one->color          = CLR_ROYAL_BLUE;

 Entity *ground_one         = AddEntity(entityList);
 ground_one->position       = {600, 300, 0};
 ground_one->size           = {500, 100, 0};
 ground_one->velocity       = {0};
 ground_one->componentFlags = ENTITY_STATIC_BODY | ENTITY_COLOR_BODY;
 ground_one->color          = CLR_PURPLE;

 // Entity *level_ground         = AddEntity(entityList);
 // level_ground->position       = {0, 500, 0};
 // level_ground->size           = {800, 100, 0};
 // level_ground->velocity       = {0};
 // level_ground->componentFlags = ENTITY_STATIC_BODY;
}

// TODO: Now you have everything in place. Just start making the damn game with
// the aseprite art. Gotta learn to make things bro.
function void
update_and_render(game_data *game_state, event_list *EventList, f32 dt)
{
 temp_arena scratch = temp_begin(game_scratch);
 Arena *mainArena   = game_state->main_arena;
 Arena *renderArena = game_state->render_arena;

 EntityList *entityList = &game_state->entityList;
 v2 windowDim           = game_state->main_window->GetWindowDimensions();

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 Player *player = &game_state->Player;

 // Put these variables somewhere.
 b32 runPress              = false;
 b32 attackPress           = false;
 locals b8 playerDirection = true;

 HandleInput(EventList, player);
 updateEntityMovement(game_state->World, &game_state->Player, dt);

 // FIX: This should be placed somewhere with other animation state
 // transition.
 if (abs(game_state->Player.velocity.x) > 20.0f)
 {
  runPress              = true;
  player->current_state = PState_Run;
  if (game_state->Player.velocity.x > 0.0f)
  {
   player->isRight = true;
  }
  else
  {
   player->isRight = false;
  }
 }
 else
 {
  player->current_state = PState_None;
 }
 // gravitySystem(Player, dt);
 collisionCheckSystem(entityList, player);

 // RENDERING PART
 {
  Texture2D *textures = game_state->textureList;

  ren::begin_texture_mode();
  ren::quad_texture({0, 0},
                    {windowDim.x, windowDim.y},
                    CLR_WHITE,
                    {0.0f, 0.0f, 1.0f, 1.0f},
                    &textures[TEXTURE_BACKGROUND]);
  ren::end_texture_mode();
  ren::begin();
  for (s32 i = 0; i < entityList->cur; i++)
  {
   Entity *cur_entity = entityList->entities + i;

   if (cur_entity->componentFlags & ENTITY_COLOR_BODY)
   {
    ren::quad(cur_entity->position, cur_entity->size, cur_entity->color);
   }
  }
  ren::end();

  // ren::quad_texture({200, 200},
  //                   {100, 100},
  //                   CLR_WHITE,
  //                   {0.0f, 0.0f, 1.0f, 1.0f},
  //                   &textures[TEXTURE_TEST]);
 }
 // SpriteFlipbook *currentPlayerAnimation = &playerIdle;
 PlayerAnimate(player, dt);

 {
  // Entity *ground_one   = AddEntity(entityList);
  // ground_one->position = {600, 100, 0};
  // ground_one->size     = {400, 100, 0};
  //
  // ren::begin();
  // ren::quad(ground_one->position, ground_one->size, CLR_EMERALD_GREEN);
  // ren::end();
 }
 temp_end(scratch);
}
