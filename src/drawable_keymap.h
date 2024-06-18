#ifndef DRAWABLE_KEYMAP_H
#define DRAWABLE_KEYMAP_H
#include "types.h"

void drawable_keymap_draw_move_barrel (SDL_Renderer *, fonts_t, colors_t, scene_t, turret_t,
                                       ground_t);
void drawable_keymap_draw_pause (SDL_Renderer *, fonts_t, colors_t, scene_t, ground_t);
void drawable_keymap_draw_proceedhint (level_t, SDL_Renderer *, fonts_t, colors_t, scene_t,
                                       ground_t, counters_t);
void drawable_keymap_draw_quit (SDL_Renderer *, fonts_t, colors_t, scene_t, turret_t, ground_t);
void drawable_keymap_draw_restart (level_t, SDL_Renderer *, fonts_t, colors_t, scene_t, turret_t,
                                   ground_t, counters_t);
void drawable_keymap_draw_shoot (SDL_Renderer *, fonts_t, colors_t, scene_t, turret_t, ground_t);
void drawable_keymap_draw_start (SDL_Renderer *, fonts_t, colors_t, scene_t, ground_t);
void drawable_keymap_draw_unpause (SDL_Renderer *, fonts_t, colors_t, scene_t, ground_t);

#endif
