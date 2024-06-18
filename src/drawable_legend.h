#ifndef O_LEGEND_H
#define O_LEGEND_H
#include "types.h"

void drawable_legendrawable_draw (level_t, SDL_Renderer *, fonts_t, colors_t, scene_t, legendrawable_t, counters_t);
legendrawable_t drawable_legendrawable_init (void);

#endif
