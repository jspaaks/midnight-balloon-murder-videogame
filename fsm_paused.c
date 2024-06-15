#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"
#include "fsm.h"
#include "o_keymap.h"
#include "levels.h"
#include "wrapped.h"
#include "fsm_paused.h"
#include "o_background.h"
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
#include "o_titles.h"

void fsm_paused_draw (ctx_t ctx, drawing_t drawing, drawables_t drawables, counters_t counters) {

    o_background_draw(drawing.renderer);

    o_scene_draw(drawing.renderer,
                 drawing.scene,
                 drawing.colors);

    o_moon_draw(drawing.renderer,
                drawing.scene,
                drawing.spritesheet,
                drawables.moon);

    o_barrel_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.barrel);

    o_turret_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.turret);

    o_flash_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.barrel,
                  drawables.flash);

    o_legend_draw(ctx,
                  drawing.renderer,
                  drawing.scene,
                  drawing.fonts,
                  drawing.colors,
                  drawables.legend,
                  counters);

    o_balloons_draw(drawing.renderer,
                    drawing.scene,
                    drawing.spritesheet,
                    drawables.balloons);

    o_bullets_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.bullets);

    o_collisions_draw(drawing.renderer,
                  drawing.scene,
                  drawing.spritesheet,
                  drawables.collisions);

    o_ground_draw(drawing.renderer,
                  drawing.scene,
                  drawing.colors,
                  drawables.ground);

    o_keymap_draw_move_barrel(drawing.renderer,
                              drawing.scene,
                              drawing.fonts,
                              drawing.colors,
                              drawables.turret,
                              drawables.ground);

    o_keymap_draw_shoot(drawing.renderer,
                        drawing.scene,
                        drawing.fonts,
                        drawing. colors,
                        drawables.turret,
                        drawables.ground);

    o_keymap_draw_proceedhint(ctx,
                              counters,
                              drawing.renderer,
                              drawing.scene,
                              drawing.fonts,
                              drawing.colors,
                              drawables.ground);

    o_keymap_draw_unpause(drawing.renderer,
                          drawing.scene,
                          drawing.fonts,
                          drawing.colors,
                          drawables.ground);

    o_keymap_draw_restart(ctx,
                          counters,
                          drawing.renderer,
                          drawing.scene,
                          drawing.fonts,
                          drawing.colors,
                          drawables.turret,
                          drawables.ground);

    o_keymap_draw_quit(drawing.renderer,
                       drawing.scene,
                       drawing.fonts,
                       drawing.colors,
                       drawables.turret,
                       drawables.ground);

    o_titles_draw_paused(drawing.renderer,
                         drawing.scene,
                         drawing.fonts,
                         drawing.colors);

    SDL_RenderPresent(drawing.renderer);
}

void fsm_paused_update (timing_t, counters_t * counters, ctx_t * ctx, SDL_Window * window, drawing_t * drawing, drawables_t * drawables, gamestate_t ** gamestate) {
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
                        levels_set(ctx, counters, ctx->ilevel, drawing, drawables);
                        *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                    }
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(window, ctx->isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    ctx->isfullscreen = !ctx->isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    ctx->resized = true;
                }
                break;
            }
        }
    }
    o_scene_update(ctx,
                   drawing->renderer,
                   &drawing->scene);

}
