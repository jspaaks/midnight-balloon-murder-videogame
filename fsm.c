#include "fsm.h"
#include "s_start.h"
#include "s_playing.h"
#include "s_paused.h"
#include "s_level_finished.h"

static state_t states[] = {
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
    {
        .draw = s_level_finished_draw,
        .label = LEVEL_FINISHED,
        .update = s_level_finished_update,
    },
};

state_t * fsm_set_state (state_name_t label) {
    return &states[label];
}
