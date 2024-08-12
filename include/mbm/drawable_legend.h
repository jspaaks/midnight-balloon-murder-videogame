#ifndef DRAWABLE_LEGEND_H
#define DRAWABLE_LEGEND_H
#include "mbm/types.h"

void drawable_legend_draw (level_t, SDL_Renderer *, fonts_t, colors_t, scene_t, legend_t,
                           counters_t);
legend_t drawable_legend_init (void);

#endif
