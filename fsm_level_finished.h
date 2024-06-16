#ifndef FSM_LEVEL_FINISHED_H
#define FSM_LEVEL_FINISHED_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_level_finished_draw (ctx_t, drawing_t, drawables_t, counters_t);
void fsm_level_finished_update (timing_t, counters_t *, ctx_t *, drawing_t *, drawables_t *, gamestate_t **);

#endif
