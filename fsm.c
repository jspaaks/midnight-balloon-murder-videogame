#include "fsm.h"
#include "fsm_start.h"
#include "fsm_playing.h"
#include "fsm_paused.h"
#include "fsm_level_finished.h"

static state_t states[] = {
    {
        .draw = fsm_start_draw,
        .label = START,
        .update = fsm_start_update,
    },
    {
        .draw = fsm_playing_draw,
        .label = PLAYING,
        .update = fsm_playing_update,
    },
    {
        .draw = fsm_paused_draw,
        .label = PAUSED,
        .update = fsm_paused_update,
    },
    {
        .draw = fsm_level_finished_draw,
        .label = LEVEL_FINISHED,
        .update = fsm_level_finished_update,
    },
};

state_t * fsm_set_state (state_name_t label) {
    return &states[label];
}
