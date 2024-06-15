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
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_scene.h"
#include "o_turret.h"

static void deinit (ctx_t *, SDL_Window **, drawing_t *, drawables_t *);
static void init_ctx (ctx_t *, timing_t *);
static void init_sdl (void);
static void init_drawing (drawing_t *, SDL_Window **);
static void init_drawables (ctx_t, drawing_t *, drawables_t *, counters_t *);

static void deinit (ctx_t * ctx, SDL_Window ** window, drawing_t * drawing, drawables_t * drawables) {
    // --- concrete entities
    o_balloons_deinit(&drawables->balloons);
    o_bullets_deinit(&drawables->bullets);
    o_collisions_deinit(&drawables->collisions);
    // --- abstract entities
    levels_deinit(ctx);
    fonts_deinit(&drawing->fonts);
    chunks_deinit(ctx);
    keystate_deinit(ctx);
    // --- sdl infrastructure
    renderer_deinit(&drawing->renderer);
    window_deinit(window);
    spritesheet_deinit(&drawing->spritesheet);
    // --- deinitialize sdl library
    SDL_Quit();
}

static void init_ctx (ctx_t * ctx, timing_t * timing) {
    keystate_init(ctx);
    chunks_init(ctx);
    levels_init(ctx);
    timing->dt.frame = 0.0000000000001;
    ctx->isfullscreen = false;
    ctx->resized = true;
}

static void init_sdl (void) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_LogError(SDL_ENOMEM, "Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

static void init_drawables (ctx_t ctx, drawing_t * drawing, drawables_t * drawables, counters_t * counters) {
    o_ground_init(drawing->scene, &drawables->ground);
    o_moon_init(drawing->scene, &drawables->moon);
    o_turret_init(drawing->scene, drawables->ground, &drawables->turret);
    o_barrel_init(drawables->turret, &drawables->barrel);
    o_balloons_init(ctx.level, &drawables->balloons, counters);
    o_bullets_init(ctx.level, drawables->ground, &drawables->bullets, counters);
    o_collisions_init(&drawables->collisions);
    o_flash_init(drawables->barrel, &drawables->flash);
    o_legend_init(&drawables->legend);
}

static void init_drawing (drawing_t * drawing, SDL_Window ** window) {
    o_scene_init(&drawing->scene);
    window_init(drawing->scene, window);
    renderer_init(*window, &drawing->renderer);
    spritesheet_init(drawing->renderer, &drawing->spritesheet);
    colors_init(&drawing->colors);
    fonts_init(&drawing->fonts);
}

int main (void) {

    ctx_t ctx;
    drawables_t drawables;
    drawing_t drawing;
    timing_t timing;
    counters_t counters;
    SDL_Window * window = NULL;

    srand(time(NULL));

    init_sdl();
    init_drawing(&drawing, &window);
    init_ctx(&ctx, &timing);
    init_drawables(ctx, &drawing, &drawables, &counters);

    levels_set(&ctx, &counters, LEVEL_NOVICE, &drawing, &drawables);

    gamestate_t * gamestate = fsm_gamestate_get(GAMESTATE_STARTING);
    gamestate_t * frame = gamestate;
    Uint64 tnow = SDL_GetTicks64();
    Uint64 tstart = tnow;

    unsigned int nframes = 0;

    SDL_Log("starting\n");
    while (true) {

        frame = gamestate;  // so .update() and .draw() are of the same state
        frame->draw(ctx, drawing, drawables, counters);
        frame->update(timing, &counters, &ctx, window, &drawing, &drawables, &gamestate);

        nframes++;

        SDL_Delay(1);
        tnow = SDL_GetTicks64();
        if (tnow - tstart > 10) {
            timing.dt.frame = ((float) (tnow - tstart)) / nframes / 1000;
            nframes = 0;
            tstart = SDL_GetTicks64();
        }
    }
    deinit(&ctx, &window, &drawing, &drawables);
    return EXIT_SUCCESS;
}
