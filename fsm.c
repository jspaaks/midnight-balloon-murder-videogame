#include "fsm.h"
#include "hiscores.h"
#include "playing.h"
#include "SDL_surface.h"
#include "SDL_video.h"

static state_t states[] = {
    {
        .draw = playing_draw,
        .label = PLAYING,
        .update = playing_update,
    },
    {
        .draw = hiscores_draw,
        .label = HISCORES,
        .update = hiscores_update,
    },
};

state_t * fsm_set_state (state_name_t label) {
    return &states[label];
}
