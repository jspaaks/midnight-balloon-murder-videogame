#ifndef LEVELS_H
#define LEVELS_H
#include "types.h"

void levels_deinit(ctx_t *);
void levels_init(ctx_t *);
void levels_set (ctx_t *, unsigned int, drawing_t *, drawables_t *);

#endif
