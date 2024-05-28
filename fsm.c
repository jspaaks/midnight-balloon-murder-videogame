#include "fsm.h"
#include "playing.h"
#include "paused.h"

static struct state states[] = {
    {
        .draw = playing_draw,
        .label = PLAYING,
        .update = playing_update,
    },
    {
        .draw = paused_draw,
        .label = PAUSED,
        .update = paused_update,
    },
};

struct state * fsm_set_state (state_name_t label) {
    return &states[label];
}
