#ifndef FSM_PAUSED_H
#define FSM_PAUSED_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_paused_draw (ctx_t, drawing_t, drawables_t);
void fsm_paused_update (ctx_t *, SDL_Window *, drawing_t *, drawables_t *, gamestate_t **);

#endif
