#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include <cstdio>

Window::Window(u32 width, u32 height, std::string title):
    m_Height{height}, m_Width{width}, m_Title{title}
{
    if(!Init()) {
        printf("couldn't init");
    }
}

Window::~Window()
{
    glfwTerminate();
}

b32 Window::Init()
{
    if(!glfwInit())
    {
        printf("[LOG_ERROR]: failed to initialize glfw");
        return false;
    }

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

    if(!m_Window) {
        printf("failed to init window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to init glad");
        return false;
    }

    return true;
}
