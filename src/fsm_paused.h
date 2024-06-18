#ifndef FSM_PAUSED_H
#define FSM_PAUSED_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_paused_draw(level_t, drawing_t, drawables_t, counters_t);
void fsm_paused_update (timing_t, chunks_t, counters_t *, drawing_t *, drawables_t *,
                               gamestate_t **, level_t *);
#endif
