#ifndef O_GROUND_H
#define O_GROUND_H
#include "SDL_render.h"
#include "types.h"

void drawable_groundrawable_draw (SDL_Renderer *, colors_t, scene_t, groundrawable_t);
groundrawable_t drawable_groundrawable_init(scene_t);

#endif
