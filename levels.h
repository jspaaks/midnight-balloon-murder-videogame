#ifndef LEVELS_H
#define LEVELS_H
#include "types.h"

void levels_deinit(ctx_t *);
void levels_init(ctx_t *);
void levels_set (scene_t, ctx_t *, counters_t *, unsigned int, drawables_t *);

#endif
