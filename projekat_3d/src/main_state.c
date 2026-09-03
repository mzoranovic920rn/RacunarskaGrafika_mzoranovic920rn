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
}; //Da zamenim z umesto 5 da ide na 9

static GLfloat levi_zid_vertices[] =
{
    5, -1, -5,     0.7, 0.7, 0.7,
    5, -1,  5,     0.7, 0.7, 0.7,
    5,  3,  5,     0.7, 0.7, 0.7,

    5,  3,  5,     0.7, 0.7, 0.7,
    5,  3, -5,     0.7, 0.7, 0.7,
    5, -1, -5,     0.7, 0.7, 0.7,
};


static GLfloat desni_zid_vertices[] =
{
    -5, -1, -5,     0.7, 0.7, 0.7,
    -5, -1,  5,     0.7, 0.7, 0.7,
    -5,  3,  5,     0.7, 0.7, 0.7,

    -5,  3,  5,     0.7, 0.7, 0.7,
    -5,  3, -5,     0.7, 0.7, 0.7,
    -5, -1, -5,     0.7, 0.7, 0.7,
};

static GLfloat zadnji_zid_vertices[] =
{
    -5, -1, 5,     0.7, 0.7, 0.7,
     5, -1, 5,     0.7, 0.7, 0.7,
     5,  3, 5,     0.7, 0.7, 0.7,

     5,  3, 5,     0.7, 0.7, 0.7,
    -5,  3, 5,     0.7, 0.7, 0.7,
    -5, -1, 5,     0.7, 0.7, 0.7,
};


static GLuint vao, vbo, shader_program_id, uni_M, uni_VP;
static GLuint levi_zid_vao, levi_zid_vbo;
static GLuint desni_zid_vao, desni_zid_vbo;
static GLuint zadnji_zid_vao, zadnji_zid_vbo;

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

    //za levi zid
    glGenVertexArrays(1, &levi_zid_vao);
    glGenBuffers(1, &levi_zid_vbo);

    glBindVertexArray(levi_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, levi_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(levi_zid_vertices), levi_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //za desni zid

    glGenVertexArrays(1, &desni_zid_vao);
    glGenBuffers(1, &desni_zid_vbo);

    glBindVertexArray(desni_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, desni_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(desni_zid_vertices), desni_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //zadnji zid
    glGenVertexArrays(1, &zadnji_zid_vao);
    glGenBuffers(1, &zadnji_zid_vbo);

    glBindVertexArray(zadnji_zid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, zadnji_zid_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(zadnji_zid_vertices), zadnji_zid_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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


    //iscrtavanje
    glBindVertexArray(levi_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    //crtanje desni zid
    glBindVertexArray(desni_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    //crtanje zadnji zid
    glBindVertexArray(zadnji_zid_vao);

    glUniformMatrix4fv(uni_M, 1, GL_FALSE, model.m);
    glUniformMatrix4fv(uni_VP, 1, GL_FALSE, view_projection.m);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
