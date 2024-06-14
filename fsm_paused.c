#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
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

void fsm_paused_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_scene_draw(ctx);
    o_moon_draw(ctx);
    o_barrel_draw(ctx);
    o_turret_draw(ctx);
    o_flash_draw(ctx);
    o_legend_draw(ctx);
    o_balloons_draw(ctx);
    o_bullets_draw(ctx);
    o_collisions_draw(ctx);
    o_ground_draw(ctx);
    o_keymap_draw_move_barrel(ctx);
    o_keymap_draw_shoot(ctx);
    o_keymap_draw_proceedhint (ctx);
    o_keymap_draw_unpause(ctx);
    o_keymap_draw_restart(ctx);
    o_keymap_draw_quit(ctx);
    o_titles_draw_paused(ctx);
    SDL_RenderPresent(ctx->renderer);
}

void fsm_paused_update (ctx_t * ctx, gamestate_t ** gamestate) {
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
                    if (ctx->nballoons.prespawn < ctx->level->nballoons.prespawn || ctx->nbullets.prespawn < ctx->level->nbullets.prespawn ) {
                        SDL_Log("restarting level\n");
                        levels_set(ctx, ctx->ilevel);
                        *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                    }
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(ctx->window, ctx->isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    ctx->isfullscreen = !ctx->isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    ctx->scene.resized = true;
                }
                break;
            }
        }
    }
    o_scene_update(ctx);
}
