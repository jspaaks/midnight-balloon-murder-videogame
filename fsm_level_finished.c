#include <stdlib.h>
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_log.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "fsm_level_finished.h"
#include "fsm_playing.h"
#include "fsm.h"
#include "levels.h"
#include "scene.h"
#include "types.h"
#include "wrapped.h"
#include "o_background.h"
#include "o_barrel.h"
#include "o_ground.h"
#include "o_keymap.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_titles.h"
#include "o_turret.h"

static void fsm_level_finished_draw_keymap_proceed(SDL_Renderer *, colors_t, fonts_t, scene_t, level_t);
static void fsm_level_finished_draw_keymap_repeat_action(SDL_Renderer *, fonts_t, colors_t, scene_t);
static void fsm_level_finished_draw_keymap_repeat_button(SDL_Renderer *, fonts_t, colors_t, scene_t);

void fsm_level_finished_draw (level_t level, drawing_t drawing, drawables_t drawables, counters_t counters) {
    o_background_draw(drawing.renderer, drawing.colors, drawing.scene);

    o_moon_draw(drawing.renderer,
                drawing.spritesheet,
                drawing.scene,
                drawables.moon);

    o_barrel_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.barrel);

    o_turret_draw(drawing.renderer,
                  drawing.spritesheet,
                  drawing.scene,
                  drawables.turret);

    o_legend_draw(level,
                  drawing.renderer,
                  drawing.fonts,
                  drawing.colors,
                  drawing.scene,
                  drawables.legend,
                  counters);

    o_ground_draw(drawing.renderer,
                  drawing.colors,
                  drawing.scene,
                  drawables.ground);

    o_keymap_draw_proceedhint(level,
                              drawing.renderer,
                              drawing.fonts,
                              drawing.colors,
                              drawing.scene,
                              drawables.ground,
                              counters);

    o_titles_draw_level_finished(drawing.renderer,
                                 drawing.fonts,
                                 drawing.colors,
                                 drawing.scene,
                                 counters);

    fsm_level_finished_draw_keymap_proceed(drawing.renderer,
                                           drawing.colors,
                                           drawing.fonts,
                                           drawing.scene,
                                           level);

    fsm_level_finished_draw_keymap_repeat_button(drawing.renderer,
                                                 drawing.fonts,
                                                 drawing.colors,
                                                 drawing.scene);

    fsm_level_finished_draw_keymap_repeat_action(drawing.renderer,
                                                 drawing.fonts,
                                                 drawing.colors,
                                                 drawing.scene);

    SDL_RenderPresent(drawing.renderer);
}

static void fsm_level_finished_draw_keymap_proceed(SDL_Renderer * renderer, colors_t colors, fonts_t fonts, scene_t scene, level_t level) {
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
            SDL_LogError(SDL_UNSUPPORTED, "Something went wrong with determining the next level: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }
    {
        char keymap[7] = "RETURN";
        SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.large, keymap, color, colors.bg);
        SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
        if (txre.invalid) {
            SDL_LogError(SDL_ENOMEM, "Error creating the proceed button keymap on level finished screen: %s.\n", TTF_GetError());
        }
        SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
            .x = 6 * scene.sim.w / 7 - surf.payload->w / 2,
            .y = scene.sim.h / 2 - surf.payload->h / 2,
            .w = surf.payload->w,
            .h = surf.payload->h,
        });
        SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
        SDL_DestroyTexture(txre.payload);
        SDL_FreeSurface(surf.payload);
    }
    {
        char keymap[11] = "NEXT LEVEL";
        SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, keymap, color, colors.bg);
        SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
        if (txre.invalid) {
            SDL_LogError(SDL_ENOMEM, "Error creating the proceed action keymap on level finished screen: %s.\n", TTF_GetError());
        }
        SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
            .x = 6 * scene.sim.w / 7 - surf.payload->w / 2,
            .y = scene.sim.h / 2 - surf.payload->h / 2 + 30,
            .w = surf.payload->w,
            .h = surf.payload->h,
        });
        SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
        SDL_DestroyTexture(txre.payload);
        SDL_FreeSurface(surf.payload);
    }
}

static void fsm_level_finished_draw_keymap_repeat_action(SDL_Renderer * renderer, fonts_t fonts, colors_t colors, scene_t scene) {
            char keymap[13] = "REPEAT LEVEL";
            SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.regular, keymap, colors.lightgray, colors.bg);
            SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
            if (txre.invalid) {
                SDL_LogError(SDL_ENOMEM, "Error creating the repeat action keymap on level finished screen: %s.\n", TTF_GetError());
            }
            SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                .x = 1 * scene.sim.w / 7 - surf.payload->w / 2,
                .y = scene.sim.h / 2 - surf.payload->h / 2 + 30,
                .w = surf.payload->w,
                .h = surf.payload->h,
            });
            SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
            SDL_DestroyTexture(txre.payload);
            SDL_FreeSurface(surf.payload);
}

static void fsm_level_finished_draw_keymap_repeat_button(SDL_Renderer * renderer, fonts_t fonts, colors_t colors, scene_t scene) {
            char keymap[2] = "R";
            SDLW_Surface surf = TTFW_RenderText_Shaded(fonts.large, keymap, colors.lightgray, colors.bg);
            SDLW_Texture txre = SDLW_CreateTextureFromSurface(renderer, surf);
            if (txre.invalid) {
                SDL_LogError(SDL_ENOMEM, "Error creating the repeat button keymap on level finished screen: %s.\n", TTF_GetError());
            }
            SDL_Rect tgt = sim2tgt(scene, (SDL_FRect){
                .x = 1 * scene.sim.w / 7 - surf.payload->w / 2,
                .y = scene.sim.h / 2 - surf.payload->h / 2,
                .w = surf.payload->w,
                .h = surf.payload->h,
            });
            SDL_RenderCopy(renderer, txre.payload, NULL, &tgt);
            SDL_DestroyTexture(txre.payload);
            SDL_FreeSurface(surf.payload);
}

void fsm_level_finished_update (timing_t, chunks_t, counters_t * counters, ctx_t *, drawing_t * drawing, drawables_t * drawables, gamestate_t ** gamestate, level_t * level) {
    level->next_unlocked = level->next_unlocked || counters->nballoons.hit >= level->nballoons.proceed;
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
                    SDL_SetWindowFullscreen(drawing->window, drawing->scene.isfullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    drawing->scene.isfullscreen = !drawing->scene.isfullscreen;
                }
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    drawing->scene.resized = true;
                }
                break;
            }
        }
    }
    scene_update(drawing->renderer, &drawing->scene);
}
