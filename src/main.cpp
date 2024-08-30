#include "win32_inc.h"
#include "arena.h"
#include "types.h"
#include "my_maths.h"
#include "window.cpp"
#include "Shaders.cpp"
#include "push_render.cpp"

int main()
{
    // Memory
    constexpr u32 totalMainMemory = Megabytes(2);
    Arena *mainArena              = ArenaAlloc(totalMainMemory);

    // window thingy
    constexpr u32 SCREEN_WIDTH  = 1280;
    constexpr u32 SCREEN_HEIGHT = 720;
    std::string title           = "Hello there";

    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);

    // Shader Init
    Shader *basic_shader = new Shader("./shaders/basic_shader.vert",
                                      "./shaders/basic_shader.frag");

    // opengl renderer init
    ren::Init(mainArena, 2000);
    ren::add_shader(basic_shader, SHADER_BASIC);

    while (main_window.ShouldClose())
    {
        main_window.Update();

        ren::begin();
        ren::quad(500, 100, 200, 200, {0.9f, 0.8f, 0.4f, 0.1f});
        ren::end();
    }
    ArenaRelease(mainArena);
    delete basic_shader;
    return 0;
}
