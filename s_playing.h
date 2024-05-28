#ifndef S_PLAYING_H
#define S_PLAYING_H

#include <SDL_render.h>
#include <SDL_events.h>
#include "fsm.h"
#include "types.h"

void playing_draw (ctx_t *);
void playing_update (struct state **, SDL_Event *);

#endif
