#include "chunks.h"
#include "colors.h"
#include "counters.h"
#include "deinit.h"
#include "drawable_balloons.h"
#include "drawable_barrel.h"
#include "drawable_bullets.h"
#include "drawable_collisions.h"
#include "drawable_flash.h"
#include "drawable_ground.h"
#include "drawable_legend.h"
#include "drawable_moon.h"
#include "drawable_turret.h"
#include "drawables.h"
#include "drawing.h"
#include "fonts.h"
#include "fsm.h"
#include "levels.h"
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

static void sdl_init (void);

static void sdl_init (void) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_LogError(SDL_ENOMEM, "Error initializing SDL: %s\n", SDL_GetError());
        deinit();
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_ShowCursor(SDL_DISABLE);
}

int main (void) {

    chunks_t chunks;
    counters_t counters;
    drawables_t drawables;
    drawing_t drawing;
    gamestate_t * frame;
    gamestate_t * gamestate;
    level_t level;
    unsigned int nframes;
    timing_t timing;
    Uint64 tnow;
    Uint64 tstart;

    srand(time(NULL));

    deinit_prepare(&drawables.balloons, &drawables.bullets, &drawables.collisions,
                   &drawing.renderer, &drawing.window, &drawing.spritesheet, &drawing.fonts,
                   &chunks);

    sdl_init();
    level = levels_get_level(LEVEL_NOVICE);
    counters = counters_init(level);
    drawing = drawing_init();
    drawables = drawables_init(drawing.scene);
    timing = timing_init();
    chunks = chunks_init();

    levels_reset_level(level, drawing, &drawables, &counters);

    gamestate = fsm_gamestate_get(GAMESTATE_STARTING);
    frame = gamestate;
    tnow = SDL_GetTicks64();
    tstart = tnow;

    nframes = 0;

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
    deinit();
    return EXIT_SUCCESS;
}
