#include "o_legend.h"
#include <stdio.h>
#include "levels.h"
#include "o_balloons.h"
#include "colors.h"
#include "types.h"

static void o_legend_bars_draw (ctx_t *);
static void o_legend_nbullets_warning_draw (ctx_t *);

static void o_legend_nbullets_warning_draw (ctx_t * ctx) {
    static const rgba_t magenta = { .r = 200, .g =   0, .b = 255, .a = 0 };
    static const rgba_t red     = { .r = 200, .g =   0, .b =   0, .a = 0 };
    static const rgba_t orange  = { .r = 200, .g = 161, .b =   0, .a = 0 };
    static const rgba_t green   = { .r =   0, .g = 161, .b =   0, .a = 0 };
    static const rgba_t bgcolor = { .r =   0, .g =  22, .b =  43, .a = 0 };
    if (ctx->nbullets < 5) {
        SDL_SetRenderDrawColor(ctx->renderer, magenta.r, magenta.g, magenta.b, magenta.a);
    } else if (ctx->nbullets < 10) {
        SDL_SetRenderDrawColor(ctx->renderer, red.r, red.g, red.b, red.a);
    } else if (ctx->nbullets < 20) {
        SDL_SetRenderDrawColor(ctx->renderer, orange.r, orange.g, orange.b, orange.a);
    } else if (ctx->nbullets < 30) {
        SDL_SetRenderDrawColor(ctx->renderer, green.r, green.g, green.b, green.a);
    } else {
        SDL_SetRenderDrawColor(ctx->renderer, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
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
    static const rgba_t hit    = { .r =   0, .g = 161, .b =   0, .a = 0 };
    static const rgba_t middle = { .r = 128, .g = 128, .b = 128, .a = 0 };
    static const rgba_t miss   = { .r = 200, .g =   0, .b =   0, .a = 0 };
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

    SDL_SetRenderDrawColor(ctx->renderer, hit.r, hit.g, hit.b, hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        rect.x += (rect.w + 5);
        SDL_RenderFillRect(ctx->renderer, &rect);
    }
    SDL_SetRenderDrawColor(ctx->renderer, middle.r, middle.g, middle.b, middle.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        rect.x += (rect.w + 5);
        SDL_RenderFillRect(ctx->renderer, &rect);
    }
    SDL_SetRenderDrawColor(ctx->renderer, miss.r, miss.g, miss.b, miss.a);
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
            case PRESPAWN: {
                nprespawn++;
                break;
            }
            case AIRBORNE: {
                nairborne++;
                break;
            }
            case HIT: {
                nhit++;
                break;
            }
            case MISS: {
                nmiss++;
                break;
            }
            default: {
                fprintf(stderr, "Something went wrong with counting the balloon states.\n");
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
