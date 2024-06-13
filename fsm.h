#ifndef FSM_H
#define FSM_H

#include "SDL_surface.h"
#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_events.h"
#include "types.h"

gamestate_t * fsm_gamestate_get (gamestate_name_t);

#endif
