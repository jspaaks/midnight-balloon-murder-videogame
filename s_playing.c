#include <stdbool.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "constants.h"
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
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

static void s_playing_draw_keymap_middle (ctx_t *);

void s_playing_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_flash_draw(ctx);
    o_legend_draw(ctx);
    o_balloons_draw(ctx);
    o_bullets_draw(ctx);
    o_collisions_draw(ctx);
    o_ground_draw(ctx);
    s_playing_draw_keymap_middle(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_playing_draw_keymap_middle (ctx_t * ctx) {
    char keymap[12] = "ESC TO PAUSE";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.lightgray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

ctx_t * s_playing_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_Log("pausing\n");
                *state = fsm_set_state(PAUSED);
            }
        }
    }
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
            SDL_Log("No more bullets. { hit: %d, miss: %d }\n", ctx->nhit, ctx->nmiss + ctx->nprespawn.ba + ctx->nairborne.ba);
        }
        SDL_Log("level finished\n");
        *state = fsm_set_state(LEVEL_FINISHED);
    }

    return ctx;
}
