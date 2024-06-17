#include "chunks.h"
#include "colors.h"
#include "counters.h"
#include "drawables.h"
#include "drawing.h"
#include "fonts.h"
#include "fsm.h"
#include "levels.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"
#include "renderer.h"
#include "scene.h"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "spritesheet.h"
#include "timing.h"
#include "types.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void deinit (chunks_t *, drawing_t *, drawables_t *);
static void sdl_init (void);

static void deinit (chunks_t * chunks, drawing_t * drawing, drawables_t * drawables) {
    // --- concrete entities
    o_balloons_deinit(&drawables->balloons);
    o_bullets_deinit(&drawables->bullets);
    o_collisions_deinit(&drawables->collisions);
    // --- abstract entities
    fonts_deinit(&drawing->fonts);
    chunks_deinit(chunks);
    // --- sdl infrastructure
    renderer_deinit(&drawing->renderer);
    window_deinit(&drawing->window);
    spritesheet_deinit(&drawing->spritesheet);
    // --- deinitialize sdl library
    SDL_Quit();
}

static void sdl_init (void) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_LogError(SDL_ENOMEM, "Error initializing SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_ShowCursor(SDL_DISABLE);
}

int main (void) {

    srand(time(NULL));

    sdl_init();
    level_t level = levels_get_level(LEVEL_NOVICE);
    counters_t counters = counters_init(level);
    drawing_t drawing = drawing_init();
    drawables_t drawables = drawables_init(drawing.scene);
    timing_t timing = timing_init();
    chunks_t chunks = chunks_init();

    levels_reset_level(level, drawing, &drawables, &counters);

    gamestate_t * gamestate = fsm_gamestate_get(GAMESTATE_STARTING);
    gamestate_t * frame = gamestate;
    Uint64 tnow = SDL_GetTicks64();
    Uint64 tstart = tnow;

    unsigned int nframes = 0;

    SDL_Log("starting\n");
    while (true) {

        frame = gamestate; // so .update() and .draw() are of the same state
        frame->draw(level, drawing, drawables, counters);
        frame->update(timing, chunks, &counters, &drawing, &drawables, &gamestate, &level);

        nframes++;

        SDL_Delay(1);
        tnow = SDL_GetTicks64();
        if (tnow - tstart > 10) {
            timing.dt.frame = ((float) (tnow - tstart)) / nframes / 1000;
            nframes = 0;
            tstart = SDL_GetTicks64();
        }
    }
    deinit(&chunks, &drawing, &drawables);
    return EXIT_SUCCESS;
}
