#ifndef DRAWABLE_FLASH_H
#define DRAWABLE_FLASH_H
#include "types.h"

void drawable_flash_draw (SDL_Renderer *, SDL_Texture *, scene_t, barrel_t, flash_t);
flash_t drawable_flash_init(barrel_t);
void drawable_flash_update (timing_t, flash_t *);

#endif
