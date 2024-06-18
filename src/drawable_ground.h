#ifndef DRAWABLE_GROUND_H
#define DRAWABLE_GROUND_H
#include "SDL_render.h"
#include "types.h"

void drawable_ground_draw (SDL_Renderer *, colors_t, scene_t, ground_t);
ground_t drawable_ground_init(scene_t);

#endif
