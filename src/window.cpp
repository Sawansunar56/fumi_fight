#include <arena.h>
#include <event_things.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include <cstdio>

Window::Window(u32 width, u32 height, std::string title)
    : m_Height{height}, m_Width{width}, m_Title{title}, m_running{true}
{
 if (!Init())
 {
  printf("couldn't initialize glfw window");
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

 glfwSetKeyCallback(
     m_Window,
     [](GLFWwindow *window, s32 key, s32 scancode, s32 action, s32 mods) {
      Window *win_data =
          static_cast<Window *>(glfwGetWindowUserPointer(window));
      if (action == GLFW_PRESS)
      {
       if (key == GLFW_KEY_ESCAPE)
       {
        win_data->StopRunning();
       }
       else
       {
        event Event   = {};
        Event.keycode = key;
        Event.Type    = ET_PRESS;

        push_events(win_data->scratch, win_data->EventList, &Event);
       }
      }

      if (action == GLFW_RELEASE)
      {
       event Event   = {};
       Event.keycode = key;
       Event.Type    = ET_RELEASE;

       push_events(win_data->scratch, win_data->EventList, &Event);
      }
     });

 glfwSetMouseButtonCallback(
     m_Window,
     [](GLFWwindow *window, s32 button, s32 action, s32 mods) {});

 glfwSetFramebufferSizeCallback(m_Window,
                                [](GLFWwindow *window, s32 width, s32 height) {
                                 glViewport(0, 0, width, height);
                                });

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

void Window::Update(Arena *scratch, event_list* EventList)
{
 this->scratch = scratch;
 this->EventList = EventList;

 glfwPollEvents();
 glfwSwapBuffers(m_Window);
}
