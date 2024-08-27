#include "core_pch.h"
#include "types.h"
#include "const_stuff.h"
#include "push_render.h"
#include <glad/glad.h>

u32 ren::vert_arr_id                  = 0;
u32 ren::vert_buf_id                  = 0;
s32 ren::num_vertices                 = 0;
s32 ren::current_vertex_per_primitive = 3;
Vertex *ren::vertex_list              = nullptr;

void ren::Init(Arena *arena)
{
    vertex_list = PushArray(arena, GLOB_STATE::MAX_VERTICES_PER_DRAW, Vertex);

    glGenVertexArrays(1, &vert_arr_id);
    glBindVertexArray(vert_arr_id);

    glCreateBuffers(1, &vert_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buf_id);

    glVertexAttribPointer(0, sizeof(Vertex::Position) / sizeof(f32), GL_FLOAT,
                          GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(f32), GL_FLOAT,
                          GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, color)));
    glEnableVertexAttribArray(1);
}

void ren::flush()
{
    if (!num_vertices)
    {
        return;
    }

    Vertex *v = vertex_list;

    glBindBuffer(GL_ARRAY_BUFFER, vert_buf_id);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, some_ibo);

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(v[0]) * num_vertices,
                 v,
                 GL_STREAM_DRAW);

    if (current_vertex_per_primitive == 3)
    {
        glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    num_vertices = 0;
}

void ren::quad(f32 x0, f32 y0, f32 x1, f32 y1, Color color)
{
    if (num_vertices > (GLOB_STATE::MAX_VERTICES_PER_DRAW - 6))
    {
        flush();
    }

    Vertex *v = vertex_list + num_vertices;

    put_vertex(&v[0], {x1, y0}, color);
    put_vertex(&v[1], {x0, y0}, color);
    put_vertex(&v[2], {x1, y1}, color);

    put_vertex(&v[3], {x1, y1}, color);
    put_vertex(&v[4], {x0, y0}, color);
    put_vertex(&v[5], {x0, y1}, color);

    num_vertices += 6;
}

void ren::put_vertex(Vertex *vert, V2 position, Color color)
{
    vert->Position = {position.x, position.y, 0};
    vert->color    = color;
}

// NOTE: Don't really need it right now but maybe in the future when I have to 
// have multiple vertex buffer.
void ren::end()
{
    ren::flush();
    // glDeleteVertexArrays(1, &vert_arr_id);
    // glBindVertexArray(0);
}
