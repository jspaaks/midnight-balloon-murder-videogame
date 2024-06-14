#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "fsm.h"
#include "fsm_playing.h"
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
#include "o_scene.h"
#include "o_turret.h"

void fsm_playing_draw (ctx_t * ctx, SDL_Renderer * renderer) {
    o_background_draw(renderer);
    o_scene_draw(ctx, renderer);
    o_moon_draw(ctx, renderer);
    o_barrel_draw(ctx, renderer);
    o_turret_draw(ctx, renderer);
    o_flash_draw(ctx, renderer);
    o_legend_draw(ctx, renderer);
    o_balloons_draw(ctx, renderer);
    o_bullets_draw(ctx, renderer);
    o_collisions_draw(ctx, renderer);
    o_ground_draw(ctx, renderer);
    o_keymap_draw_pause(ctx, renderer);
    o_keymap_draw_proceedhint(ctx, renderer);
    SDL_RenderPresent(renderer);
}

void fsm_playing_update (ctx_t * ctx, SDL_Renderer * renderer, gamestate_t ** gamestate) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {
                        SDL_Log("pausing\n");
                        *gamestate = fsm_gamestate_get(GAMESTATE_PAUSING);
                        break;
                    }
                    case SDLK_F11: {
                        SDL_SetWindowFullscreen(ctx->window, ctx->isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                        ctx->isfullscreen = !ctx->isfullscreen;
                        break;
                    }
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:  // fallthrough
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                         ctx->scene.resized = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    o_scene_update(ctx, renderer);
    o_barrel_update(ctx);
    o_flash_update(ctx);
    o_balloons_update(ctx);
    o_bullets_update(ctx);
    o_collisions_update(ctx);

    bool no_more_balloons = ctx->nballoons.prespawn + ctx->nballoons.airborne == 0;
    bool no_more_bullets = ctx->nbullets.prespawn + ctx->nbullets.airborne == 0;
    if (no_more_balloons || no_more_bullets) {
        ctx->nballoons.miss += ctx->nballoons.prespawn + ctx->nballoons.airborne;
        ctx->nballoons.prespawn = 0;
        ctx->nballoons.airborne = 0;
        SDL_Log("finishing level\n");
        *gamestate = fsm_gamestate_get(GAMESTATE_FINISHING_LEVEL);
    }
}
