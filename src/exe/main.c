#include "mbm/chunks.h"
#include "mbm/colors.h"
#include "mbm/counters.h"
#include "mbm/deinit.h"
#include "mbm/drawable_balloons.h"
#include "mbm/drawable_barrel.h"
#include "mbm/drawable_bullets.h"
#include "mbm/drawable_collisions.h"
#include "mbm/drawable_flash.h"
#include "mbm/drawable_ground.h"
#include "mbm/drawable_legend.h"
#include "mbm/drawable_moon.h"
#include "mbm/drawable_turret.h"
#include "mbm/drawables.h"
#include "mbm/drawing.h"
#include "mbm/fonts.h"
#include "mbm/fsm.h"
#include "mbm/levels.h"
#include "mbm/renderer.h"
#include "mbm/scene.h"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_filesystem.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "mbm/spritesheet.h"
#include "mbm/timing.h"
#include "mbm/types.h"
#include "mbm/window.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void sdl_init (void);

static void sdl_init (void) {
    int flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(flags) != 0) {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
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

    char * basepath = SDL_GetBasePath();

    deinit_prepare_all(&drawables.balloons, &drawables.bullets, &drawables.collisions,
                       &drawing.renderer, &drawing.window, &drawing.spritesheet, &drawing.fonts,
                       &chunks);

    sdl_init();
    level = levels_get_level(LEVEL_NOVICE);
    counters = counters_init(level);
    drawing = drawing_init(basepath);
    drawables = drawables_init(drawing.scene);
    timing = timing_init();
    chunks = chunks_init(basepath);

    levels_reset_level(level, drawing, &drawables, &counters);

    gamestate = fsm_gamestate_get(GAMESTATE_STARTING);
    frame = gamestate;
    tnow = SDL_GetTicks64();
    tstart = tnow;

    nframes = 0;

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
