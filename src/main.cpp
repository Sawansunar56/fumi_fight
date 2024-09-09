#include "win32_inc.h"
#include "stb_image.h"
#include "arena.h"
#include "types.h"
#include "window.cpp"
#include "Shaders.cpp"
#include "push_render.cpp"

int main()
{
    // Memory
    // CLEAN: Maybe I can make a sub arena instead of having two separate arenas.
    constexpr u32 totalMainMemory   = Megabytes(5);
    constexpr u32 totalRenderMemory = Megabytes(5);
    Arena *mainArena                = ArenaAlloc(totalMainMemory);
    Arena *renderArena              = ArenaAlloc(totalRenderMemory);

    // window thingy
    constexpr u32 SCREEN_WIDTH  = 1280;
    constexpr u32 SCREEN_HEIGHT = 720;
    std::string title           = "Hello there";
    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);

    // opengl renderer init
    ren::Init(renderArena);

    // TODO: Do some texture loading bro

    while (main_window.ShouldClose())
    {
        main_window.Update();

        // CLEAN: This shouldn't be in here. Put this somewhere else.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ren::begin();
        ren::quad({100, 100}, {200, 200}, {0.23f, 0.54f, 0.233f, 1.0f});
        ren::end();

        ren::begin_texture_mode();
        // min, max, texture coords
        ren::quad_texture({}, {}, {});
        ren::end_texture_mode();
    }
    ArenaRelease(mainArena);
    return 0;
}
