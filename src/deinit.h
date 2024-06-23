#ifndef DEINIT_H
#define DEINIT_H
#include "types.h"

void deinit (void);
void deinit_prepare_all (balloon_t **, bullet_t **, collision_t **, SDL_Renderer **, SDL_Window **,
                         SDL_Texture **, fonts_t *, chunks_t *);
void deinit_prepare_balloons (balloon_t **);
void deinit_prepare_bullets (bullet_t **);
void deinit_prepare_chunks (chunks_t *);
void deinit_prepare_collisions (collision_t **);
void deinit_prepare_fonts (fonts_t *);
void deinit_prepare_renderer (SDL_Renderer **);
void deinit_prepare_spritesheet (SDL_Texture **);
void deinit_prepare_window (SDL_Window **);

#endif
