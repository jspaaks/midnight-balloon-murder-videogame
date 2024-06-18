#ifndef BALLOONS_H
#define BALLOONS_H
#include "types.h"

void drawable_balloons_deinit (balloon_t **);
void drawable_balloons_draw (SDL_Renderer *, SDL_Texture *, scene_t, balloon_t *);
balloon_t * drawable_balloons_init (void);
void drawable_balloons_update (timing_t, scene_t, groundrawable_t, balloon_t **, counters_t *);

#endif
