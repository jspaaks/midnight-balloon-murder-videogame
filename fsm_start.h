#ifndef FSM_START_H
#define FSM_START_H
#include "SDL_render.h"
#include "types.h"

void fsm_start_draw (ctx_t *, SDL_Renderer *);
void fsm_start_update (ctx_t *, SDL_Renderer *, gamestate_t **);

#endif
