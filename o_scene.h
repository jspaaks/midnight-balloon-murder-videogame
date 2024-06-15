#ifndef O_SCENE_H
#define O_SCENE_H
#include "types.h"

void o_scene_draw (SDL_Renderer *, colors_t, scene_t);
void o_scene_init(scene_t *);
void o_scene_update (ctx_t *, SDL_Renderer *, scene_t *);
SDL_Rect sim2tgt (scene_t, SDL_FRect);

#endif
