#ifndef S_PAUSED_H
#define S_PAUSED_H

#include "types.h"
#include "fsm.h"

void paused_draw (ctx_t *);
void paused_update (ctx_t *, struct state **);

#endif
