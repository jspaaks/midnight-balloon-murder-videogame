#ifndef DEINIT_H
#define DEINIT_H
#include "types.h"

void deinit (void);
void deinit_prepare (balloon_t **, bullet_t **, collision_t **, SDL_Renderer **, SDL_Window **,
                     SDL_Texture **, fonts_t *, chunks_t *);

#endif
