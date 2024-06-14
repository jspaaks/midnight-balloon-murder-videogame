#ifndef O_SCENE_H
#define O_SCENE_H
#include "types.h"

void o_scene_draw (ctx_t *, SDL_Renderer *);
void o_scene_init(ctx_t *);
void o_scene_update (ctx_t *, SDL_Renderer *);
SDL_Rect sim2tgt (scene_t, SDL_FRect);

#endif
