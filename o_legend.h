#ifndef O_LEGEND_H
#define O_LEGEND_H
#include "types.h"

void o_legend_draw (ctx_t, SDL_Renderer *, fonts_t, colors_t, scene_t, legend_t, counters_t);
legend_t o_legend_init (void);

#endif
