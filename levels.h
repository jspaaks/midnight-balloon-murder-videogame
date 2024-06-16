#ifndef LEVELS_H
#define LEVELS_H
#include "types.h"

void levels_deinit(ctx_t *);
void levels_init(ctx_t *);
void levels_set (scene_t, unsigned int, ctx_t *, counters_t *, drawables_t *);

#endif
