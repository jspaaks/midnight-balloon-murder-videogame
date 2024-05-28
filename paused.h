#ifndef PAUSED_H
#define PAUSED_H

#include "types.h"
#include "fsm.h"

void paused_draw (ctx_t * ctx);
void paused_update (struct state ** game, SDL_Event *);

#endif
