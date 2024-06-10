#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "fsm.h"
#include "s_playing.h"
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

void s_playing_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_scene_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_flash_draw(ctx);
    o_legend_draw(ctx);
    o_balloons_draw(ctx);
    o_bullets_draw(ctx);
    o_collisions_draw(ctx);
    o_ground_draw(ctx);
    o_keymap_draw_pause(ctx);
    o_keymap_draw_proceedhint(ctx);
    SDL_RenderPresent(ctx->renderer);
}

ctx_t * s_playing_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Log("pausing\n");
                    *state = fsm_set_state(PAUSED);
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
    ctx = o_scene_update(ctx);
    ctx = o_ground_update(ctx);
    ctx = o_moon_update(ctx);
    ctx = o_turret_update(ctx);
    ctx = o_barrel_update(ctx);
    ctx = o_flash_update(ctx);
    ctx = o_balloons_update(ctx);
    ctx = o_bullets_update(ctx);
    ctx = o_collisions_update(ctx);
    ctx = o_legend_update(ctx);

    bool no_more_balloons = ctx->nprespawn.ba + ctx->nairborne.ba == 0;
    bool no_more_bullets = ctx->nprespawn.bu + ctx->nairborne.bu == 0;
    if (no_more_balloons || no_more_bullets) {
        if (no_more_balloons) {
            SDL_Log("No more balloons. { hit: %d, miss: %d }\n", ctx->nhit, ctx->nmiss);
        }
        if (no_more_bullets) {
            ctx = o_balloons_update_remaining_as_hit(ctx);
            ctx = o_legend_update(ctx);
            SDL_Log("No more bullets. { hit: %d, miss: %d }\n", ctx->nhit, ctx->nmiss);
        }
        SDL_Log("level finished\n");
        *state = fsm_set_state(LEVEL_FINISHED);
    }

    return ctx;
}
