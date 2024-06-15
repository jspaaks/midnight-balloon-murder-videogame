#include "fsm.h"
#include "fsm_start.h"
#include "fsm_playing.h"
#include "fsm_paused.h"
#include "fsm_level_finished.h"
#include "types.h"

static gamestate_t gamestates[] = {
    {
        .draw = fsm_start_draw,
        .label = GAMESTATE_STARTING,
        .update = fsm_start_update,
    },
    {
        .draw = fsm_playing_draw,
        .label = GAMESTATE_PLAYING,
        .update = fsm_playing_update,
    },
    {
        .draw = fsm_paused_draw,
        .label = GAMESTATE_PAUSING,
        .update = fsm_paused_update,
    },
    {
        .draw = fsm_level_finished_draw,
        .label = GAMESTATE_FINISHING_LEVEL,
        .update = fsm_level_finished_update,
    },
};

gamestate_t * fsm_gamestate_get (gamestate_enum_t label) {
    return &gamestates[label];
}
