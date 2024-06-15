#ifndef BALLOONS_H
#define BALLOONS_H
#include "types.h"

void o_balloons_deinit (balloon_t **);
void o_balloons_draw (SDL_Renderer *, scene_t, SDL_Texture *, balloon_t *);
void o_balloons_init (level_t *, balloon_t **, nballoons_t *);
void o_balloons_update (ctx_t, scene_t, ground_t, balloon_t **, nballoons_t *);

#endif
