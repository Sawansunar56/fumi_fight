#include "win32_inc.h"
#include "arena.h"
#include "types.h"
#include "base_str.cpp"
#include "window.cpp"
#include "Shaders.cpp"
#include "texture.cpp"
#include "push_render.cpp"
#include "event_things.cpp"
#include "game_fil.cpp"
#include <base_str.h>

int main()
{
  // Memory
  // CLEAN: Maybe I can make a sub arena instead of having two separate
  // arenas.
  constexpr u32 totalMainMemory   = MB(20);
  constexpr u32 totalRenderMemory = MB(10);
  constexpr s32 FPS               = 60;
  constexpr f32 frameTime         = 1.0f / FPS;
  constexpr u32 SCREEN_WIDTH      = 1280;
  constexpr u32 SCREEN_HEIGHT     = 720;

  Arena *mainArena     = ArenaAlloc(totalMainMemory);
  Arena *renderArena   = ArenaAlloc(totalRenderMemory);
  Arena *permaStrArena = ArenaAlloc(MB(10));

  // window thingy
  std::string title = "Hello there";
  Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);
  main_window.setArena(mainArena);

  game_data game_state      = {};
  game_state.main_window    = &main_window;
  game_state.main_arena     = mainArena;
  game_state.render_arena   = renderArena;
  game_state.permastr_arena = permaStrArena;

  auto previousTime = std::chrono::steady_clock::now();

  // while (main_window.ShouldClose())
  // {
  //     main_window.Update();
  //     auto frameStart = std::chrono::steady_clock::now();
  //
  //     auto currentTime = std::chrono::steady_clock::now();
  //     std::chrono::duration<f32> elapsed = currentTime - previousTime;
  //     f32 dt = elapsed.count();
  //     previousTime = currentTime;
  //
  //     update_and_render(&game_state, dt);
  //
  //     auto frameEnd = std::chrono::steady_clock::now();
  //     std::chrono::duration<f32> frameDuration = frameEnd - frameStart;
  //
  //     if (frameDuration.count() < frameTime)
  //     {
  //         std::this_thread::sleep_for(
  //             std::chrono::duration<f32>(frameTime -
  //             frameDuration.count()));
  //     }
  // }

  f32 dt                  = 0.0f;
  auto frameEnd           = std::chrono::steady_clock::now();
  Arena *scratchForEvents = ArenaAlloc(MB(2));
  u64 loop_count          = 0;

  Str8 something = make_str8((char *)"power");
  Str8 hello     = make_str8_from_s32(mainArena, 120021);
  Str8 hellox    = make_str8_from_s32(mainArena, 1201);
  Str8 helloy    = make_str8_from_s32(mainArena, 1736121);

  print_str8(something);
  println_str8(hello);
  println_str8(hellox);
  println_str8(helloy);

  while (main_window.ShouldClose())
  {
    temp_arena scratch = temp_begin(scratchForEvents);
    auto frameStart    = std::chrono::steady_clock::now();

    event_list EventList = {};
    main_window.Update(scratch.arena, &EventList);

    update_and_render(&game_state, &EventList, dt);
    frameEnd = std::chrono::steady_clock::now();

    std::chrono::duration<f32> elapsed = frameEnd - frameStart;

    dt = elapsed.count();
    temp_end(scratch);
    loop_count += 1;
  }
  ArenaRelease(permaStrArena);
  ArenaRelease(mainArena);
  ArenaRelease(renderArena);
  return 0;
}
