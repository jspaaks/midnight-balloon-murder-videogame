#ifndef DRAWABLE_TITLES_H
#define DRAWABLE_TITLES_H
#include "mbm/types.h"

void drawable_titles_draw_level_finished (SDL_Renderer *, fonts_t, colors_t, scene_t, counters_t);
void drawable_titles_draw_opening_title (SDL_Renderer *, fonts_t, colors_t, scene_t);
void drawable_titles_draw_paused (SDL_Renderer *, fonts_t, colors_t, scene_t);

#endif
