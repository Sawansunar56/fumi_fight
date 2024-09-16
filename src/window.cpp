#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include <cstdio>

void keyHandler(GLFWwindow *window, s32 key, s32 scancode, s32 action, s32 mods)
{
    Window *win_data = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        win_data->StopRunning();
    }
}

void mouseHandler(GLFWwindow *window, s32 button, s32 action, s32 mods) 
{
    
}

void framebuffer_size_callback(GLFWwindow *window, s32 width, s32 height)
{
    glViewport(0, 0, width, height);
}

Window::Window(u32 width, u32 height, std::string title)
    : m_Height{height}, m_Width{width}, m_Title{title}, m_running{true}
{
    if (!Init())
    {
        printf("couldn't init");
    }
}

Window::~Window() { glfwTerminate(); }

b32 Window::Init()
{
    if (!glfwInit())
    {
        printf("[LOG_ERROR]: failed to initialize glfw");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE);

    m_Window =
        glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

    if (!m_Window)
    {
        printf("failed to init window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetKeyCallback(m_Window, keyHandler);
    glfwSetMouseButtonCallback(m_Window, mouseHandler);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    glfwSetWindowUserPointer(m_Window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to init glad");
        return false;
    }

    return true;
}

b32 Window::ShouldClose() const
{
    return !glfwWindowShouldClose(m_Window) && m_running;
}

void Window::Update() const
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}
