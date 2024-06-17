#ifndef O_TITLES_H
#define O_TITLES_H
#include "types.h"

void o_titles_draw_level_finished (SDL_Renderer *, fonts_t, colors_t, scene_t, counters_t);
void o_titles_draw_opening_title (SDL_Renderer *, fonts_t, colors_t, scene_t);
void o_titles_draw_paused (SDL_Renderer *, fonts_t, colors_t, scene_t);

#endif
