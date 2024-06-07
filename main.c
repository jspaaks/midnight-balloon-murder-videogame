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
    ctx->resized = true;
    ctx->scene = (SDL_Rect) {
        .x = 0,
        .y = 0,
        .w = 1280,
        .h = 720,
    };
    // --- abstract entities
    ctx = colors_init(ctx);
    ctx = fonts_init(ctx);
    ctx = keystate_init(ctx);
    ctx = levels_init(ctx);
    // --- time related
    ctx->dt.frame = 0.0000000000001;
    return true;
}

int main (void) {
    ctx_t ctx;
    if (!init(&ctx)) {
        exit(EXIT_FAILURE);
    }

    state_t * state = fsm_set_state (START);
    state_t * frame = state;
    Uint64 tnow = SDL_GetTicks64();
    Uint64 tstart = tnow;

    unsigned int nframes = 0;

    while (true) {

        frame = state;  // so .update() and .draw() are of the same state
        frame->update(&ctx, &state);
        frame->draw(&ctx);

        nframes++;

        SDL_Delay(1);
        tnow = SDL_GetTicks64();
        if (tnow - tstart > 10) {
            ctx.dt.frame = ((float) (tnow - tstart)) / nframes / 1000;
            nframes = 0;
            tstart = SDL_GetTicks64();
        }
    }
    deinit(&ctx);
    return EXIT_SUCCESS;
}
