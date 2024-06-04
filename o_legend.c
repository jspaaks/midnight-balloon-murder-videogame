#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "types.h"
#include "colors.h"
#include "levels.h"
#include "o_legend.h"
#include "o_balloons.h"

static void o_legend_draw_bars (ctx_t *);
static void o_legend_draw_bullet_count_bg (ctx_t *);
static void o_legend_draw_bullet_count_text (ctx_t *);

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
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.middle.r,
                                          ctx->colors.middle.g,
                                          ctx->colors.middle.b,
                                          ctx->colors.middle.a);
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

static void o_legend_draw_bullet_count_bg (ctx_t * ctx) {
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

static void o_legend_draw_bullet_count_text (ctx_t * ctx) {
    static char str[30];
    // make the bullet count string
    sprintf(str, "bullets %d", ctx->nbullets);

    // render the bullet string to a surface
    SDL_Surface * surf = TTF_RenderText_Shaded(ctx->font, str, ctx->colors.white, *ctx->legend.highlight.bg);

    SDL_Rect tgt = {
        .x = ctx->legend.highlight.tgt.x + (ctx->legend.highlight.tgt.w - surf->w) / 2,
        .y = ctx->legend.highlight.tgt.y + (ctx->legend.highlight.tgt.h - surf->h) / 2,
        .w = surf->w,
        .h = surf->h,
    };

    // create the equivalent bullet string texture
    SDL_Texture * txre = SDL_CreateTextureFromSurface(ctx->renderer, surf);
    if (txre == NULL) {
        SDL_LogError(SDL_ENOMEM, "Error creating a texture for the nbullet legend caption: %s\n", SDL_GetError());
    }

    // render the bullet count string texture
    SDL_RenderCopy(ctx->renderer, txre, NULL, &tgt);

    // clean up resources
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
}

void o_legend_draw (ctx_t * ctx) {
    o_legend_draw_bars(ctx);
    o_legend_draw_bullet_count_bg(ctx);
    o_legend_draw_bullet_count_text(ctx);
}

ctx_t * o_legend_init (ctx_t * ctx) {
    const int n = 10;
    ctx->legend.nbars = n;
    SDL_Rect first = {
        .x = 40,
        .y = 40,
        .w = 15,
        .h = 18,
    };
    for (int i = 0; i < ctx->legend.nbars; i++) {
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
    ctx->legend.bg.tgt = (SDL_Rect) {
        .x = ctx->legend.bars[0].tgt.x,
        .y = ctx->legend.bars[0].tgt.y,
        .w = ctx->legend.highlight.tgt.w,
        .h = (ctx->legend.highlight.tgt.y + ctx->legend.highlight.tgt.h) - ctx->legend.bars[0].tgt.y,
    };
    SDL_Log("{ ctx->legend.highlight.tgt.x: %d }\n", ctx->legend.highlight.tgt.x);
    return ctx;
}

ctx_t * o_legend_update (ctx_t * ctx) {
    int nhit = 0;
    int nmiss = 0;
    int nprespawn = 0;
    int nairborne = 0;
    for (int i = 0; i < ctx->level->nballoons; i++) {
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
