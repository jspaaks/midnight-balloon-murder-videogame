#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_log.h"
#include "types.h"
#include "colors.h"
#include "levels.h"
#include "o_legend.h"
#include "o_balloons.h"

static void o_legend_bars_draw (ctx_t *);
static void o_legend_nbullets_warning_draw (ctx_t *);

static void o_legend_nbullets_warning_draw (ctx_t * ctx) {
    if (ctx->nbullets < 5) {
        SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.magenta.r,
                                              ctx->colors.magenta.g,
                                              ctx->colors.magenta.b,
                                              ctx->colors.magenta.a);
    } else if (ctx->nbullets < 10) {
        SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.red.r,
                                              ctx->colors.red.g,
                                              ctx->colors.red.b,
                                              ctx->colors.red.a);
    } else if (ctx->nbullets < 20) {
        SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.orange.r,
                                              ctx->colors.orange.g,
                                              ctx->colors.orange.b,
                                              ctx->colors.orange.a);
    } else if (ctx->nbullets < 30) {
        SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.green.r,
                                              ctx->colors.green.g,
                                              ctx->colors.green.b,
                                              ctx->colors.green.a);
    } else {
        SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.bg.r,
                                              ctx->colors.bg.g,
                                              ctx->colors.bg.b,
                                              ctx->colors.bg.a);
    }
    SDL_Rect rect = {
        .x = 80,
        .y = 80,
        .w = 195,
        .h = 38,
    };
    SDL_RenderFillRect(ctx->renderer, &rect);
}

static void o_legend_bars_draw (ctx_t * ctx) {
    static const int nbars = 10;
    static int j = 0;

    int nhit = nbars * ctx->nhit / ctx->level->nballoons;
    int nmiss = nbars * ctx->nmiss / ctx->level->nballoons;
    int nmiddle = nbars - nhit - nmiss;

    SDL_Rect rect = {
        .x = 60,
        .y = 50,
        .w = 15,
        .h = 18,
    };

    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.hit.r,
                                          ctx->colors.hit.g,
                                          ctx->colors.hit.b,
                                          ctx->colors.hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        rect.x += (rect.w + 5);
        SDL_RenderFillRect(ctx->renderer, &rect);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.middle.r,
                                          ctx->colors.middle.g,
                                          ctx->colors.middle.b,
                                          ctx->colors.middle.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        rect.x += (rect.w + 5);
        SDL_RenderFillRect(ctx->renderer, &rect);
    }
    SDL_SetRenderDrawColor(ctx->renderer, ctx->colors.miss.r,
                                          ctx->colors.miss.g,
                                          ctx->colors.miss.b,
                                          ctx->colors.miss.a);
    for (int i = 0; i < nmiss; i++, j++) {
        rect.x += (rect.w + 5);
        SDL_RenderFillRect(ctx->renderer, &rect);
    }
}

void o_legend_draw (ctx_t * ctx) {
    o_legend_bars_draw(ctx);
    o_legend_nbullets_warning_draw(ctx);
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
                SDL_Log("Something went wrong with counting the balloon states.\n");
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
