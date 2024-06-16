#include <stdio.h>
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_log.h"
#include "SDL_ttf.h"
#include "colors.h"
#include "levels.h"
#include "scene.h"
#include "types.h"
#include "wrapped.h"
#include "o_balloons.h"
#include "o_legend.h"

static void o_legend_draw_bars (level_t, SDL_Renderer *, scene_t, colors_t, legend_t, counters_t);
static void o_legend_draw_rect_nbullets (SDL_Renderer *, scene_t, colors_t, legend_t, counters_t);
static void o_legend_draw_text_hit (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t);
static void o_legend_draw_text_level (level_t, SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t);
static void o_legend_draw_text_miss (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t);
static void o_legend_draw_text_nballoons (level_t, SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t, counters_t);
static void o_legend_draw_text_nbullets (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t, counters_t);
static void o_legend_draw_text_nhit (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t, counters_t);
static void o_legend_draw_text_nmiss (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t, counters_t);
static SDL_Color o_legend_get_ammolow_bgcolor(counters_t, colors_t);

static void o_legend_draw_bars (level_t level, SDL_Renderer * renderer, scene_t scene, colors_t colors, legend_t legend, counters_t counters) {
    int j = 0;
    int nhit = legend.nbars * counters.nballoons.hit / level.nballoons.prespawn;
    int nmiss = legend.nbars * counters.nballoons.miss / level.nballoons.prespawn;
    int nmiddle = legend.nbars - nhit - nmiss;
    SDL_SetRenderDrawColor(renderer, colors.hit.r,
                                     colors.hit.g,
                                     colors.hit.b,
                                     colors.hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }

    SDL_SetRenderDrawColor(renderer, colors.middlegray.r,
                                     colors.middlegray.g,
                                     colors.middlegray.b,
                                     colors.middlegray.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }

    SDL_SetRenderDrawColor(renderer, colors.miss.r,
                                     colors.miss.g,
                                     colors.miss.b,
                                     colors.miss.a);
    for (int i = 0; i < nmiss; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }
}

static void o_legend_draw_rect_nbullets (SDL_Renderer * renderer, scene_t scene, colors_t colors, legend_t legend, counters_t counters) {
    // choose a warning color or use background color if not low on ammo
    SDL_Color color = o_legend_get_ammolow_bgcolor(counters, colors);

    // render the bullet count highlight rect
    SDL_SetRenderDrawColor(renderer, color.r,
                                     color.g,
                                     color.b,
                                     color.a);
    SDL_Rect tgt = sim2tgt(scene, legend.highlight.sim);
    SDL_RenderFillRect(renderer, &tgt);
}

static void o_legend_draw_text_hit (SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend) {
    static const char caption[4] = "HIT";
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the hit legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = legend.bars[0].sim.x,
        .y = legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_level (level_t level, SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend) {
    char caption[30];
    sprintf(caption, "%s LEVEL", level.name);
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the level legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = 2 * scene.sim.w / 4 - surf.payload->w / 2,
        .y = legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_miss (SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend) {
    static const char caption[5] = "MISS";
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the miss legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = legend.bars[legend.nbars - 1].sim.x + legend.bars[legend.nbars - 1].sim.w - surf.payload->w,
        .y = legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nballoons (level_t level, SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend, counters_t counters) {
    int nremaining = counters.nballoons.prespawn + counters.nballoons.airborne;
    if (nremaining == 0) {
        // we're in the level finished screen
        return;
    }
    char caption[30];
    sprintf(caption, "BALLOONS %d / %d", nremaining, level.nballoons.prespawn);
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nballoons legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = 3 * scene.sim.w / 4 - surf.payload->w / 2,
        .y = legend.bars[0].sim.y - surf.payload->h,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nbullets (SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend, counters_t counters) {
    char caption[30];
    sprintf(caption, "BULLETS %d", counters.nbullets.prespawn);
    SDL_Color fgcolor = counters.nbullets.prespawn >= 30 ? colors.lightgray : colors.white;
    SDL_Color bgcolor = o_legend_get_ammolow_bgcolor(counters, colors);
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, fgcolor, bgcolor);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nbullets legend caption.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = legend.highlight.sim.x + (legend.highlight.sim.w - surf.payload->w) / 2,
        .y = legend.highlight.sim.y + (legend.highlight.sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nhit (SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend, counters_t counters) {
    char caption[30];
    sprintf(caption, "%d", counters.nballoons.hit);
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nhit legend text.\n");
        exit(EXIT_FAILURE);
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = legend.bars[0].sim.x - surf.payload->w - 10,
        .y = legend.bars[0].sim.y + (legend.bars[0].sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

static void o_legend_draw_text_nmiss (SDL_Renderer * renderer, scene_t scene, fonts_t fonts, colors_t colors, legend_t legend, counters_t counters) {
    char caption[30];
    sprintf(caption, "%d", counters.nballoons.miss);
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the nmiss legend text.\n");
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
        .x = legend.bars[legend.nbars - 1].sim.x + legend.bars[legend.nbars - 1].sim.w + 10,
        .y = legend.bars[0].sim.y + (legend.bars[0].sim.h - surf.payload->h) / 2,
        .w = surf.payload->w,
        .h = surf.payload->h,
    });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void o_legend_draw (level_t level, SDL_Renderer * renderer, fonts_t fonts, colors_t colors, scene_t scene, legend_t legend, counters_t counters) {
    o_legend_draw_bars(level, renderer, scene, colors, legend, counters);
    o_legend_draw_rect_nbullets(renderer, scene, colors, legend, counters);
    o_legend_draw_text_nbullets(renderer, scene, fonts, colors, legend, counters);
    o_legend_draw_text_hit(renderer, scene, fonts, colors, legend);
    o_legend_draw_text_miss(renderer, scene, fonts, colors, legend);
    o_legend_draw_text_nhit(renderer, scene, fonts, colors, legend, counters);
    o_legend_draw_text_nmiss(renderer, scene, fonts, colors, legend, counters);
    o_legend_draw_text_nballoons(level, renderer, scene, fonts, colors, legend, counters);
    o_legend_draw_text_level(level, renderer, scene, fonts, colors, legend);
}

static SDL_Color o_legend_get_ammolow_bgcolor(counters_t counters, colors_t colors) {
    SDL_Color color;
    if (counters.nbullets.prespawn < 5) {
        color = colors.magenta;
    } else if (counters.nbullets.prespawn < 10) {
        color = colors.red;
    } else if (counters.nbullets.prespawn < 20) {
        color = colors.orange;
    } else if (counters.nbullets.prespawn < 30) {
        color = colors.green;
    } else {
        color = colors.bg;
    }
    return color;
}

legend_t o_legend_init (void) {
    const unsigned int n = 10;
    legend_t legend;
    legend.nbars = n;
    SDL_Rect first = {
        .x = 60,
        .y = 55,
        .w = 15,
        .h = 20,
    };
    for (unsigned int i = 0; i < legend.nbars; i++) {
        legend.bars[i].sim = (SDL_FRect) {
            .x = first.x + i * (first.w + 5),
            .y = first.y,
            .w = first.w,
            .h = first.h,
        };
    }
    legend.highlight.sim = (SDL_FRect) {
        .x = legend.bars[0].sim.x,
        .y = legend.bars[0].sim.y + legend.bars[0].sim.h + 7,
        .w = (legend.bars[n-1].sim.x + legend.bars[n-1].sim.w) - legend.bars[0].sim.x,
        .h = 40,
    };
    return legend;
}
