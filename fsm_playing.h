#ifndef FSM_PLAYING_H
#define FSM_PLAYING_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_playing_draw (ctx_t, drawing_t, drawables_t, counters_t);
void fsm_playing_update (timing_t, counters_t *, ctx_t *, drawing_t *, drawables_t *, gamestate_t **);

#endif
