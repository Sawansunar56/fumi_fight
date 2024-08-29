#include "win32_inc.h"
#include "arena.h"
#include "types.h"
#include "my_maths.h"
#include "window.cpp"
#include "Shaders.cpp"
#include "push_render.cpp"

int main()
{
    constexpr u32 totalMainMemory = Megabytes(2);
    Arena *mainArena = ArenaAlloc(totalMainMemory);

    constexpr u32 SCREEN_WIDTH  = 1280;
    constexpr u32 SCREEN_HEIGHT = 720;
    std::string title           = "hello there";

    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);

    Shader basic_shader("./shaders/basic_shader.vert", "./shaders/basic_shader.frag");

    ren::Init(mainArena, 2000);

    GLFWwindow *window = main_window.GetNativeWindow();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);

        basic_shader.Bind();
        ren::begin();
        ren::quad(-0.5f, 0.5f, 0.5f, -0.5f, {0.9f, 0.8f, 0.4f, 0.1f});
        ren::end();
    }

    ArenaRelease(mainArena);
    return 0;
}
