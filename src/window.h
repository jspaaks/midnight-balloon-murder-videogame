#ifndef WINDOW_H
#define WINDOW_H
#include "types.h"

void window_deinit (SDL_Window **);
SDL_Window * window_init(scene_t);

#endif
