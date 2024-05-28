#include "s_playing.h"
#include "types.h"
#include "constants.h"
#include "fsm.h"
#include "o_background.h"
#include "o_moon.h"
#include "o_ground.h"
#include "o_turret.h"
#include <SDL_render.h>
#include <SDL_rect.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_events.h>
#include <stdio.h>
#include <stdlib.h>

void playing_draw (ctx_t * ctx) {
    background_draw(ctx);
    ground_draw(ctx);
    moon_draw(ctx);
    turret_draw(ctx);
}

void playing_update (struct state ** game, SDL_Event * event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            fprintf(stdout, "Pausing.\n");
            *game = fsm_set_state(PAUSED);
        }
        turret_update(event);
    }
}
