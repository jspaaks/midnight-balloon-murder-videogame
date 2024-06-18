#include "drawable_keymap.h"
#include "scene.h"
#include "SDL_log.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "types.h"
#include "wrapped.h"
#include <stdio.h>

void drawable_keymap_draw_move_barrel (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                       scene_t scene, turret_t turret, ground_t ground) {
    char action[21] = "W / S TO MOVE BARREL";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, action, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = turret.sim.x + turret.sim.w / 2 - surf.payload->w / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_pause (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, ground_t ground) {
    char keymap[12] = "ESC TO PAUSE";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, keymap, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_proceedhint (level_t level, SDL_Renderer * renderer, fonts_t fonts,
                                       colors_t colors, scene_t scene, ground_t ground,
                                       counters_t counters) {
    SDL_Color color = colors.middlegray;

    char str[100];
    if (level.label == LEVEL_BERSERKER) {
        sprintf(str, "FINAL LEVEL");
    } else if (counters.nballoons.miss > level.nballoons.prespawn - level.nballoons.proceed) {
        sprintf(str, "NOT ENOUGH HITS TO PROCEED TO NEXT LEVEL");
    } else if (level.next_unlocked || counters.nballoons.hit >= level.nballoons.proceed) {
        sprintf(str, "NEXT LEVEL UNLOCKED");
        color = colors.lightgray;
    } else {
        sprintf(str, "NEED %d HITS TO PROCEED TO NEXT LEVEL", level.nballoons.proceed);
    }
    SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, str, color, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_quit (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                scene_t scene, turret_t turret, ground_t ground) {
    char keymap[10] = "Q TO QUIT";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, keymap, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the right bottom keymap on paused screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = scene.sim.w - turret.sim.x - turret.sim.w / 2 - surf.payload->w / 2,
                           .y = scene.sim.h - ground.sim.h / 3 - surf.payload->h / 2,
                           .w = surf.payload->w,
                           .h = surf.payload->h,
                       });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_restart (level_t level, SDL_Renderer * renderer, fonts_t fonts,
                                   colors_t colors, scene_t scene, turret_t turret, ground_t ground,
                                   counters_t counters) {
    if (counters.nballoons.prespawn == level.nballoons.prespawn &&
        counters.nbullets.prespawn == level.nbullets.prespawn) {
        // we're effectively at the start of the level already
        return;
    }
    char keymap[19] = "R TO RESTART LEVEL";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, keymap, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the right top keymap on paused screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt =
        sim2tgt(scene, (SDL_FRect){
                           .x = scene.sim.w - turret.sim.x - turret.sim.w / 2 - surf.payload->w / 2,
                           .y = scene.sim.h - 2 * ground.sim.h / 3 - surf.payload->h / 2,
                           .w = surf.payload->w,
                           .h = surf.payload->h,
                       });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_shoot (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, turret_t turret, ground_t ground) {
    char action[15] = "SPACE TO SHOOT";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, action, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = turret.sim.x + turret.sim.w / 2 - surf.payload->w / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_start (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                 scene_t scene, ground_t ground) {
    char keymap[20] = "PRESS ENTER TO PLAY";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, keymap, colors.lightgray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the keymap legend text on title screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.h - 2 * ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}

void drawable_keymap_draw_unpause (SDL_Renderer * renderer, fonts_t fonts, colors_t colors,
                                   scene_t scene, ground_t ground) {
    char keymap[15] = "ESC TO UNPAUSE";
    SDLW_Surface surf =
        TTFW_RenderText_Shaded(fonts.regular, keymap, colors.middlegray, colors.ground);
    SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
    if (txre.invalid) {
        SDL_LogError(SDL_ENOMEM, "Error creating the middle keymap on paused screen: %s.\n",
                     TTF_GetError());
    }
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = (scene.sim.w - surf.payload->w) / 2,
                                      .y = scene.sim.h - ground.sim.h / 3 - surf.payload->h / 2,
                                      .w = surf.payload->w,
                                      .h = surf.payload->h,
                                  });
    SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
    SDL_DestroyTexture(txre.payload);
    SDL_FreeSurface(surf.payload);
}
