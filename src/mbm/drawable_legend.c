#include "mbm/drawable_legend.h"
#include "mbm/colors.h"
#include "mbm/deinit.h"
#include "mbm/drawable_balloons.h"
#include "mbm/levels.h"
#include "mbm/scene.h"
#include "SDL_log.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_ttf.h"
#include "mbm/types.h"
#include <stdio.h>

static void drawable_legend_draw_bars (level_t, SDL_Renderer *, scene_t, colors_t, legend_t,
                                       counters_t);
static void drawable_legend_draw_rect_nbullets (SDL_Renderer *, scene_t, colors_t, legend_t,
                                                counters_t);
static void drawable_legend_draw_text_hit (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t);
static void drawable_legend_draw_text_level (level_t, SDL_Renderer *, scene_t, fonts_t, colors_t,
                                             legend_t);
static void drawable_legend_draw_text_miss (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t);
static void drawable_legend_draw_text_nballoons (level_t, SDL_Renderer *, scene_t, fonts_t,
                                                 colors_t, legend_t, counters_t);
static void drawable_legend_draw_text_nbullets (SDL_Renderer *, scene_t, fonts_t, colors_t,
                                                legend_t, counters_t);
static void drawable_legend_draw_text_nhit (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t,
                                            counters_t);
static void drawable_legend_draw_text_nmiss (SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t,
                                             counters_t);
static SDL_Color drawable_legend_get_ammolow_bgcolor(counters_t, colors_t);

static void drawable_legend_draw_bars (level_t level, SDL_Renderer * renderer, scene_t scene,
                                       colors_t colors, legend_t legend, counters_t counters) {
    int j = 0;
    int nhit = legend.nbars * counters.nballoons.hit / level.nballoons.prespawn;
    int nmiss = legend.nbars * counters.nballoons.miss / level.nballoons.prespawn;
    int nmiddle = legend.nbars - nhit - nmiss;
    SDL_SetRenderDrawColor(renderer, colors.hit.r, colors.hit.g, colors.hit.b, colors.hit.a);
    for (int i = 0; i < nhit; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }

    SDL_SetRenderDrawColor(renderer, colors.middlegray.r, colors.middlegray.g, colors.middlegray.b,
                           colors.middlegray.a);
    for (int i = 0; i < nmiddle; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }

    SDL_SetRenderDrawColor(renderer, colors.miss.r, colors.miss.g, colors.miss.b, colors.miss.a);
    for (int i = 0; i < nmiss; i++, j++) {
        SDL_Rect tgt = sim2tgt(scene, legend.bars[j].sim);
        SDL_RenderFillRect(renderer, &tgt);
    }
}

static void drawable_legend_draw_rect_nbullets (SDL_Renderer * renderer, scene_t scene,
                                                colors_t colors, legend_t legend,
                                                counters_t counters) {
    // choose a warning color or use background color if not low on ammo
    SDL_Color color = drawable_legend_get_ammolow_bgcolor(counters, colors);

    // render the bullet count highlight rect
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect tgt = sim2tgt(scene, legend.highlight.sim);
    SDL_RenderFillRect(renderer, &tgt);
}

static void drawable_legend_draw_text_hit (SDL_Renderer * renderer, scene_t scene, fonts_t fonts,
                                           colors_t colors, legend_t legend) {
    static const char caption[4] = "HIT";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = legend.bars[0].sim.x,
                                      .y = legend.bars[0].sim.y - surf->h,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the HIT legend text.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_level (level_t level, SDL_Renderer * renderer, scene_t scene,
                                             fonts_t fonts, colors_t colors, legend_t legend) {
    char caption[30];
    sprintf(caption, "%s LEVEL", level.name);

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = 2 * scene.sim.w / 4 - surf->w / 2,
                                      .y = legend.bars[0].sim.y - surf->h,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the LEVEL legend text.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_miss (SDL_Renderer * renderer, scene_t scene, fonts_t fonts,
                                            colors_t colors, legend_t legend) {

    static const char caption[5] = "MISS";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = legend.bars[legend.nbars - 1].sim.x +
                                           legend.bars[legend.nbars - 1].sim.w - surf->w,
                                      .y = legend.bars[0].sim.y - surf->h,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the MISS legend text.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_nballoons (level_t level, SDL_Renderer * renderer,
                                                 scene_t scene, fonts_t fonts, colors_t colors,
                                                 legend_t legend, counters_t counters) {
    int nremaining = counters.nballoons.prespawn + counters.nballoons.airborne;
    if (nremaining == 0) {
        // we're in the level finished screen
        return;
    }
    char caption[30];
    sprintf(caption, "BALLOONS %d / %d", nremaining, level.nballoons.prespawn);

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = 3 * scene.sim.w / 4 - surf->w / 2,
                                      .y = legend.bars[0].sim.y - surf->h,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the BALLOONS legend text.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_nbullets (SDL_Renderer * renderer, scene_t scene,
                                                fonts_t fonts, colors_t colors, legend_t legend,
                                                counters_t counters) {

    char caption[30];
    sprintf(caption, "BULLETS %d", counters.nbullets.prespawn);
    SDL_Color fgcolor = counters.nbullets.prespawn >= 30 ? colors.lightgray : colors.white;
    SDL_Color bgcolor = drawable_legend_get_ammolow_bgcolor(counters, colors);

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, fgcolor, bgcolor);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = legend.highlight.sim.x + (legend.highlight.sim.w - surf->w) / 2,
                           .y = legend.highlight.sim.y + (legend.highlight.sim.h - surf->h) / 2,
                           .w = surf->w,
                           .h = surf->h,
                       });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the BULLETS legend caption.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_nhit (SDL_Renderer * renderer, scene_t scene, fonts_t fonts,
                                            colors_t colors, legend_t legend, counters_t counters) {

    char caption[30];
    sprintf(caption, "%d", counters.nballoons.hit);

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = legend.bars[0].sim.x - surf->w - 10,
                           .y = legend.bars[0].sim.y + (legend.bars[0].sim.h - surf->h) / 2,
                           .w = surf->w,
                           .h = surf->h,
                       });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the legend text for counters.nballoons.hit.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void drawable_legend_draw_text_nmiss (SDL_Renderer * renderer, scene_t scene, fonts_t fonts,
                                             colors_t colors, legend_t legend,
                                             counters_t counters) {
    char caption[30];
    sprintf(caption, "%d", counters.nballoons.miss);

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = legend.bars[legend.nbars - 1].sim.x +
                                legend.bars[legend.nbars - 1].sim.w + 10,
                           .y = legend.bars[0].sim.y + (legend.bars[0].sim.h - surf->h) / 2,
                           .w = surf->w,
                           .h = surf->h,
                       });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_Log("Error creating the legend text for counters.nballoons.miss.\n");
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_legend_draw (level_t level, SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                           scene_t scene, legend_t legend, counters_t counters) {
    drawable_legend_draw_bars(level, renderer, scene, colors, legend, counters);
    drawable_legend_draw_rect_nbullets(renderer, scene, colors, legend, counters);
    drawable_legend_draw_text_nbullets(renderer, scene, fonts, colors, legend, counters);
    drawable_legend_draw_text_hit(renderer, scene, fonts, colors, legend);
    drawable_legend_draw_text_miss(renderer, scene, fonts, colors, legend);
    drawable_legend_draw_text_nhit(renderer, scene, fonts, colors, legend, counters);
    drawable_legend_draw_text_nmiss(renderer, scene, fonts, colors, legend, counters);
    drawable_legend_draw_text_nballoons(level, renderer, scene, fonts, colors, legend, counters);
    drawable_legend_draw_text_level(level, renderer, scene, fonts, colors, legend);
}

static SDL_Color drawable_legend_get_ammolow_bgcolor (counters_t counters, colors_t colors) {
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

legend_t drawable_legend_init (void) {
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
        legend.bars[i].sim = (SDL_FRect){
            .x = first.x + i * (first.w + 5),
            .y = first.y,
            .w = first.w,
            .h = first.h,
        };
    }
    legend.highlight.sim = (SDL_FRect){
        .x = legend.bars[0].sim.x,
        .y = legend.bars[0].sim.y + legend.bars[0].sim.h + 7,
        .w = (legend.bars[n - 1].sim.x + legend.bars[n - 1].sim.w) - legend.bars[0].sim.x,
        .h = 40,
    };
    return legend;
}
