#include "types.h"
#include "window.cpp"

int main()
{
    constexpr u32 SCREEN_HEIGHT = 720;
    constexpr u32 SCREEN_WIDTH  = 1280;
    std::string title           = "hello there";

    Window main_window(SCREEN_WIDTH, SCREEN_HEIGHT, title);

    GLFWwindow *window = main_window.GetNativeWindow();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
