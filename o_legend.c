#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "constants.h"
#include "types.h"
#include "colors.h"
#include "levels.h"
#include "o_legend.h"
#include "o_balloons.h"

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
    int nhit = ctx->legend.nbars * ctx->nhit / ctx->level->nballoons;
    int nmiss = ctx->legend.nbars * ctx->nmiss / ctx->level->nballoons;
    int nmiddle = ctx->legend.nbars - nhit - nmiss;
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.hit.r,
                                          ctx->colors.hit.g,
                                          ctx->colors.hit.b,
                                          ctx->colors.hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        SDL_RenderFillRect(ctx->renderer, &ctx->legend.bars[j].tgt);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.middlegray.r,
                                          ctx->colors.middlegray.g,
                                          ctx->colors.middlegray.b,
                                          ctx->colors.middlegray.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        SDL_RenderFillRect(ctx->renderer, &ctx->legend.bars[j].tgt);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.miss.r,
                                          ctx->colors.miss.g,
                                          ctx->colors.miss.b,
                                          ctx->colors.miss.a);
    for (int i = 0; i < nmiss; i++, j++) {
        SDL_RenderFillRect(ctx->renderer, &ctx->legend.bars[j].tgt);
    }
}

static void o_legend_draw_rect_nbullets (ctx_t * ctx) {
    // choose a warning color or use background color if not low on ammo
    if (ctx->nbullets < 5) {
        ctx->legend.highlight.bg = &ctx->colors.magenta;
    } else if (ctx->nbullets < 10) {
        ctx->legend.highlight.bg = &ctx->colors.red;
    } else if (ctx->nbullets < 20) {
        ctx->legend.highlight.bg = &ctx->colors.orange;
    } else if (ctx->nbullets < 30) {
        ctx->legend.highlight.bg = &ctx->colors.green;
    } else {
        ctx->legend.highlight.bg = &ctx->colors.bg;
    }

    // render the bullet count highlight rect
    SDL_SetRenderDrawColor(ctx->renderer, ctx->legend.highlight.bg->r,
                                          ctx->legend.highlight.bg->g,
                                          ctx->legend.highlight.bg->b,
                                          ctx->legend.highlight.bg->a);
    SDL_RenderFillRect(ctx->renderer, &ctx->legend.highlight.tgt);
}

static void o_legend_draw_text_hit (ctx_t * ctx) {
    char hit[4] = "HIT";

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, hit, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the hit legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the hit legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = ctx->legend.bars[0].tgt.x,
        .y = ctx->legend.bars[0].tgt.y - surf->h,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_level (ctx_t * ctx) {
    char level[30];
    sprintf(level, "%s LEVEL", ctx->level->name);

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, level, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the level legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the level legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf->w) / 2,
        .y = ctx->legend.bars[0].tgt.y + (ctx->legend.bars[0].tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_miss (ctx_t * ctx) {
    char miss[5] = "MISS";

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, miss, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the miss legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the miss legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = ctx->legend.bars[ctx->legend.nbars - 1].tgt.x + ctx->legend.bars[ctx->legend.nbars - 1].tgt.w - surf->w,
        .y = ctx->legend.bars[0].tgt.y - surf->h,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_nballoons (ctx_t * ctx) {
    char nballoons[30];
    sprintf(nballoons, "BALLOONS %d", ctx->nprespawn + ctx->nairborne);

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, nballoons, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the nballoons legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the nballoons legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = (SCREEN_WIDTH - surf->w) / 2,
        .y = ctx->legend.highlight.tgt.y + (ctx->legend.highlight.tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_nbullets (ctx_t * ctx) {
    char nbullets[30];
    sprintf(nbullets, "BULLETS %d", ctx->nbullets);

    SDL_Color color = ctx->nbullets >= 30 ? ctx->colors.lightgray : ctx->colors.white;

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, nbullets, color, *ctx->legend.highlight.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the nbullets legend caption: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the nbullets legend caption: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = ctx->legend.highlight.tgt.x + (ctx->legend.highlight.tgt.w - surf->w) / 2,
        .y = ctx->legend.highlight.tgt.y + (ctx->legend.highlight.tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_nhit (ctx_t * ctx) {
    char nhit[30];
    sprintf(nhit, "%d", ctx->nhit);

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, nhit, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the nhit legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the nhit legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = ctx->legend.bars[0].tgt.x - surf->w - 10,
        .y = ctx->legend.bars[0].tgt.y + (ctx->legend.bars[0].tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

static void o_legend_draw_text_nmiss (ctx_t * ctx) {
    char nmiss[30];
    sprintf(nmiss, "%d", ctx->nmiss);

    // render the string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, nmiss, ctx->colors.lightgray, ctx->colors.bg);
    if (surf == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a surface for the nmiss legend text: %s\n", SDL_GetError());
    }

    // create the equivalent string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the nmiss legend text: %s\n", SDL_GetError());
    }

    SDL_Rect tgt = {
        .x = ctx->legend.bars[ctx->legend.nbars - 1].tgt.x + ctx->legend.bars[ctx->legend.nbars - 1].tgt.w + 10,
        .y = ctx->legend.bars[0].tgt.y + (ctx->legend.bars[0].tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // render the string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
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

ctx_t * o_legend_init (ctx_t * ctx) {
    const unsigned int n = 10;
    ctx->legend.nbars = n;
    SDL_Rect first = {
        .x = 60,
        .y = 49,
        .w = 15,
        .h = 20,
    };
    for (unsigned int i = 0; i < ctx->legend.nbars; i++) {
        ctx->legend.bars[i].tgt = (SDL_Rect) {
            .x = first.x + i * (first.w + 5),
            .y = first.y,
            .w = first.w,
            .h = first.h,
        };
    }
    ctx->legend.highlight.tgt = (SDL_Rect) {
        .x = ctx->legend.bars[0].tgt.x,
        .y = ctx->legend.bars[0].tgt.y + ctx->legend.bars[0].tgt.h + 7,
        .w = (ctx->legend.bars[n-1].tgt.x + ctx->legend.bars[n-1].tgt.w) - ctx->legend.bars[0].tgt.x,
        .h = 40,
    };
    return ctx;
}

ctx_t * o_legend_update (ctx_t * ctx) {
    unsigned int nhit = 0;
    unsigned int nmiss = 0;
    unsigned int nprespawn = 0;
    unsigned int nairborne = 0;
    for (unsigned int i = 0; i < ctx->level->nballoons; i++) {
        switch (ctx->balloons[i].state) {
            case BA_PRESPAWN: {
                nprespawn++;
                break;
            }
            case BA_AIRBORNE: {
                nairborne++;
                break;
            }
            case BA_HIT: {
                nhit++;
                break;
            }
            case BA_MISS: {
                nmiss++;
                break;
            }
            default: {
                SDL_LogError(SDL_UNSUPPORTED, "Something went wrong with counting the balloon states.\n");
                break;
            }
        }
    }
    ctx->nprespawn = nprespawn;
    ctx->nairborne = nairborne;
    ctx->nhit = nhit;
    ctx->nmiss = nmiss;
    return ctx;
}
