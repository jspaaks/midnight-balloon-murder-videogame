#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "SDL.h"
#include "chunks.h"
#include "colors.h"
#include "fonts.h"
#include "fsm.h"
#include "keystate.h"
#include "levels.h"
#include "renderer.h"
#include "spritesheet.h"
#include "types.h"
#include "window.h"
#include "o_scene.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_turret.h"
#include "o_legend.h"


static void deinit (ctx_t *, SDL_Renderer **);
static void init (ctx_t *, SDL_Renderer **);

static void deinit (ctx_t * ctx, SDL_Renderer ** renderer) {
    // --- concrete entities
    o_balloons_deinit(ctx);
    o_bullets_deinit(ctx);
    o_collisions_deinit(ctx);
    // --- abstract entities
    levels_deinit(ctx);
    fonts_deinit(ctx);
    chunks_deinit(ctx);
    keystate_deinit(ctx);
    // --- sdl infrastructure
    renderer_deinit(renderer);
    window_deinit(ctx);
    spritesheet_deinit(ctx);
    // --- deinitialize sdl library
    SDL_Quit();
}

static void init (ctx_t * ctx, SDL_Renderer ** renderer) {
    // initialize the random number generator
    srand(time(NULL));
    // --- initialize sdl library
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_LogError(SDL_ENOMEM, "Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // --- sdl infrastructure
    o_scene_init(ctx);
    window_init(ctx);
    renderer_init(ctx, renderer);
    spritesheet_init(ctx, *renderer);
    // --- abstract entities
    colors_init(ctx);
    fonts_init(ctx);
    keystate_init(ctx);
    chunks_init(ctx);
    levels_init(ctx);
    // --- time related
    ctx->dt.frame = 0.0000000000001;
}

int main (void) {
    SDL_Log("starting\n");
    ctx_t ctx;
    SDL_Renderer * renderer = NULL;
    init(&ctx, &renderer);
    gamestate_t * gamestate = fsm_gamestate_get(GAMESTATE_STARTING);
    gamestate_t * frame = gamestate;
    Uint64 tnow = SDL_GetTicks64();
    Uint64 tstart = tnow;

    unsigned int nframes = 0;

    while (true) {

        frame = gamestate;  // so .update() and .draw() are of the same state
        frame->draw(&ctx, renderer);
        frame->update(&ctx, &gamestate);

        nframes++;

        SDL_Delay(1);
        tnow = SDL_GetTicks64();
        if (tnow - tstart > 10) {
            ctx.dt.frame = ((float) (tnow - tstart)) / nframes / 1000;
            nframes = 0;
            tstart = SDL_GetTicks64();
        }
    }
    deinit(&ctx, &renderer);
    return EXIT_SUCCESS;
}
