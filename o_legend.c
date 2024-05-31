#include "o_legend.h"
#include <stdio.h>
#include "levels.h"
#include "o_balloons.h"
#include "colors.h"

void o_legend_draw (ctx_t * ctx) {
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
        .h = 20,
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
