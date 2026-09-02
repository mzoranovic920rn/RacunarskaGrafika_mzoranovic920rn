#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <math_3d.h>
#include <rafgl.h>

extern vec3_t camera_position;
extern vec3_t camera_target;
extern vec3_t camera_up;

extern mat4_t view;
extern mat4_t projection;
extern mat4_t view_projection;

void camera_init(void);
void camera_update(rafgl_game_data_t *game_data, float delta_time, int raster_width, int raster_height);

#endif
