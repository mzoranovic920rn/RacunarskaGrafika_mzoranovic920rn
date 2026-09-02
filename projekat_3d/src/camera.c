#include <camera.h>
#include <stdio.h>

//definisanje
mat4_t view, projection, view_projection;

float fov = 90.0f;

vec3_t camera_position = vec3m(0.0f, 0.0f, -4.0f);
vec3_t camera_target = vec3m(0.0f, 0.0f, 0.0f);
vec3_t camera_up = vec3m(0.0f, 1.0f, 0.0f);

void camera_init(void)
{
        //trenutno ostaje prazno
}

void camera_update(rafgl_game_data_t *game_data, float delta_time, int raster_width, int raster_height)
{
    if(game_data->keys_down['W']) camera_position.z += 1.0f * delta_time;
    if(game_data->keys_down['S']) camera_position.z -= 1.0f * delta_time;

    if(game_data->keys_down['A']) camera_position.x += 1.0f * delta_time;
    if(game_data->keys_down['D']) camera_position.x -= 1.0f * delta_time;

    if(game_data->keys_down[RAFGL_KEY_SPACE]) camera_position.y += 1.0f * delta_time;
    if(game_data->keys_down[RAFGL_KEY_LEFT_SHIFT]) camera_position.y -= 1.0f * delta_time;

    float aspect = (float)raster_width / raster_height;

    projection = m4_perspective(fov, aspect, 0.1f, 100.0f);
    view = m4_look_at(camera_position, camera_target, camera_up);
    view_projection = m4_mul(projection, view);

    //dodato radi provere dal trenutno radi
    printf("Kamera pozicija: x=%.2f y=%.2f z=%.2f\n", camera_position.x, camera_position.y, camera_position.z);
}
