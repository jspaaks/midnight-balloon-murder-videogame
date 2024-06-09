#include <stdio.h>
#include "SDL_log.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "types.h"
#include "wrapped.h"
#include "o_keymap.h"
#include "o_scene.h"

void o_keymap_draw_move_barrel (ctx_t * ctx) {
    char action[21] = "W / S TO MOVE BARREL";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, action, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 - surf.payload->w / 2,
        .y = ctx->scene.tgt.h - 2 * ctx->ground.tgt.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_keymap_draw_pause (ctx_t * ctx) {
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

void o_keymap_draw_proceedhint (ctx_t * ctx) {
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

void o_keymap_draw_quit (ctx_t * ctx) {
    char keymap[10] = "Q TO QUIT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the right bottom keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->scene.tgt.w - ctx->turret.tgt.x - ctx->turret.tgt.w / 2 - surf.payload->w / 2,
        .y = ctx->scene.tgt.h - ctx->ground.tgt.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_keymap_draw_restart (ctx_t * ctx) {
    if (ctx->nprespawn.ba == ctx->level->nprespawn.ba && ctx->nprespawn.bu == ctx->level->nprespawn.bu) {
        // we're effectively at the start of the level already
        return;
    }
    char keymap[19] = "R TO RESTART LEVEL";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the right top keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->scene.tgt.w - ctx->turret.tgt.x - ctx->turret.tgt.w / 2 - surf.payload->w / 2,
        .y = ctx->scene.tgt.h - 2 * ctx->ground.tgt.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_keymap_draw_shoot (ctx_t * ctx) {
    char action[15] = "SPACE TO SHOOT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, action, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = {
        .x = ctx->turret.tgt.x + ctx->turret.tgt.w / 2 - surf.payload->w / 2,
        .y = ctx->scene.tgt.h - ctx->ground.tgt.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    };
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_keymap_draw_start (ctx_t * ctx) {
    char keymap[20] = "PRESS ENTER TO PLAY";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.lightgray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n", TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = (ctx->scene.sim.w - surf.payload->w) / 2,
        .y = ctx->scene.sim.h - 2 * ctx->ground.sim.h / 3 - surf.payload->h / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_keymap_draw_unpause (ctx_t * ctx) {
    char keymap[15] = "ESC TO UNPAUSE";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, keymap, ctx->colors.middlegray, ctx->colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n", TTF_GetError());
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
