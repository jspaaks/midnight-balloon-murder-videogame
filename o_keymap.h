#ifndef O_KEYMAP_H
#define O_KEYMAP_H

void o_keymap_draw_move_barrel (SDL_Renderer *, scene_t, fonts_t, colors_t, turret_t, ground_t);
void o_keymap_draw_pause (SDL_Renderer *, scene_t, fonts_t, colors_t, ground_t);
void o_keymap_draw_proceedhint (ctx_t, SDL_Renderer *, scene_t, fonts_t, colors_t, ground_t);
void o_keymap_draw_quit (SDL_Renderer *, scene_t, fonts_t, colors_t, turret_t, ground_t);
void o_keymap_draw_restart (ctx_t, SDL_Renderer *, scene_t, fonts_t, colors_t, turret_t, ground_t);
void o_keymap_draw_shoot (SDL_Renderer *, scene_t, fonts_t, colors_t, turret_t, ground_t);
void o_keymap_draw_start (SDL_Renderer *, scene_t, fonts_t, colors_t, ground_t);
void o_keymap_draw_unpause (SDL_Renderer *, scene_t, fonts_t, colors_t, ground_t);

#endif
