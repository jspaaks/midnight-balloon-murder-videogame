#ifndef O_SCENE_H
#define O_SCENE_H
#include "types.h"

scene_t scene_init();
void scene_update (SDL_Renderer *, scene_t *);
SDL_Rect sim2tgt (scene_t, SDL_FRect);

#endif
