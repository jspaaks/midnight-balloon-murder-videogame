#include "deinit.h"
#include "drawable_keymap.h"
#include "scene.h"
#include "SDL_log.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "types.h"
#include <stdio.h>

void drawable_keymap_draw_move_barrel (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                       scene_t scene, turret_t turret, ground_t ground) {

    char caption[21] = "W / S TO MOVE BARREL";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = turret.sim.x + turret.sim.w / 2 - surf->w / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the move barrel keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_pause (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, ground_t ground) {

    char caption[13] = "ESC TO PAUSE";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the pause keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_proceedhint (level_t level, SDL_Renderer * renderer, fonts_t fonts,
                                       colors_t colors, scene_t scene, ground_t ground,
                                       counters_t counters) {
    SDL_Color color = colors.middlegray;

    char caption[100];
    if (level.label == LEVEL_BERSERKER) {
        sprintf(caption, "FINAL LEVEL");
    } else if (counters.nballoons.miss > level.nballoons.prespawn - level.nballoons.proceed) {
        sprintf(caption, "NOT ENOUGH HITS TO PROCEED TO NEXT LEVEL");
    } else if (level.next_unlocked || counters.nballoons.hit >= level.nballoons.proceed) {
        sprintf(caption, "NEXT LEVEL UNLOCKED");
        color = colors.lightgray;
    } else {
        sprintf(caption, "NEED %d HITS TO PROCEED TO NEXT LEVEL", level.nballoons.proceed);
    }

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, color, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the proceedhint keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_quit (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                scene_t scene, turret_t turret, ground_t ground) {
    char caption[10] = "Q TO QUIT";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = scene.sim.w - turret.sim.x - turret.sim.w / 2 - surf->w / 2,
                           .y = scene.sim.h - ground.sim.h / 3 - surf->h / 2,
                           .w = surf->w,
                           .h = surf->h,
                       });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the quit keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_restart (level_t level, SDL_Renderer * renderer, fonts_t fonts,
                                   colors_t colors, scene_t scene, turret_t turret, ground_t ground,
                                   counters_t counters) {
    if (counters.nballoons.prespawn == level.nballoons.prespawn &&
        counters.nbullets.prespawn == level.nbullets.prespawn) {
        // we're effectively at the start of the level already
        return;
    }
    char caption[19] = "R TO RESTART LEVEL";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = scene.sim.w - turret.sim.x - turret.sim.w / 2 - surf->w / 2,
                           .y = scene.sim.h - 2 * ground.sim.h / 3 - surf->h / 2,
                           .w = surf->w,
                           .h = surf->h,
                       });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the restart keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_shoot (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, turret_t turret, ground_t ground) {
    char caption[15] = "SPACE TO SHOOT";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = turret.sim.x + turret.sim.w / 2 - surf->w / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the shoot keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_start (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, ground_t ground) {
    char caption[20] = "PRESS ENTER TO PLAY";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.lightgray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the play keymap legend: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void drawable_keymap_draw_unpause (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                   scene_t scene, ground_t ground) {
    char caption[15] = "ESC TO UNPAUSE";

    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, caption, colors.middlegray, colors.ground);
    if (surf == NULL) goto cleanup;

    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;

    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf->w) / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the unpause keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}
