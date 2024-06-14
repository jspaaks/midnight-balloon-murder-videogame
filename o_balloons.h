#ifndef BALLOONS_H
#define BALLOONS_H
#include "types.h"

void o_balloons_draw (ctx_t *, SDL_Renderer *);
void o_balloons_deinit (ctx_t *);
void o_balloons_init (ctx_t *);
void o_balloons_update (ctx_t *);
void o_balloons_update_remove (ctx_t *);

#endif
