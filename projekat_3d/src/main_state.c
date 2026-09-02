#include <camera.h>
#include <main_state.h>
#include <glad/glad.h>
#include <math.h>

#include <rafgl.h>
#include <game_constants.h>

static GLfloat pod_vertices[] =
{
    -5, -1, -5,     0.5, 0.35, 0.2,
     5, -1, -5,     0.5, 0.35, 0.2,
     5, -1,  5,     0.5, 0.35, 0.2,

     5, -1,  5,     0.5, 0.35, 0.2,
    -5, -1,  5,     0.5, 0.35, 0.2,
    -5, -1, -5,     0.5, 0.35, 0.2,
};

static GLuint vao, vbo, shader_program_id, uni_M, uni_VP;
mat4_t model;

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    camera_init();

    shader_program_id = rafgl_program_create_from_name("second_shader");
    uni_M = glGetUniformLocation(shader_program_id, "uni_M");
    uni_VP = glGetUniformLocation(shader_program_id, "uni_VP");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pod_vertices), pod_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

    model = m4_identity();
}

void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    camera_update(game_data, delta_time, game_data->raster_width, game_data->raster_height);

}

void main_state_render(GLFWwindow *window, void *args)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program_id);

    glBindVertexArray(vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
