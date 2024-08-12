#include "mbm/fsm_playing.h"
#include "mbm/drawable_background.h"
#include "mbm/drawable_balloons.h"
#include "mbm/drawable_barrel.h"
#include "mbm/drawable_bullets.h"
#include "mbm/drawable_collisions.h"
#include "mbm/drawable_flash.h"
#include "mbm/drawable_ground.h"
#include "mbm/drawable_keymap.h"
#include "mbm/drawable_legend.h"
#include "mbm/drawable_moon.h"
#include "mbm/drawable_turret.h"
#include "mbm/fsm.h"
#include "mbm/scene.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "mbm/types.h"
#include <stdbool.h>

void fsm_playing_draw (const level_t level, const drawing_t drawing, const drawables_t drawables,
                       const counters_t counters) {

    drawable_background_draw(drawing.renderer, drawing.colors, drawing.scene);
    drawable_moon_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.moon);
    drawable_barrel_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.barrel);
    drawable_turret_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.turret);
    drawable_flash_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.barrel,
                        drawables.flash);
    drawable_legend_draw(level, drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                         drawables.legend, counters);
    drawable_balloons_draw(drawing.renderer, drawing.spritesheet, drawing.scene,
                           drawables.balloons);
    drawable_bullets_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.bullets);
    drawable_collisions_draw(drawing.renderer, drawing.spritesheet, drawing.colors, drawing.fonts,
                             drawing.scene, drawables.collisions);
    drawable_ground_draw(drawing.renderer, drawing.colors, drawing.scene, drawables.ground);
    drawable_keymap_draw_pause(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                               drawables.ground);
    drawable_keymap_draw_proceedhint(level, drawing.renderer, drawing.fonts, drawing.colors,
                                     drawing.scene, drawables.ground, counters);
    SDL_RenderPresent(drawing.renderer);
}

void fsm_playing_update (const timing_t timing, const chunks_t chunks, counters_t * counters,
                         drawing_t * drawing, drawables_t * drawables, gamestate_t ** gamestate,
                         level_t *) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        *gamestate = fsm_gamestate_get(GAMESTATE_PAUSING);
                        break;
                    }
                    case SDLK_F11: {
                        SDL_SetWindowFullscreen(
                            drawing->window,
                            drawing->scene.isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                        drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                        break;
                    }
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED: // deliberate fallthrough
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        drawing->scene.resized = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
    drawable_barrel_update(timing, &drawables->barrel);
    drawable_balloons_update(timing, drawing->scene, drawables->ground, &drawables->balloons,
                             counters);
    drawable_bullets_update(timing, drawing->scene, drawables->ground, chunks, counters,
                            &drawables->barrel, &drawables->flash, &drawables->bullets);
    drawable_flash_update(timing, &drawables->flash);
    drawable_collisions_update(timing, drawing->scene, drawables->ground, chunks,
                               drawables->balloons, drawables->bullets, counters,
                               &drawables->collisions);

    bool no_more_balloons = counters->nballoons.prespawn + counters->nballoons.airborne == 0;
    bool no_more_bullets = counters->nbullets.prespawn + counters->nbullets.airborne == 0;
    if (no_more_balloons || no_more_bullets) {
        counters->nballoons.miss += counters->nballoons.prespawn + counters->nballoons.airborne;
        counters->nballoons.prespawn = 0;
        counters->nballoons.airborne = 0;
        *gamestate = fsm_gamestate_get(GAMESTATE_FINISHING_LEVEL);
    }
}
