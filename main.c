#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "SDL.h"
#include "colors.h"
#include "constants.h"
#include "fonts.h"
#include "fsm.h"
#include "keystate.h"
#include "levels.h"
#include "renderer.h"
#include "spritesheet.h"
#include "types.h"
#include "window.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_turret.h"
#include "o_legend.h"


static void deinit (ctx_t *);
static bool init (ctx_t *);

static void deinit (ctx_t * ctx) {
    // --- concrete entities
    ctx = o_balloons_deinit(ctx);
    // --- abstract entities
    ctx = levels_deinit(ctx);
    ctx = fonts_deinit(ctx);
    ctx = keystate_deinit(ctx);
    // --- sdl infrastructure
    ctx = renderer_deinit(ctx);
    ctx = window_deinit(ctx);
    ctx = spritesheet_deinit(ctx);
    // --- deinitialize sdl library
    SDL_Quit();
}

static bool init (ctx_t * ctx) {
    // initialize the random number generator
    srand(time(NULL));
    // --- initialize sdl library
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_LogError(SDL_ENOMEM, "Error initializing SDL: %s\n", SDL_GetError());
        return false;
    }
    // --- sdl infrastructure
    ctx = window_init(ctx);
    ctx = renderer_init(ctx);
    ctx = spritesheet_init(ctx);
    // --- abstract entities
    ctx = colors_init(ctx);
    ctx = fonts_init(ctx);
    ctx = levels_init(ctx);
    ctx = keystate_init(ctx);
    // --- concrete entities
    ctx = o_turret_init(ctx);
    ctx = o_barrel_init(ctx);
    ctx = o_balloons_init(ctx);
    ctx = o_bullets_init(ctx);
    ctx = o_collisions_init(ctx);
    ctx = o_flash_init(ctx);
    ctx = o_legend_init(ctx);
    // --- time related
    ctx->dt.frame = 0.0000000000001;
    return true;
}

int main (void) {
    ctx_t ctx;
    if (!init(&ctx)) {
        exit(EXIT_FAILURE);
    }

    struct state * state = fsm_set_state (PLAYING);
    struct state * frame = state;
    Uint64 tstart;

    bool have_balloons = true;
    bool have_bullets = true;

    while (have_balloons && have_bullets) {
        tstart = SDL_GetTicks64();

        frame = state;  // so .update() and .draw() are of the same state
        frame->update(&ctx, &state);
        frame->draw(&ctx);

        have_balloons = ctx.nprespawn + ctx.nairborne > 0;
        have_bullets = ctx.nbullets > 0; // TODO take airborne bullets into account

        SDL_Delay(1);
        ctx.dt.frame = ((float) (SDL_GetTicks64() - tstart)) / 1000;
    }
    if (!have_balloons) {
        SDL_Log("No more balloons.\n");
    }
    if (!have_bullets) {
        SDL_Log("No more bullets.\n");
    }

    deinit(&ctx);
    return EXIT_SUCCESS;
}
