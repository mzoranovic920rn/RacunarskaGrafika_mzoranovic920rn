#include <stdio.h>

#define RAFGL_IMPLEMENTATION
#include <rafgl.h>

#include <main_state.h>
#include <game_constants.h>

int main(void)
{
    rafgl_game_t game;

    rafgl_game_init(&game, GAME_TITLE, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, GAME_FULLSCREEN);

    rafgl_game_add_named_game_state(&game, main_state);

    rafgl_game_start(&game, NULL);

    return 0;
}
