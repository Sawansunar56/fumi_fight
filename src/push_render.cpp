#include "types.h"
#include "push_render.h"
#include <glad/glad.h>
#include "Shaders.h"
#include "my_maths.h"
#include "texture.h"

void ren::Init_Im(Arena *arena)
{
    this->vert_arr_id                  = 0;
    this->vert_buf_id                  = 0;
    this->current_vertex_per_primitive = 3;
    this->num_vertices                 = 0;
    this->num_indices                  = 0;
    this->max_vertex_count             = MAX_VERT_COUNT;
    this->max_index_count              = MAX_INDEX_COUNT;
    this->vertex_list        = PushArray(arena, this->max_vertex_count, Vertex);
    this->index_list         = PushArray(arena, this->max_index_count, u32);
    this->shaderList.list    = PushArray(arena, SHADER_MAX, Shader *);
    this->shaderList.maximum = SHADER_MAX;

    // NOTE: Improve this shader handling after you have the full picture of the
    // amount of things needed.
    for (i32 i = 0; i < SHADER_MAX; ++i)
    {
        this->shaderList.list[i] = PushStruct(arena, Shader);
    }

    // CLEAN: This would get to tedious after sometime. COMPRESS IT.
    if (!this->shaderList.list[SHADER_BASIC]->isInitialized)
    {
        this->shaderList.list[SHADER_BASIC]->Init(
            "./shaders/basic_shader.vert",
            "./shaders/basic_shader.frag");
    }

    if (!this->shaderList.list[SHADER_TEXTURE]->isInitialized)
    {
        this->shaderList.list[SHADER_TEXTURE]->Init(
            "./shaders/texture_shader.vert",
            "./shaders/texture_shader.frag");
    }

    m_Projection = create_orthographic_mat(0.0f, 1280, 720, 0.0f, 1.0f, -1.0f);

    glGenVertexArrays(1, &vert_arr_id);
    glBindVertexArray(vert_arr_id);

    glCreateBuffers(1, &vert_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, vert_buf_id);

    glCreateBuffers(1, &index_buf_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);

    // TODO: include uv as well but use index buffer to reserve on memory.
    glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(f32),
                          GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(f32),
                          GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, color)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, sizeof(Vertex::uv0) / sizeof(f32),
                          GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, uv0)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, texture_index)));
    glEnableVertexAttribArray(3);

    setbackgroundColorHSL({182, 5, 8, 100});

    for (u8 i = 0; i < MAX_TEXTURE_SLOT; ++i)
    {
        texture_samplers[i] = i;
        textures[i]         = nullptr;
    }
    this->texture_slot_index = 0;

    Shader *texture_Shader = this->shaderList.list[SHADER_TEXTURE];
    texture_Shader->Bind();
    texture_Shader->SetIntArray("u_textures",
                                texture_samplers,
                                MAX_TEXTURE_SLOT);
}

void ren::setBackgroundColorRGB(const color &rgb_color)
{
    color Color = normalize_color(rgb_color);
    glClearColor(Color.x, Color.y, Color.z, Color.a);
}

void ren::setbackgroundColorHSL(const hsl_color &Hsl_Color)
{
    color Color = normalize_hsl(Hsl_Color);
    glClearColor(Color.r, Color.g, Color.b, Color.a);
}

void ren::setBackgroundColor(const color &Color)
{
    setBackgroundColorRGB(Color);
}

void ren::begin_Im(s32 ShaderType)
{
    Shader *shader = shaderList.list[ShaderType];
    shader->Bind();

    shader->SetUniformMat4("u_Projection", m_Projection);
    // shader->SetInt("text1", 0);
    this->draw_call = 0;
}

void ren::end_Im() { ren::flush(); }

void ren::flush()
{
    this->draw_call += 1;
    if (!num_vertices || !num_indices)
    {
        return;
    }

    Vertex *v = vertex_list;
    u32 *i    = index_list;

    glBindBuffer(GL_ARRAY_BUFFER, vert_buf_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(v[0]) * num_vertices,
                 v,
                 GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(i[0]) * num_indices,
                 i,
                 GL_STATIC_DRAW);

    if (current_vertex_per_primitive == 3)
    {
        // glDrawArrays(GL_TRIANGLES, 0, num_vertices);
        glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
    }
    num_vertices = 0;
    num_indices  = 0;
}

void ren::quad_Im(f32 x0, f32 y0, f32 x1, f32 y1, color Color)
{
    if (num_vertices > (max_vertex_count - 4) ||
        num_indices > (max_index_count - 6))
    {
        flush();
    }

    Vertex *v = vertex_list + num_vertices;
    u32 *i    = index_list + num_indices;

    // put_vertex(&v[0], {x1, y0}, Color);
    // put_vertex(&v[1], {x0, y0}, Color);
    // put_vertex(&v[2], {x1, y1}, Color);
    //
    // put_vertex(&v[3], {x1, y1}, Color);
    // put_vertex(&v[4], {x0, y0}, Color);
    // put_vertex(&v[5], {x0, y1}, Color);
    put_vertex(&v[0], {x0, y0}, Color);
    put_vertex(&v[1], {x1, y0}, Color);
    put_vertex(&v[2], {x1, y1}, Color);
    put_vertex(&v[3], {x0, y1}, Color);

    i[0] = num_indices + 1;
    i[1] = num_indices + 0;
    i[2] = num_indices + 2;
    i[3] = num_indices + 2;
    i[4] = num_indices + 0;
    i[5] = num_indices + 3;

    // top_right, top_left, bottom_right, bottom_right, top_left, bottom_left

    num_vertices += 4;
    num_indices += 6;
}

void ren::put_vertex(Vertex *vert, v2 position, color Color, v2 uv)
{
    vert->position = {position.x, position.y, 0};
    vert->color    = Color;
    vert->uv0      = uv;
}

void ren::put_vertex(Vertex *vert,
                     v2 position,
                     color Color,
                     f32 texture_index,
                     v2 uv)
{
    vert->position      = {position.x, position.y, 0};
    vert->color         = Color;
    vert->uv0           = uv;
    vert->texture_index = texture_index;
}

void ren::add_shader_Im(Shader *current_shader, shader_types type)
{
    if (shaderList.count >= shaderList.maximum)
    {
        printf("maximum shader list limit reached\n");
        return;
    }

    shaderList.list[type] = current_shader;
    shaderList.count += 1;
}

void ren::begin_texture_mode_Im(s32 ShaderType)
{
    Shader *shader = shaderList.list[ShaderType];
    shader->Bind();

    // CLEAN: Is there a way to do this without making it null everytime I start
    // for (i32 i = 0; i < MAX_TEXTURE_SLOT; i++)
    // {
    //     textures[i] = nullptr;
    // }

    shader->SetUniformMat4("u_Projection", m_Projection);
    // texture_slot_index = 0;
    this->draw_call = 0;
}

void ren::end_texture_mode_Im() { texture_flush(); }

void ren::texture_flush()
{
    for (u8 i = 0; i < MAX_TEXTURE_SLOT; i++)
    {
        if (!textures[i])
            continue;
        textures[i]->Bind(i);
    }

    flush();
    texture_slot_index = 0;
}

void ren::quad_texture_Im(f32 x0,
                          f32 y0,
                          f32 x1,
                          f32 y1,
                          color Color,
                          v4 uv,
                          Texture2D *texture)
{
    f32 tex_index = -1.0f;
    if (num_vertices > (max_vertex_count - 4) ||
        num_indices > (max_index_count - 6))
    {
        flush();
    }
    for (i32 i = 0; i < MAX_TEXTURE_SLOT; i++)
    {
        if (!textures[i])
            continue;
        if (textures[i]->m_Id == texture->m_Id)
        {
            tex_index = (f32)i;
            texture_slot_index++;
            break;
        }
    }

    if (tex_index < 0)
    {
        // FIX: Because texture_slot_index doesn't get incrementated if the
        // value is found in the list. It causes the thing to override if you
        // finally can't find the value in it starting from zero.
        // CLEAN: Not removing the above comment because I don't really know if
        // incrementing the slot index would fix the problem in edge cases,
        // maybe even introduce a new bug.
        if (texture_slot_index >= MAX_TEXTURE_SLOT)
        {
            texture_flush();
        }

        tex_index                    = (f32)texture_slot_index;
        textures[texture_slot_index] = texture;
        texture_slot_index++;
    }

    Vertex *v = vertex_list + num_vertices;
    u32 *i    = index_list + num_indices;
    // NOTE: This is pretty unreadable now. Make sure to clean this up somehow.
    // put_vertex(&v[0], {x1, y0}, Color, tex_index, {uv.z, uv.y});
    // put_vertex(&v[1], {x0, y0}, Color, tex_index, {uv.x, uv.y});
    // put_vertex(&v[2], {x1, y1}, Color, tex_index, {uv.z, uv.w});
    //
    // put_vertex(&v[3], {x1, y1}, Color, tex_index, {uv.z, uv.w});
    // put_vertex(&v[4], {x0, y0}, Color, tex_index, {uv.x, uv.y});
    // put_vertex(&v[5], {x0, y1}, Color, tex_index, {uv.x, uv.w});

    // top_right, top_left, bottom_right, bottom_right, top_left, bottom_left
    // 1, 0, 2, 2, 0, 3
    // 5, 4, 6, 6, 4, 7
    put_vertex(&v[0], {x0, y0}, Color, tex_index, {uv.x, uv.y});
    put_vertex(&v[1], {x1, y0}, Color, tex_index, {uv.z, uv.y});
    put_vertex(&v[2], {x1, y1}, Color, tex_index, {uv.z, uv.w});
    put_vertex(&v[3], {x0, y1}, Color, tex_index, {uv.x, uv.w});

    i[0] = num_vertices + 1;
    i[1] = num_vertices + 0;
    i[2] = num_vertices + 2;
    i[3] = num_vertices + 2;
    i[4] = num_vertices + 0;
    i[5] = num_vertices + 3;

    num_vertices += 4;
    num_indices += 6;
}
