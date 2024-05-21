#ifndef FSM_H
#define FSM_H

#include "SDL_surface.h"
#include "SDL_video.h"

typedef enum {
    PLAYING = 0,
    HISCORES
} state_name_t;

typedef struct {
    void (*draw)(SDL_Window **, SDL_Surface **);
    void (*update)(void);
    state_name_t label;
} state_t;

state_t * fsm_set_state (state_name_t);

#endif
