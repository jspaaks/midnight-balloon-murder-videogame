#include "mbm/fsm_paused.h"
#include "mbm/deinit.h"
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
#include "mbm/drawable_titles.h"
#include "mbm/drawable_turret.h"
#include "mbm/fsm.h"
#include "mbm/levels.h"
#include "mbm/scene.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "mbm/types.h"
#include <stdbool.h>

void fsm_paused_draw (const level_t level, const drawing_t drawing, const drawables_t drawables,
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
    drawable_keymap_draw_move_barrel(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                                     drawables.turret, drawables.ground);
    drawable_keymap_draw_shoot(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                               drawables.turret, drawables.ground);
    drawable_keymap_draw_proceedhint(level, drawing.renderer, drawing.fonts, drawing.colors,
                                     drawing.scene, drawables.ground, counters);
    drawable_keymap_draw_unpause(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                                 drawables.ground);
    drawable_keymap_draw_restart(level, drawing.renderer, drawing.fonts, drawing.colors,
                                 drawing.scene, drawables.turret, drawables.ground, counters);
    drawable_keymap_draw_quit(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                              drawables.turret, drawables.ground);
    drawable_titles_draw_paused(drawing.renderer, drawing.fonts, drawing.colors, drawing.scene);
    SDL_RenderPresent(drawing.renderer);
}

void fsm_paused_update (const timing_t, const chunks_t, counters_t * counters, drawing_t * drawing,
                        drawables_t * drawables, gamestate_t ** gamestate, level_t * level) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_q) {
                    deinit();
                } else if (event.key.keysym.sym == SDLK_r) {
                    if (counters->nballoons.prespawn < level->nballoons.prespawn ||
                        counters->nbullets.prespawn < level->nbullets.prespawn) {
                        levels_reset_level(*level, *drawing, drawables, counters);
                        *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                    }
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(drawing->window, drawing->scene.isfullscreen
                                                                 ? 0
                                                                 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    drawing->scene.resized = true;
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
}
