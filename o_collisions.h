#ifndef O_COLLISIONS_H
#define O_COLLISIONS_H
#include "types.h"

void o_collisions_deinit (ctx_t *);
void o_collisions_draw (ctx_t *, SDL_Renderer *);
void o_collisions_init (ctx_t *);
void o_collisions_update (ctx_t *);

#endif
