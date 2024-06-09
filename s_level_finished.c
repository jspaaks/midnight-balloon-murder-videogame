#include <stdlib.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "fsm.h"
#include "s_playing.h"
#include "s_level_finished.h"
#include "levels.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_barrel.h"
#include "o_ground.h"
#include "o_keymap.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_scene.h"
#include "o_titles.h"
#include "o_turret.h"

static void s_level_finished_draw_keymap_proceed(ctx_t *);
static void s_level_finished_draw_keymap_repeat_action(ctx_t *);
static void s_level_finished_draw_keymap_repeat_button(ctx_t *);

static bool next_unlocked;
static bool next_exists;

void s_level_finished_draw (ctx_t * ctx) {
    o_background_draw(ctx);
    o_scene_draw(ctx);
    o_moon_draw(ctx);
    o_turret_draw(ctx);
    o_barrel_draw(ctx);
    o_legend_draw(ctx);
    o_ground_draw(ctx);
    o_keymap_draw_proceedhint(ctx);
    o_titles_draw_level_finished(ctx);
    s_level_finished_draw_keymap_proceed(ctx);
    s_level_finished_draw_keymap_repeat_button(ctx);
    s_level_finished_draw_keymap_repeat_action(ctx);
    SDL_RenderPresent(ctx->renderer);
}

static void s_level_finished_draw_keymap_proceed(ctx_t * ctx) {
    SDL_Color color;
    int c = next_exists << 1 | next_unlocked;
    switch (c) {
        case 0: {
            // next level doesnt exist, dont show anything
            return;
        }
        case 1: {
            // next level doesnt exist, dont show anything
            return;
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
        SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.large, keymap, color, ctx->colors.bg);
        SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
        if (txre.invalid) {
            SDL_LogError(SDL_ENOMEM, "Error creating the proceed button keymap on level finished screen: %s.\n", TTF_GetError());
        }
        SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
            .x = 6 * ctx->scene.sim.w / 7 - surf.payload->w / 2,
            .y = ctx->scene.sim.h / 2 - surf.payload->h / 2,
            .w = surf.payload->w,
            .h = surf.payload->h,
        });
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
        SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
            .x = 6 * ctx->scene.sim.w / 7 - surf.payload->w / 2,
            .y = ctx->scene.sim.h / 2 - surf.payload->h / 2 + 30,
            .w = surf.payload->w,
            .h = surf.payload->h,
        });
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
            SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
                .x = 1 * ctx->scene.sim.w / 7 - surf.payload->w / 2,
                .y = ctx->scene.sim.h / 2 - surf.payload->h / 2 + 30,
                .w = surf.payload->w,
                .h = surf.payload->h,
            });
            SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
            SDL_DestroyTexture(txre.payload);
            SDL_FreeSurface(surf.payload);
}

static void s_level_finished_draw_keymap_repeat_button(ctx_t * ctx) {
            char keymap[2] = "R";
            SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.large, keymap, ctx->colors.lightgray, ctx->colors.bg);
            SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
            if (txre.invalid) {
                SDL_LogError(SDL_ENOMEM, "Error creating the repeat button keymap on level finished screen: %s.\n", TTF_GetError());
            }
            SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
                .x = 1 * ctx->scene.sim.w / 7 - surf.payload->w / 2,
                .y = ctx->scene.sim.h / 2 - surf.payload->h / 2,
                .w = surf.payload->w,
                .h = surf.payload->h,
            });
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
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (next_unlocked && event.key.keysym.sym == SDLK_RETURN) {
                    ctx->ilevel += next_exists ? 1 : 0;
                    levels_set(ctx, ctx->ilevel);
                    SDL_Log("playing -- next level\n");
                    *state = fsm_set_state(PLAYING);
                } else if (event.key.keysym.sym == SDLK_r) {
                    levels_set(ctx, ctx->ilevel);
                    SDL_Log("playing -- same level\n");
                    *state = fsm_set_state(PLAYING);
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_Log("resize\n");
                    ctx->scene.resized = true;
                }
                break;
            }
        }
    }
    ctx = o_scene_update(ctx);
    ctx = o_ground_update(ctx);
    ctx = o_moon_update(ctx);
    return ctx;
}
