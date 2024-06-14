#ifndef O_BULLETS_H
#define O_BULLETS_H
#include "types.h"

void o_bullets_deinit (ctx_t *);
void o_bullets_draw (ctx_t *, SDL_Renderer *);
void o_bullets_init (ctx_t *);
void o_bullets_update (ctx_t *);

#endif
