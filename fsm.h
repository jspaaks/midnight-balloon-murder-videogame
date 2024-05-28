#ifndef FSM_H
#define FSM_H

#include "types.h"
#include <SDL_surface.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>

typedef enum {
    PLAYING = 0,
    PAUSED,
} state_name_t;

struct state {
    void (*draw)(ctx_t *);
    void (*update)(struct state **, SDL_Event *);
    state_name_t label;
};

struct state * fsm_set_state (state_name_t);

#endif
