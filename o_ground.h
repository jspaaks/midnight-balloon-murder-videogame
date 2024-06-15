#ifndef O_GROUND_H
#define O_GROUND_H
#include "SDL_render.h"
#include "types.h"

void o_ground_draw (SDL_Renderer *, scene_t, colors_t, ground_t);
void o_ground_init (scene_t, ground_t *);

#endif
