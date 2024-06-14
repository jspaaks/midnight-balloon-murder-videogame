#ifndef FSM_LEVEL_FINISHED_H
#define FSM_LEVEL_FINISHED_H
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"

void fsm_level_finished_draw (ctx_t *, SDL_Renderer *);
void fsm_level_finished_update (ctx_t *, SDL_Window *, SDL_Renderer *, gamestate_t **);

#endif
