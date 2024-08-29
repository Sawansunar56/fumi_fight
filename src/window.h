#pragma once
#include "types.h"
#include <string>

class GLFWwindow;

class Window
{
  public:
    Window(u32, u32, std::string title);
    ~Window();
    b32 Init();
    b32 ShouldClose() const;
    void Update() const;
    inline GLFWwindow *GetNativeWindow() { return m_Window; }
    inline void StopRunning() { m_running = false; }

  private:
    GLFWwindow *m_Window;
    u32 m_Height, m_Width;
    std::string m_Title;
    b32 m_running;
};
