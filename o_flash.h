#ifndef O_FLASH_H
#define O_FLASH_H
#include "types.h"

void o_flash_draw (SDL_Renderer *, scene_t, SDL_Texture *, barrel_t, flash_t);
void o_flash_init (barrel_t, flash_t *);
void o_flash_update (ctx_t *, flash_t *);

#endif
