#ifndef O_LEGEND_H
#define O_LEGEND_H
#include "types.h"

void o_legend_draw (ctx_t, SDL_Renderer *, scene_t, fonts_t, colors_t, legend_t, nballoons_t, nbullets_t);
void o_legend_init (legend_t *);

#endif
