#include "fsm_level_finished.h"
#include "deinit.h"
#include "drawable_background.h"
#include "drawable_barrel.h"
#include "drawable_ground.h"
#include "drawable_keymap.h"
#include "drawable_legend.h"
#include "drawable_moon.h"
#include "drawable_titles.h"
#include "drawable_turret.h"
#include "fsm.h"
#include "fsm_playing.h"
#include "levels.h"
#include "scene.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "types.h"
#include <stdlib.h>

static void fsm_level_finished_draw_keymap_proceed (SDL_Renderer *, colors_t, fonts_t, scene_t,
                                                    level_t);
static void fsm_level_finished_draw_keymap_repeat_action (SDL_Renderer *, fonts_t, colors_t,
                                                          scene_t);
static void fsm_level_finished_draw_keymap_repeat_button (SDL_Renderer *, fonts_t, colors_t,
                                                          scene_t);

void fsm_level_finished_draw (level_t level, drawing_t drawing, drawables_t drawables,
                              counters_t counters) {
    drawable_background_draw(drawing.renderer, drawing.colors, drawing.scene);
    drawable_moon_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.moon);
    drawable_barrel_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.barrel);
    drawable_turret_draw(drawing.renderer, drawing.spritesheet, drawing.scene, drawables.turret);
    drawable_legend_draw(level, drawing.renderer, drawing.fonts, drawing.colors, drawing.scene,
                         drawables.legend, counters);
    drawable_ground_draw(drawing.renderer, drawing.colors, drawing.scene, drawables.ground);
    drawable_keymap_draw_proceedhint(level, drawing.renderer, drawing.fonts, drawing.colors,
                                     drawing.scene, drawables.ground, counters);
    drawable_titles_draw_level_finished(drawing.renderer, drawing.fonts, drawing.colors,
                                        drawing.scene, counters);
    fsm_level_finished_draw_keymap_proceed(drawing.renderer, drawing.colors, drawing.fonts,
                                           drawing.scene, level);
    fsm_level_finished_draw_keymap_repeat_button(drawing.renderer, drawing.fonts, drawing.colors,
                                                 drawing.scene);
    fsm_level_finished_draw_keymap_repeat_action(drawing.renderer, drawing.fonts, drawing.colors,
                                                 drawing.scene);
    SDL_RenderPresent(drawing.renderer);
}

static void fsm_level_finished_draw_keymap_proceed (SDL_Renderer * renderer, colors_t colors,
                                                    fonts_t fonts, scene_t scene, level_t level) {
    SDL_Color color;
    bool next_exists = level.label < LEVEL_BERSERKER;
    int c = next_exists << 1 | level.next_unlocked;
    switch (c) {
        case 0: {
            // next level doesnt exist, dont show anything
            return;
        }
        case 1: {
            // next level doesnt exist, dont show anything
            return;
        }
        case 2: {
            // level exists but is locked
            color = colors.middlegray;
            break;
        }
        case 3: {
            // level exists and is unlocked
            color = colors.lightgray;
            break;
        }
        default: {
            SDL_LogError(SDL_UNSUPPORTED,
                         "Something went wrong with determining the next level: %s",
                         SDL_GetError());
            deinit();
        }
    }

    // --- the keymap

    char caption1[7] = "RETURN";
    SDL_Surface * surf1 = TTF_RenderText_Shaded(fonts.large, caption1, color, colors.bg);
    if (surf1 == NULL) goto cleanup;
    SDL_Texture * txre1 = SDL_CreateTextureFromSurface(renderer, surf1);
    if (txre1 == NULL) goto cleanup;
    SDL_Rect tgt1 = sim2tgt(scene, (SDL_FRect){
                                       .x = 6 * scene.sim.w / 7 - surf1->w / 2,
                                       .y = scene.sim.h / 2 - surf1->h / 2,
                                       .w = surf1->w,
                                       .h = surf1->h,
                                   });
    SDL_RenderCopy(renderer, txre1, NULL, &tgt1);

    // --- the action

    char caption2[11] = "NEXT LEVEL";
    SDL_Surface * surf2 = TTF_RenderText_Shaded(fonts.regular, caption2, color, colors.bg);
    if (surf2 == NULL) goto cleanup;
    SDL_Texture * txre2 = SDL_CreateTextureFromSurface(renderer, surf2);
    if (txre2 == NULL) goto cleanup;
    SDL_Rect tgt2 = sim2tgt(scene, (SDL_FRect){
                                       .x = 6 * scene.sim.w / 7 - surf2->w / 2,
                                       .y = scene.sim.h / 2 - surf2->h / 2 + 30,
                                       .w = surf2->w,
                                       .h = surf2->h,
                                   });
    SDL_RenderCopy(renderer, txre2, NULL, &tgt2);

    // --- free resources
    SDL_DestroyTexture(txre1);
    SDL_DestroyTexture(txre2);
    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the proceed keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre1);
    SDL_DestroyTexture(txre2);
    SDL_FreeSurface(surf1);
    SDL_FreeSurface(surf2);
    deinit();
}

static void fsm_level_finished_draw_keymap_repeat_action (SDL_Renderer * renderer, fonts_t fonts,
                                                          colors_t colors, scene_t scene) {
    char keymap[13] = "REPEAT LEVEL";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.regular, keymap, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;
    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = 1 * scene.sim.w / 7 - surf->w / 2,
                                      .y = scene.sim.h / 2 - surf->h / 2 + 30,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the repeat-level action: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

static void fsm_level_finished_draw_keymap_repeat_button (SDL_Renderer * renderer, fonts_t fonts,
                                                          colors_t colors, scene_t scene) {
    char caption[2] = "R";
    SDL_Surface * surf = TTF_RenderText_Shaded(fonts.large, caption, colors.lightgray, colors.bg);
    if (surf == NULL) goto cleanup;
    SDL_Texture * txre = SDL_CreateTextureFromSurface(renderer, surf);
    if (txre == NULL) goto cleanup;
    SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                                      .x = 1 * scene.sim.w / 7 - surf->w / 2,
                                      .y = scene.sim.h / 2 - surf->h / 2,
                                      .w = surf->w,
                                      .h = surf->h,
                                  });
    SDL_RenderCopy(renderer, txre, NULL, &tgt);
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    return;
cleanup:
    SDL_LogError(SDL_ENOMEM, "Error creating the repeat-level keymap: %s.\n", TTF_GetError());
    SDL_DestroyTexture(txre);
    SDL_FreeSurface(surf);
    deinit();
}

void fsm_level_finished_update (timing_t, chunks_t, counters_t * counters, drawing_t * drawing,
                                drawables_t * drawables, gamestate_t ** gamestate,
                                level_t * level) {
    level->next_unlocked =
        level->next_unlocked || counters->nballoons.hit >= level->nballoons.proceed;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (level->next_unlocked && event.key.keysym.sym == SDLK_RETURN) {
                    *level = levels_get_level(level->label_next);
                    levels_reset_level(*level, *drawing, drawables, counters);
                    SDL_Log("playing -- next level\n");
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_r) {
                    levels_reset_level(*level, *drawing, drawables, counters);
                    SDL_Log("playing -- same level\n");
                    *gamestate = fsm_gamestate_get(GAMESTATE_PLAYING);
                } else if (event.key.keysym.sym == SDLK_F11) {
                    SDL_SetWindowFullscreen(drawing->window, drawing->scene.isfullscreen
                                                                 ? 0
                                                                 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    drawing->scene.resized = true;
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
}
