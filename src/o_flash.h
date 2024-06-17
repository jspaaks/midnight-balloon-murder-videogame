#ifndef O_FLASH_H
#define O_FLASH_H
#include "types.h"

void o_flash_draw (SDL_Renderer *, SDL_Texture *, scene_t, barrel_t, flash_t);
flash_t o_flash_init(barrel_t);
void o_flash_update (timing_t, flash_t *);

#endif
