#include "win32_inc.h"
#include "arena.h"
#include "types.h"
#include "window.cpp"
#include "Shaders.cpp"
#include "push_render.cpp"
#include "texture.cpp"
#include "game_fil.cpp"

int main()
{
    // Memory
    // CLEAN: Maybe I can make a sub arena instead of having two separate
    // arenas.
    constexpr u32 totalMainMemory   = Megabytes(5);
    constexpr u32 totalRenderMemory = Megabytes(5);
    Arena *mainArena                = ArenaAlloc(totalMainMemory);
    Arena *renderArena              = ArenaAlloc(totalRenderMemory);

    // window thingy
    constexpr u32 SCREEN_WIDTH  = 1280;
    constexpr u32 SCREEN_HEIGHT = 720;
    std::string title           = "Hello there";
    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);

    game_data game_state    = {};
    game_state.main_window  = &main_window;
    game_state.main_arena   = mainArena;
    game_state.render_arena = renderArena;

    while (main_window.ShouldClose())
    {
        main_window.Update();
        update_and_render(&game_state);
    }
    ArenaRelease(mainArena);
    ArenaRelease(renderArena);
    return 0;
}
