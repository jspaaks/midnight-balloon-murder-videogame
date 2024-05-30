#ifndef S_PLAYING_H
#define S_PLAYING_H

#include <SDL_render.h>
#include <SDL_events.h>
#include "fsm.h"
#include "context.h"

void playing_draw (ctx_t *);
void playing_update (ctx_t *, struct state **);

#endif
