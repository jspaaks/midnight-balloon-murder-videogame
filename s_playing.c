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
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

static void s_playing_draw_keymap_middle_bottom (ctx_t *);
static void s_playing_draw_keymap_middle_top (ctx_t *);

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
    s_playing_draw_keymap_middle_bottom(ctx);
    s_playing_draw_keymap_middle_top(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_playing_draw_keymap_middle_bottom (ctx_t * ctx) {
    char keymap[12] = "ESC TO PAUSE";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (ctx->scene.tgt.w - surf.payload->w) / 2,
        .y = ctx->scene.tgt.h - ctx->ground.tgt.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_playing_draw_keymap_middle_top (ctx_t * ctx) {
    SDL_Color color = ctx->colors.middlegray;
    char str[100];
    if (ctx->ilevel == ctx->nlevels - 1) {
        sprintf(str, "FINAL LEVEL");
    } else if (ctx->nmiss > ctx->level->nprespawn.ba - ctx->level->nproceed) {
        sprintf(str, "NOT ENOUGH HITS TO PROCEED TO NEXT LEVEL");
        color = ctx->colors.lightgray;
    } else if (ctx->nhit >= ctx->level->nproceed) {
        sprintf(str, "PLAYER PROCEEDS TO NEXT LEVEL!");
        color = ctx->colors.lightgray;
    } else {
        sprintf(str, "NEED %d HITS TO PROCEED TO NEXT LEVEL", ctx->level->nproceed);
    }
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, str, color, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (ctx->scene.tgt.w - surf.payload->w) / 2,
        .y = ctx->scene.tgt.h - 2 * ctx->ground.tgt.h / 3 - surf.payload->h / 2,
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
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Log("pausing\n");
                    *state = fsm_set_state(PAUSED);
                }
                break;
            }
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED: {
                ctx->resized = true;
                break;
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
            ctx = o_balloons_update_remaining_as_hit(ctx);
            ctx = o_legend_update(ctx);
            SDL_Log("No more bullets. { hit: %d, miss: %d }\n", ctx->nhit, ctx->nmiss);
        }
        SDL_Log("level finished\n");
        *state = fsm_set_state(LEVEL_FINISHED);
    }

    return ctx;
}
