#include <main_state.h>
#include <glad/glad.h>
#include <math.h>

#include <rafgl.h>
#include <game_constants.h>

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
}

void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{

}

void main_state_render(GLFWwindow *window, void *args)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
