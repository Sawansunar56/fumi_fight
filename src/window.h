#pragma once
#include "types.h"
#include "my_maths.h"
#include "event_things.h"
#include <string>

class GLFWwindow;

class Window
{
  public:
    Window(u32, u32, std::string title);
    ~Window();
    b32 Init();
    b32 ShouldClose() const;
    void Update(Arena *scratch, event_list* EventList);
    inline v2 GetWindowDimensions() const 
    {
        return {static_cast<f32>(m_Width), static_cast<f32>(m_Height)};
    }
    inline GLFWwindow *GetNativeWindow() { return m_Window; }
    inline void StopRunning() { m_running = false; }
    inline void setEventList(event_list *list) { EventList = list; }
    inline void setArena(Arena *arena) { mainArena = arena; };

  private:
    GLFWwindow *m_Window;
    u32 m_Height, m_Width;
    std::string m_Title;
    b32 m_running;
    event_list *EventList;
    Arena *mainArena;
    Arena *scratch;
};
