#include <stdlib.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "constants.h"
#include "fsm.h"
#include "s_playing.h"
#include "s_level_finished.h"
#include "levels.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_barrel.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"

static void s_level_finished_draw_keymap_middle_top(ctx_t *);
static void s_level_finished_draw_keymap_proceed(ctx_t *);
static void s_level_finished_draw_keymap_repeat_action(ctx_t *);
static void s_level_finished_draw_keymap_repeat_button(ctx_t *);
static void s_level_finished_draw_title (ctx_t *);

static bool next_unlocked;
static bool next_exists;

void s_level_finished_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_legend_draw(ctx);
    o_ground_draw(ctx);
    s_level_finished_draw_title(ctx);
    s_level_finished_draw_keymap_proceed(ctx);
    s_level_finished_draw_keymap_repeat_button(ctx);
    s_level_finished_draw_keymap_repeat_action(ctx);
    s_level_finished_draw_keymap_middle_top(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_level_finished_draw_keymap_middle_top(ctx_t * ctx) {
    if (ctx->nhit >= ctx->level->nproceed) {
        // player has enough hits to proceed
        return;
    }
    if (!next_exists) {
        // there is no next level
        return;
    }
    char str[100];
    sprintf(str, "HIT %d TO PROCEED TO NEXT LEVEL", ctx->level->nproceed);
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, str, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on level finished screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT - 2 * GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_level_finished_draw_keymap_proceed(ctx_t * ctx) {
    SDL_Color color;
    int c = next_exists << 1 | next_unlocked;
    switch (c) {
        case 0: {
            // next level doesnt exist, dont show anything
            break;
        }
        case 1: {
            // next level doesnt exist, dont show anything
            break;
        }
        case 2: {
            // level exists but is locked
            color = ctx->colors.middlegray;
            break;
        }
        case 3: {
            // level exists and is unlocked
            color = ctx->colors.lightgray;
            break;
        }
        default: {
            SDL_LogError(SDL_UNSUPPORTED, "Something went wrong with determining the next level: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }
    {
        char keymap[7] = "RETURN";
        SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.doppel, keymap, color, ctx->colors.bg);
        SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
        if (txre.invalid) {
            SDL_LogError(SDL_ENOMEM, "Error creating the proceed button keymap on level finished screen: %s.\n", TTF_GetError());
        }
        SDL_Rect tgt = {
            .x = 6 * SCREEN_WIDTH / 7 - surf.payload->w / 2,
            .y = SCREEN_HEIGHT / 2 - surf.payload->h / 2,
            .w = surf.payload->w,
            .h = surf.payload->h,
        };
        SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
        SDL_DestroyTexture(txre.payload);
        SDL_FreeSurface(surf.payload);
    }
    {
        char keymap[11] = "NEXT LEVEL";
        SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, color, ctx->colors.bg);
        SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
        if (txre.invalid) {
            SDL_LogError(SDL_ENOMEM, "Error creating the proceed action keymap on level finished screen: %s.\n", TTF_GetError());
        }
        SDL_Rect tgt = {
            .x = 6 * SCREEN_WIDTH / 7 - surf.payload->w / 2,
            .y = SCREEN_HEIGHT / 2 - surf.payload->h / 2 + 40,
            .w = surf.payload->w,
            .h = surf.payload->h,
        };
        SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
        SDL_DestroyTexture(txre.payload);
        SDL_FreeSurface(surf.payload);
    }

}

static void s_level_finished_draw_keymap_repeat_action(ctx_t * ctx) {
            char keymap[13] = "REPEAT LEVEL";
            SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.lightgray, ctx->colors.bg);
            SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
            if (txre.invalid) {
                SDL_LogError(SDL_ENOMEM, "Error creating the repeat action keymap on level finished screen: %s.\n", TTF_GetError());
            }
            SDL_Rect tgt = {
            .x = 1 * SCREEN_WIDTH / 7 - surf.payload->w / 2,
                .y = SCREEN_HEIGHT / 2 - surf.payload->h / 2 + 40,
                .w = surf.payload->w,
                .h = surf.payload->h,
            };
            SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
            SDL_DestroyTexture(txre.payload);
            SDL_FreeSurface(surf.payload);
}

static void s_level_finished_draw_keymap_repeat_button(ctx_t * ctx) {
            char keymap[2] = "R";
            SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.doppel, keymap, ctx->colors.lightgray, ctx->colors.bg);
            SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
            if (txre.invalid) {
                SDL_LogError(SDL_ENOMEM, "Error creating the repeat button keymap on level finished screen: %s.\n", TTF_GetError());
            }
            SDL_Rect tgt = {
                .x = 1 * SCREEN_WIDTH / 7 - surf.payload->w / 2,
                .y = SCREEN_HEIGHT / 2 - surf.payload->h / 2,
                .w = surf.payload->w,
                .h = surf.payload->h,
            };
            SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
            SDL_DestroyTexture(txre.payload);
            SDL_FreeSurface(surf.payload);
}

static void s_level_finished_draw_title (ctx_t * ctx) {
    char title[15];
    if (ctx->nmiss == 0) {
        strncpy(title, "PERFECT SCORE!", 15);
    } else {
        strncpy(title, "LEVEL FINISHED", 15);
    }
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.large, title, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title on level finished screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT * 0.44 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

ctx_t * s_level_finished_update (ctx_t * ctx, state_t ** state) {
    if (ctx->nhit >= ctx->level->nproceed) {
        ctx->ilevel_unlocked = ctx->ilevel +  1;
    }
    next_unlocked = ctx->ilevel + 1 <= ctx->ilevel_unlocked;
    next_exists = ctx->ilevel + 1 < ctx->nlevels;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (next_unlocked && event.key.keysym.sym == SDLK_RETURN) {
                ctx->ilevel += next_exists ? 1 : 0;
                levels_set(ctx, ctx->ilevel);
                SDL_Log("playing -- next level\n");
                *state = fsm_set_state(PLAYING);
            }
            if (event.key.keysym.sym == SDLK_r) {
                levels_set(ctx, ctx->ilevel);
                SDL_Log("playing -- same level\n");
                *state = fsm_set_state(PLAYING);
            }
        }
    }
    return ctx;
}
