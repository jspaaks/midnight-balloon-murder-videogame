#include "drawable_titles.h"
#include "deinit.h"
#include "scene.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "types.h"
#include <string.h>

void drawable_titles_draw_level_finished (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                          scene_t scene, counters_t counters) {
    char title[15];
    if (counters.nballoons.miss == 0) {
        strncpy(title, "PERFECT SCORE!", 15);
    } else {
        strncpy(title, "LEVEL FINISHED", 15);
    }
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.xlarge, title, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.h * 0.44 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;

cleanup:
    SDL_Log("Error creating the title on level finished screen: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_titles_draw_opening_title (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                         scene_t scene) {
    static const struct {
        char l[2];
        char m[22];
        char r[2];
    } titleparts = {
        .l = "M",
        .m = "IDNIGHT BALLOON MURDE",
        .r = "R",
    };

    static struct {
        SDL_Surface * l;
        SDL_Surface * m;
        SDL_Surface * r;
    } surfs;

    static struct {
        SDL_Texture * l;
        SDL_Texture * m;
        SDL_Texture * r;
    } txres;

    static struct {
        SDL_Rect l;
        SDL_Rect m;
        SDL_Rect r;
        SDL_Rect underline;
    } tgts;

    surfs.l = TTF_RenderText_Shaded(fonts.xxxlarge, titleparts.l, colors.lightgray, colors.bg);
    if (surfs.l == NULL) goto cleanup;

    surfs.m = TTF_RenderText_Shaded(fonts.xxlarge, titleparts.m, colors.lightgray, colors.bg);
    if (surfs.m == NULL) goto cleanup;

    surfs.r = TTF_RenderText_Shaded(fonts.xxxlarge, titleparts.r, colors.lightgray, colors.bg);
    if (surfs.r == NULL) goto cleanup;

    txres.l = SDL_CreateTextureFromSurface(renderer, surfs.l);
    if (txres.l == NULL) goto cleanup;

    txres.m = SDL_CreateTextureFromSurface(renderer, surfs.m);
    if (txres.m == NULL) goto cleanup;

    txres.r = SDL_CreateTextureFromSurface(renderer, surfs.r);
    if (txres.r == NULL) goto cleanup;

    tgts.l = sim2tgt(scene, (SDL_FRect){
                                .x = (scene.sim.w - surfs.m->w) / 2 - surfs.l->w,
                                .y = scene.sim.h * 0.31 - 7,
                                .w = surfs.l->w,
                                .h = surfs.l->h,
                            });
    tgts.m = sim2tgt(scene, (SDL_FRect){
                                .x = (scene.sim.w - surfs.m->w) / 2,
                                .y = scene.sim.h * 0.31,
                                .w = surfs.m->w,
                                .h = surfs.m->h,
                            });
    tgts.r = sim2tgt(scene, (SDL_FRect){
                                .x = (scene.sim.w - surfs.m->w) / 2 + surfs.m->w,
                                .y = scene.sim.h * 0.31 - 7,
                                .w = surfs.r->w,
                                .h = surfs.r->h,
                            });
    tgts.underline = sim2tgt(scene, (SDL_FRect){
                                        .x = (scene.sim.w - surfs.m->w) / 2,
                                        .y = scene.sim.h * 0.31 + surfs.m->h - 51,
                                        .w = surfs.m->w,
                                        .h = 3,
                                    });
    SDL_RenderCopy(renderer, txres.l, NULL, &tgts.l);
    SDL_RenderCopy(renderer, txres.m, NULL, &tgts.m);
    SDL_RenderCopy(renderer, txres.r, NULL, &tgts.r);
    SDL_SetRenderDrawColor(renderer, colors.lightgray.r, colors.lightgray.g, colors.lightgray.b,
                           colors.lightgray.a);
    SDL_RenderFillRect(renderer, &tgts.underline);

    SDL_DestroyTexture(txres.l);
    SDL_DestroyTexture(txres.m);
    SDL_DestroyTexture(txres.r);

    SDL_FreeSurface(surfs.l);
    SDL_FreeSurface(surfs.m);
    SDL_FreeSurface(surfs.r);
    return;

cleanup:
    SDL_Log("Error creating the title text.\n");
    SDL_DestroyTexture(txres.l);
    SDL_DestroyTexture(txres.m);
    SDL_DestroyTexture(txres.r);
    SDL_FreeSurface(surfs.l);
    SDL_FreeSurface(surfs.m);
    SDL_FreeSurface(surfs.r);
    deinit();
}

void drawable_titles_draw_paused (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                  scene_t scene) {

    char title[7] = "PAUSED";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.xlarge, title, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = scene.sim.x + (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.y + scene.sim.h * 0.44 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;

cleanup:
    SDL_Log("Error creating the title on paused screen: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}
