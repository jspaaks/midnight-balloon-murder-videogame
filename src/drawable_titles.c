#include "drawable_titles.h"
#include "scene.h"
#include "SDL_log.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "types.h"
#include "wrapped.h"
#include <string.h>

void drawable_titles_draw_level_finished (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                          scene_t scene, counters_t counters) {
    char title[15];
    if (counters.nballoons.miss == 0) {
        strncpy(title, "PERFECT SCORE!", 15);
    } else {
        strncpy(title, "LEVEL FINISHED", 15);
    }
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.xlarge, title, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title on level finished screen: %s.\n",
                     TTF_GetError());
        // TODO free and exit
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.h * 0.44 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_titles_draw_opening_title (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                         scene_t scene) {
    static const struct {
        char left[2];
        char middle[22];
        char right[2];
    } titleparts = {
        .left = "M",
        .middle = "IDNIGHT BALLOON MURDE",
        .right = "R",
    };

    static struct {
        SDLW_Surface left;
        SDLW_Surface middle;
        SDLW_Surface right;
    } surfs;

    static struct {
        SDLW_Texture left;
        SDLW_Texture middle;
        SDLW_Texture right;
    } txres;

    static struct {
        SDL_Rect left;
        SDL_Rect middle;
        SDL_Rect right;
        SDL_Rect underline;
    } tgts;

    surfs.left =
        TTFW_RenderText_Shaded(fonts.xxxlarge, titleparts.left, colors.lightgray, colors.bg);
    surfs.middle =
        TTFW_RenderText_Shaded(fonts.xxlarge, titleparts.middle, colors.lightgray, colors.bg);
    surfs.right =
        TTFW_RenderText_Shaded(fonts.xxxlarge, titleparts.right, colors.lightgray, colors.bg);

    txres.left = SDLW_CreateTextureFromSurface(renderer, surfs.left);
    txres.middle = SDLW_CreateTextureFromSurface(renderer, surfs.middle);
    txres.right = SDLW_CreateTextureFromSurface(renderer, surfs.right);

    if (txres.left.invalid || txres.middle.invalid || txres.right.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title text.\n");
        // TODO free
        exit(EXIT_FAILURE);
    }

    tgts.left =
        sim2tgt(scene, (SDL_FRect){
                           .x = (scene.sim.w - surfs.middle.payload->w) / 2 - surfs.left.payload->w,
                           .y = scene.sim.h * 0.31 - 7,
                           .w = surfs.left.payload->w,
                           .h = surfs.left.payload->h,
                       });
    tgts.middle = sim2tgt(scene, (SDL_FRect){
                                     .x = (scene.sim.w - surfs.middle.payload->w) / 2,
                                     .y = scene.sim.h * 0.31,
                                     .w = surfs.middle.payload->w,
                                     .h = surfs.middle.payload->h,
                                 });
    tgts.right = sim2tgt(
        scene, (SDL_FRect){
                   .x = (scene.sim.w - surfs.middle.payload->w) / 2 + surfs.middle.payload->w,
                   .y = scene.sim.h * 0.31 - 7,
                   .w = surfs.right.payload->w,
                   .h = surfs.right.payload->h,
               });
    tgts.underline = sim2tgt(scene, (SDL_FRect){
                                        .x = (scene.sim.w - surfs.middle.payload->w) / 2,
                                        .y = scene.sim.h * 0.31 + surfs.middle.payload->h - 51,
                                        .w = surfs.middle.payload->w,
                                        .h = 3,
                                    });
    SDL_RenderCopy(renderer, txres.left.payload, NULL, &tgts.left);
    SDL_RenderCopy(renderer, txres.middle.payload, NULL, &tgts.middle);
    SDL_RenderCopy(renderer, txres.right.payload, NULL, &tgts.right);
    SDL_SetRenderDrawColor(renderer, colors.lightgray.r, colors.lightgray.g, colors.lightgray.b,
                           colors.lightgray.a);
    SDL_RenderFillRect(renderer, &tgts.underline);

    SDL_DestroyTexture(txres.left.payload);
    SDL_DestroyTexture(txres.middle.payload);
    SDL_DestroyTexture(txres.right.payload);

    SDL_FreeSurface(surfs.left.payload);
    SDL_FreeSurface(surfs.middle.payload);
    SDL_FreeSurface(surfs.right.payload);
}

void drawable_titles_draw_paused (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                  scene_t scene) {
    char title[7] = "PAUSED";
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.xlarge, title, colors.lightgray, colors.bg);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the title on paused screen: %s.\n",
                     TTF_GetError());
        // TODO free and exit
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = scene.sim.x + (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.y + scene.sim.h * 0.44 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}
