#include "fsm.h"
#include "s_start.h"
#include "s_playing.h"
#include "s_paused.h"

static struct state states[] = {
    {
        .draw = s_start_draw,
        .label = START,
        .update = s_start_update,
    },
    {
        .draw = s_playing_draw,
        .label = PLAYING,
        .update = s_playing_update,
    },
    {
        .draw = s_paused_draw,
        .label = PAUSED,
        .update = s_paused_update,
    },
};

struct state * fsm_set_state (state_name_t label) {
    return &states[label];
}
