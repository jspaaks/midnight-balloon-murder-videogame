#ifndef S_PLAYING_H
#define S_PLAYING_H

#include "SDL_render.h"
#include "SDL_events.h"
#include "types.h"
#include "fsm.h"

void s_playing_draw (ctx_t *);
ctx_t * s_playing_update (ctx_t *, struct state **);

#endif
