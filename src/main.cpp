#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "types.h"
#include <cstdio>

int main()
{
    constexpr i32 SCREEN_HEIGHT = 720;
    constexpr i32 SCREEN_WIDTH = 1280;
    constexpr char title[] = "hello there";

    GLFWwindow* window;
    if(!glfwInit())
    {
        printf("[LOG_ERROR]: failed to initialize glfw");
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, nullptr, nullptr);

    if(!window) {
        printf("failed to init window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to init glad");
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
