#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "constants.h"
#include "types.h"
#include "fsm.h"
#include "wrapped.h"
#include "s_paused.h"
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

static void s_paused_draw_keymap_left_bottom_action (ctx_t *);
static void s_paused_draw_keymap_left_bottom_button (ctx_t *);
static void s_paused_draw_keymap_left_top_action (ctx_t *);
static void s_paused_draw_keymap_left_top_button (ctx_t *);
static void s_paused_draw_keymap_middle (ctx_t *);
static void s_paused_draw_keymap_right (ctx_t *);
static void s_paused_draw_title (ctx_t *);

void s_paused_draw (ctx_t * ctx) {
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
    s_paused_draw_keymap_left_bottom_action (ctx);
    s_paused_draw_keymap_left_bottom_button (ctx);
    s_paused_draw_keymap_left_top_action (ctx);
    s_paused_draw_keymap_left_top_button (ctx);
    s_paused_draw_keymap_middle(ctx);
    s_paused_draw_keymap_right(ctx);
    s_paused_draw_title(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_paused_draw_keymap_left_bottom_action (ctx_t * ctx) {
    char action[6] = "SHOOT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, action, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 + 3,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_paused_draw_keymap_left_bottom_button (ctx_t * ctx) {
    char button[6] = "SPACE";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, button, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 - surf.payload->w - 3,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_paused_draw_keymap_left_top_action (ctx_t * ctx) {
    char action[12] = "MOVE BARREL";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, action, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 + 3,
        .y = SCREEN_HEIGHT - 2 * GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_paused_draw_keymap_left_top_button (ctx_t * ctx) {
    char button[6] = "W / S";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, button, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 - surf.payload->w - 3,
        .y = SCREEN_HEIGHT - 2 * GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}


static void s_paused_draw_keymap_middle (ctx_t * ctx) {
    char keymap[15] = "ESC TO UNPAUSE";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
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

static void s_paused_draw_keymap_right (ctx_t * ctx) {
    char keymap[10] = "Q TO QUIT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the right keymap on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = SCREEN_WIDTH - ctx->turret.tgt.x - ctx->turret.tgt.w / 2 - surf.payload->w / 2,
        .y = SCREEN_HEIGHT - GROUND_HEIGHT / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void s_paused_draw_title (ctx_t * ctx) {
    char title[7] = "PAUSED";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.large, title, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf.payload->w) / 2,
        .y = SCREEN_HEIGHT * 0.31,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

ctx_t * s_paused_update (ctx_t * ctx, state_t ** state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_Log("playing\n");
                *state = fsm_set_state(PLAYING);
            }
            if (event.key.keysym.sym == SDLK_q) {
                SDL_Log("quitting\n");
                exit(EXIT_SUCCESS);
            }
        }
    }
    return ctx;
}
