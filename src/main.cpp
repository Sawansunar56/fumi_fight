#include "win32_inc.h"
#include "arena.h"
#include "types.h"
#include "window.cpp"
#include "Shaders.cpp"
#include "texture.cpp"
#include "push_render.cpp"
#include "event_things.cpp"
#include "game_fil.cpp"

int main()
{
    // Memory
    // CLEAN: Maybe I can make a sub arena instead of having two separate
    // arenas.
    constexpr u32 totalMainMemory   = MB(5);
    constexpr u32 totalRenderMemory = MB(10);
    Arena *mainArena                = ArenaAlloc(totalMainMemory);
    Arena *renderArena              = ArenaAlloc(totalRenderMemory);
    event_list *EventList           = PushStruct(mainArena, event_list);

    constexpr s32 FPS       = 60;
    constexpr f32 frameTime = 1.0f / FPS;

    // window thingy
    constexpr u32 SCREEN_WIDTH  = 1280;
    constexpr u32 SCREEN_HEIGHT = 720;
    std::string title           = "Hello there";
    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);
    main_window.setArena(mainArena);
    main_window.setEventList(EventList);

    game_data game_state    = {};
    game_state.main_window  = &main_window;
    game_state.main_arena   = mainArena;
    game_state.render_arena = renderArena;
    game_state.EventList    = EventList;

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

    f32 dt        = 0.0f;
    auto frameEnd = std::chrono::steady_clock::now();
    while (main_window.ShouldClose())
    {
        auto frameStart = std::chrono::steady_clock::now();
        main_window.Update();
        update_and_render(&game_state, dt);
        frameEnd = std::chrono::steady_clock::now();

        std::chrono::duration<f32> elapsed = frameEnd - frameStart;

        dt = elapsed.count();
    }
    ArenaRelease(mainArena);
    ArenaRelease(renderArena);
    return 0;
}
