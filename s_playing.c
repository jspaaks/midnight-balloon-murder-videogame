#include "s_playing.h"
#include "context.h"
#include "constants.h"
#include "fsm.h"
#include "o_background.h"
#include "o_moon.h"
#include "o_ground.h"
#include "o_turret.h"
#include "o_balloons.h"
#include <SDL_render.h>
#include <SDL_rect.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_events.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>

void s_playing_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_balloons_draw(ctx);
    o_ground_draw(ctx);
}

void s_playing_update (ctx_t * ctx, struct state ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                fprintf(stdout, "pausing\n");
                *state = fsm_set_state(PAUSED);
            }
        }
    }
    o_turret_update(ctx);
    o_balloons_update(ctx);
    SDL_RenderPresent(ctx->renderer);
}
