#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "types.h"
#include "colors.h"
#include "levels.h"
#include "o_legend.h"
#include "o_balloons.h"
#include "o_scene.h"
#include "wrapped.h"

static void o_legend_draw_bars (ctx_t *);
static void o_legend_draw_rect_nbullets (ctx_t *);
static void o_legend_draw_text_hit (ctx_t *);
static void o_legend_draw_text_level (ctx_t *);
static void o_legend_draw_text_miss (ctx_t *);
static void o_legend_draw_text_nballoons (ctx_t *);
static void o_legend_draw_text_nbullets (ctx_t *);
static void o_legend_draw_text_nhit (ctx_t *);
static void o_legend_draw_text_nmiss (ctx_t *);

static void o_legend_draw_bars (ctx_t * ctx) {
    int j = 0;
    int nhit = ctx->legend.nbars * ctx->nballoons.hit / ctx->level->nballoons.prespawn;
    int nmiss = ctx->legend.nbars * ctx->nballoons.miss / ctx->level->nballoons.prespawn;
    int nmiddle = ctx->legend.nbars - nhit - nmiss;
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.hit.r,
                                          ctx->colors.hit.g,
                                          ctx->colors.hit.b,
                                          ctx->colors.hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        SDL_Rect tgt = sim2tgt(ctx->scene, ctx->legend.bars[j].sim);
        SDL_RenderFillRect(ctx->renderer, &tgt);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.middlegray.r,
                                          ctx->colors.middlegray.g,
                                          ctx->colors.middlegray.b,
                                          ctx->colors.middlegray.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        SDL_Rect tgt = sim2tgt(ctx->scene, ctx->legend.bars[j].sim);
        SDL_RenderFillRect(ctx->renderer, &tgt);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.miss.r,
                                          ctx->colors.miss.g,
                                          ctx->colors.miss.b,
                                          ctx->colors.miss.a);
    for (int i = 0; i < nmiss; i++, j++) {
        SDL_Rect tgt = sim2tgt(ctx->scene, ctx->legend.bars[j].sim);
        SDL_RenderFillRect(ctx->renderer, &tgt);
    }
}

static void o_legend_draw_rect_nbullets (ctx_t * ctx) {
    // choose a warning color or use background color if not low on ammo
    if (ctx->nbullets.prespawn < 5) {
        ctx->legend.highlight.bg = &ctx->colors.magenta;
    } else if (ctx->nbullets.prespawn < 10) {
        ctx->legend.highlight.bg = &ctx->colors.red;
    } else if (ctx->nbullets.prespawn < 20) {
        ctx->legend.highlight.bg = &ctx->colors.orange;
    } else if (ctx->nbullets.prespawn < 30) {
        ctx->legend.highlight.bg = &ctx->colors.green;
    } else {
        ctx->legend.highlight.bg = &ctx->colors.bg;
    }

    // render the bullet count highlight rect
    SDL_SetRenderDrawColor(ctx->renderer, ctx->legend.highlight.bg->r,
                                          ctx->legend.highlight.bg->g,
                                          ctx->legend.highlight.bg->b,
                                          ctx->legend.highlight.bg->a);
    SDL_Rect tgt = sim2tgt(ctx->scene, ctx->legend.highlight.sim);
    SDL_RenderFillRect(ctx->renderer, &tgt);
}

static void o_legend_draw_text_hit (ctx_t * ctx) {
    static const char hit[4] = "HIT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, hit, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the hit legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = ctx->legend.bars[0].sim.x,
        .y = ctx->legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_level (ctx_t * ctx) {
    char level[30];
    sprintf(level, "%s LEVEL", ctx->level->name);
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, level, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the level legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = 2 * ctx->scene.sim.w / 4 - surf.payload->w / 2,
        .y = ctx->legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_miss (ctx_t * ctx) {
    static const char miss[5] = "MISS";
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, miss, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the miss legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = ctx->legend.bars[ctx->legend.nbars - 1].sim.x + ctx->legend.bars[ctx->legend.nbars - 1].sim.w - surf.payload->w,
        .y = ctx->legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nballoons (ctx_t * ctx) {
    int nremaining = ctx->nballoons.prespawn + ctx->nballoons.airborne;
    if (nremaining == 0) {
        // we're in the level finished screen
        return;
    }
    char nballoons[30];
    sprintf(nballoons, "BALLOONS %d / %d", nremaining, ctx->level->nballoons.prespawn);
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, nballoons, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nballoons legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = 3 * ctx->scene.sim.w / 4 - surf.payload->w / 2,
        .y = ctx->legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nbullets (ctx_t * ctx) {
    char nbullets[30];
    sprintf(nbullets, "BULLETS %d", ctx->nbullets.prespawn);
    SDL_Color color = ctx->nbullets.prespawn >= 30 ? ctx->colors.lightgray : ctx->colors.white;
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, nbullets, color, *ctx->legend.highlight.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nbullets legend caption.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = ctx->legend.highlight.sim.x + (ctx->legend.highlight.sim.w - surf.payload->w) / 2,
        .y = ctx->legend.highlight.sim.y + (ctx->legend.highlight.sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nhit (ctx_t * ctx) {
    char nhit[30];
    sprintf(nhit, "%d", ctx->nballoons.hit);
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, nhit, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nhit legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = ctx->legend.bars[0].sim.x - surf.payload->w - 10,
        .y = ctx->legend.bars[0].sim.y + (ctx->legend.bars[0].sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nmiss (ctx_t * ctx) {
    char nmiss[30];
    sprintf(nmiss, "%d", ctx->nballoons.miss);
    SDLW_Surface surf = TTFW_RenderText_Shaded(ctx->fonts.regular, nmiss, ctx->colors.lightgray, ctx->colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nmiss legend text.\n");
    }
    SDL_Rect tgt = sim2tgt(ctx->scene, (SDL_FRect){
        .x = ctx->legend.bars[ctx->legend.nbars - 1].sim.x + ctx->legend.bars[ctx->legend.nbars - 1].sim.w + 10,
        .y = ctx->legend.bars[0].sim.y + (ctx->legend.bars[0].sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(ctx->renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_legend_draw (ctx_t * ctx) {
    o_legend_draw_bars(ctx);
    o_legend_draw_rect_nbullets(ctx);
    o_legend_draw_text_nbullets(ctx);
    o_legend_draw_text_hit(ctx);
    o_legend_draw_text_miss(ctx);
    o_legend_draw_text_nhit(ctx);
    o_legend_draw_text_nmiss(ctx);
    o_legend_draw_text_nballoons(ctx);
    o_legend_draw_text_level(ctx);
}

void o_legend_init (ctx_t * ctx) {
    const unsigned int n = 10;
    ctx->legend.nbars = n;
    SDL_Rect first = {
        .x = 60,
        .y = 55,
        .w = 15,
        .h = 20,
    };
    for (unsigned int i = 0; i < ctx->legend.nbars; i++) {
        ctx->legend.bars[i].sim = (SDL_FRect) {
            .x = first.x + i * (first.w + 5),
            .y = first.y,
            .w = first.w,
            .h = first.h,
        };
    }
    ctx->legend.highlight.sim = (SDL_FRect) {
        .x = ctx->legend.bars[0].sim.x,
        .y = ctx->legend.bars[0].sim.y + ctx->legend.bars[0].sim.h + 7,
        .w = (ctx->legend.bars[n-1].sim.x + ctx->legend.bars[n-1].sim.w) - ctx->legend.bars[0].sim.x,
        .h = 40,
    };
}
