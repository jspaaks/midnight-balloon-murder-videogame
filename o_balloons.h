#ifndef BALLOONS_H
#define BALLOONS_H
#include "types.h"

void o_balloons_deinit (balloon_t **);
void o_balloons_draw (SDL_Renderer *, SDL_Texture *, scene_t, balloon_t *);
void o_balloons_init (level_t *, balloon_t **, counters_t *);
void o_balloons_update (timing_t, scene_t, ground_t, balloon_t **, counters_t *);

#endif
