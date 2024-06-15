#ifndef FSM_PAUSED_H
#define FSM_PAUSED_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_paused_draw (ctx_t, drawing_t, drawables_t, counters_t);
void fsm_paused_update (SDL_Window *, timing_t, counters_t *, ctx_t *, drawing_t *, drawables_t *, gamestate_t **);

#endif
