#include "mbm/fsm.h"
#include "mbm/fsm_level_finished.h"
#include "mbm/fsm_paused.h"
#include "mbm/fsm_playing.h"
#include "mbm/fsm_start.h"
#include "mbm/types.h"

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

gamestate_t * fsm_gamestate_get (const gamestate_enum_t label) {
    return &gamestates[label];
}
