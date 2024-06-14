#ifndef FSM_PLAYING_H
#define FSM_PLAYING_H
#include "SDL_render.h"
#include "types.h"

void fsm_playing_draw (ctx_t *, SDL_Renderer *);
void fsm_playing_update (ctx_t *, SDL_Renderer *, gamestate_t **);

#endif
