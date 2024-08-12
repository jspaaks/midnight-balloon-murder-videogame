#ifndef LEVELS_H
#define LEVELS_H
#include "types.h"

level_t levels_get_level(level_enum_t);
void levels_reset_level (level_t, drawing_t, drawables_t *, counters_t *);

#endif
