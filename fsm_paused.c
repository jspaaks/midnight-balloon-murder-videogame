#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "fsm_paused.h"
#include "fsm.h"
#include "levels.h"
#include "scene.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_keymap.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_titles.h"
#include "o_turret.h"

void fsm_paused_draw (ctx_t ctx, drawing_t drawing, drawables_t drawables, counters_t counters) {

    o_background_draw(drawing.renderer, drawing.colors, drawing.scene);

    o_moon_draw(drawing.renderer,
                drawing.spritesheet,
                drawing.scene,
                drawables.moon);

    o_barrel_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.barrel);

    o_turret_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.turret);

    o_flash_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.barrel,
                  drawables.flash);

    o_legend_draw(ctx,
                  drawing.renderer,
                  drawing.fonts,
                  drawing.colors,
                  drawing.scene,
                  drawables.legend,
                  counters);

    o_balloons_draw(drawing.renderer,
                    drawing.spritesheet,
                    drawing.scene,
                    drawables.balloons);

    o_bullets_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.bullets);

    o_collisions_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.collisions);

    o_ground_draw(drawing.renderer,
                  drawing.colors,
                  drawing.scene,
                  drawables.ground);

    o_keymap_draw_move_barrel(drawing.renderer,
                              drawing.fonts,
                              drawing.colors,
                              drawing.scene,
                              drawables.turret,
                              drawables.ground);

    o_keymap_draw_shoot(drawing.renderer,
                        drawing.fonts,
                        drawing.colors,
                        drawing.scene,
                        drawables.turret,
                        drawables.ground);

    o_keymap_draw_proceedhint(ctx,
                              drawing.renderer,
                              drawing.fonts,
                              drawing.colors,
                              drawing.scene,
                              drawables.ground,
                              counters);

    o_keymap_draw_unpause(drawing.renderer,
                          drawing.fonts,
                          drawing.colors,
                          drawing.scene,
                          drawables.ground);

    o_keymap_draw_restart(ctx,
                          drawing.renderer,
                          drawing.fonts,
                          drawing.colors,
                          drawing.scene,
                          drawables.turret,
                          drawables.ground,
                          counters);

    o_keymap_draw_quit(drawing.renderer,
                       drawing.fonts,
                       drawing.colors,
                       drawing.scene,
                       drawables.turret,
                       drawables.ground);

    o_titles_draw_paused(drawing.renderer,
                         drawing.fonts,
                         drawing.colors,
                         drawing.scene);

    SDL_RenderPresent(drawing.renderer);
}

void fsm_paused_update (timing_t, chunks_t, counters_t * counters, ctx_t * ctx, drawing_t * drawing, drawables_t * drawables, gamestate_t ** gamestate) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Log("playing\n");
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_q) {
                    SDL_Log("quitting\n");
                    exit(EXIT_SUCCESS);
                } else if (event.key.keysym.sym == SDLK_r) {
                    if (counters->nballoons.prespawn < ctx->level->nballoons.prespawn || counters->nbullets.prespawn < ctx->level->nbullets.prespawn ) {
                        SDL_Log("restarting level\n");
                        levels_set(drawing->scene, ctx->ilevel, ctx, counters, drawables);
                        *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                    }
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(drawing->window, drawing->scene.isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    drawing->scene.resized = true;
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
}
