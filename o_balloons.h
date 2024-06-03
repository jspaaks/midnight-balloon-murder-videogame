#ifndef BALLOONS_H
#define BALLOONS_H
#include <stdbool.h>
#include "types.h"
#include "SDL_rect.h"

void o_balloons_draw (ctx_t *);
void o_balloons_free (balloon_t *);
ctx_t * o_balloons_init (ctx_t *);
ctx_t * o_balloons_update (ctx_t *);

#endif
