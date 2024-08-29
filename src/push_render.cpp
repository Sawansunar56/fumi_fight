#include "types.h"
#include "push_render.h"
#include <glad/glad.h>

void ren::Init_Im(Arena *arena, i32 max_vertex_count)
{
    this->vertex_list = PushArray(arena, max_vertex_count, Vertex);
    this->vert_arr_id = 0;
    this->vert_buf_id = 0;
    this->num_vertices = 0;
    this->current_vertex_per_primitive = 3;
    this->max_vertex_count = max_vertex_count;

    glGenVertexArrays(1, &vert_arr_id);
    glBindVertexArray(vert_arr_id);

    glCreateBuffers(1, &vert_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buf_id);

    glVertexAttribPointer(0,
                          sizeof(Vertex::position) / sizeof(f32),
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void *)(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          sizeof(Vertex::color) / sizeof(f32),
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void *)(offsetof(Vertex, color)));
    glEnableVertexAttribArray(1);

    glClearColor(0.098, 0.098, 0.090, 1.0f);
}

void ren::begin_Im() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
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

void ren::quad_Im(f32 x0, f32 y0, f32 x1, f32 y1, Color color)
{
    if (num_vertices > (max_vertex_count - 6))
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

void ren::put_vertex(Vertex *vert, v2 position, Color color)
{
    vert->position = {position.x, position.y, 0};
    vert->color    = color;
}

void ren::end_Im()
{
    ren::flush();
    // glDeleteVertexArrays(1, &vert_arr_id);
    // glBindVertexArray(0);
}
