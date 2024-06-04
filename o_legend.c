#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "types.h"
#include "colors.h"
#include "levels.h"
#include "o_legend.h"
#include "o_balloons.h"

static void o_legend_bars_draw (ctx_t *);
static void o_legend_nbullets_warning_draw (ctx_t *);

static void o_legend_nbullets_warning_draw (ctx_t * ctx) {

    static SDL_Color * bgcolor = NULL;
    static char str[30];
    static SDL_Rect rect = {
        .x = 80,
        .y = 80,
        .w = 195,
        .h = 38,
    };

    // choose a warning color or use background color if not low on ammo
    if (ctx->nbullets < 5) {
        bgcolor = &ctx->colors.magenta;
    } else if (ctx->nbullets < 10) {
        bgcolor = &ctx->colors.red;
    } else if (ctx->nbullets < 20) {
        bgcolor = &ctx->colors.orange;
    } else if (ctx->nbullets < 30) {
        bgcolor = &ctx->colors.green;
    } else {
        bgcolor = &ctx->colors.bg;
    }

    // render the bullet count highlight rect
    SDL_SetRenderDrawColor(ctx->renderer, bgcolor->r,
                                          bgcolor->g,
                                          bgcolor->b,
                                          bgcolor->a);
    SDL_RenderFillRect(ctx->renderer, &rect);

    // make the bullet count string
    sprintf(str, "bullets %d", ctx->nbullets);

    // render the bullet string to a surface
    SDL_Surface * text = TTF_RenderText_Shaded(ctx->font, str, ctx->colors.white, *bgcolor);
    SDL_Rect txt_tgt = {
        .x = rect.x + (rect.w - text->w) / 2,
        .y = rect.y + (rect.h - text->h) / 2,
        .w = text->w,
        .h = text->h,
    };

    // create the equivalent bullet string texture
    SDL_Texture * message = SDL_CreateTextureFromSurface(ctx->renderer, text);

    // render the bullet count string texture
    SDL_RenderCopy(ctx->renderer, message, NULL, &txt_tgt);
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
